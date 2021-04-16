/*!
 \file hash.h
 Describes hash functions used in this project.
 */

#pragma once

#include <functional>
#include <type_traits>
#include <cinttypes>
#include <string>
#include <iostream>
#include "farmhash/farmhash.h"
#include "utils/hashutil.h"

template<class K>
class Hasher32 {
public:
  uint32_t s;    //!< hash s.
  
  Hasher32()
    : s(0xe2211) {
  }
  
  explicit Hasher32(uint32_t _s)
    : s(_s) {
  }
  
  //! set bitmask and s
  void setSeed(uint32_t _s) {
    s = _s;
  }
  
  template<class K1>
  inline typename std::enable_if<!std::is_same<K1, std::string>::value, uint64_t *>::type
  getBase(const K &k0) const {
    uint64_t *base;
    return (uint64_t *) &k0;
  }
  
  template<class K1>
  inline typename std::enable_if<std::is_same<K1, std::string>::value, uint64_t *>::type
  getBase(const K &k0) const {
    uint64_t *base;
    return (uint64_t *) &k0[0];
  }
  
  template<class K1>
  inline typename std::enable_if<!std::is_same<K1, std::string>::value, uint16_t>::type
  getKeyByteLength(const K &k0) const {
    return sizeof(K);
  }
  
  template<class K1>
  inline typename std::enable_if<std::is_same<K1, std::string>::value, uint16_t>::type
  getKeyByteLength(const K &k0) const {
    return k0.length();
  }
  
  inline uint32_t operator()(const K &k0) const {
    static_assert(sizeof(K) <= 32, "K length should be 32/64/96/128/160/192/224/256 bits");
    
    uint64_t *base = getBase<K>(k0);
    const uint16_t keyByteLength = getKeyByteLength<K>(k0);
    return farmhash::Hash32WithSeed((char *) base, (size_t) keyByteLength, s);
//    return XXH32((void*) base, keyByteLength, s);
  }
};

//! \brief A hash function that hashes keyType to uint32_t. When SSE4.2 support is found, use sse4.2 instructions, otherwise use default hash function  std::hash.
template<class K>
class Hasher64 {
public:
  uint64_t s;    //!< hash s.
  
  Hasher64()
    : s(0xe2211e2211) {
  }
  
  explicit Hasher64(const Hasher64 &h)
    : s(h.s) {
  }
  
  explicit Hasher64(uint64_t _s)
    : s(_s) {
  }
  
  //! set bitmask and s
  void setSeed(uint64_t _s) {
    s = _s;
  }
  
  template<class K1>
  inline typename std::enable_if<!std::is_same<K1, std::string>::value, uint64_t *>::type
  getBase(const K &k0) const {
    uint64_t *base;
    return (uint64_t *) &k0;
  }
  
  template<class K1>
  inline typename std::enable_if<std::is_same<K1, std::string>::value, uint64_t *>::type
  getBase(const K &k0) const {
    uint64_t *base;
    return (uint64_t *) &k0[0];
  }
  
  template<class K1>
  inline typename std::enable_if<!std::is_same<K1, std::string>::value, uint16_t>::type
  getKeyByteLength(const K &k0) const {
    return sizeof(K);
  }
  
  template<class K1>
  inline typename std::enable_if<std::is_same<K1, std::string>::value, uint16_t>::type
  getKeyByteLength(const K &k0) const {
    return k0.length();
  }
  
  inline uint64_t operator()(const K &k0) const {
    uint64_t *base = getBase<K>(k0);
    const uint16_t keyByteLength = getKeyByteLength<K>(k0);
    return farmhash::Hash64WithSeed((char *) base, (size_t) keyByteLength, s);
//    return XXH64((void *) base, keyByteLength, s);
  }
};

// Employing CRC32 to be compatible with the Tofino ASIC
template<class K>
class CRCHasher64 : public Hasher64<K> {
public :
  uint32_t CRC32Table[256] = {0};
  uint32_t CRC32CTable[256] = {0};
  uint32_t CRC32DTable[256] = {0};
public:
  CRCHasher64()
    : Hasher64<K>(0xe2211e2211) {
    initCRC32Table();
    initCRC32CTable();
    initCRC32DTable();
  }
  
  explicit CRCHasher64(uint64_t _s)
    : Hasher64<K>(_s) {
    initCRC32Table();
    initCRC32CTable();
    initCRC32DTable();
  }

  inline void initCRC32Table() {
    for (int i = 0; i < 256; i++) {
      uint32_t crc = i;
      for (int j = 0; j < 8; j++) {
        if (crc & 1) {
          crc = (crc >> 1) ^ 0xEDB88320;
        }
        else {
          crc >>= 1;
        }
      }
      CRC32Table[i] = crc;
    }
  }

  inline void initCRC32CTable() {
    for (int i = 0; i < 256; i++) {
      uint32_t crc = i;
      for (int j = 0; j < 8; j++) {
        if (crc & 1) {
          crc = (crc >> 1) ^ 0x82F63B78;
        }
        else {
          crc >>= 1;
        }
      }
      CRC32CTable[i] = crc;
    }
  }

  inline void initCRC32DTable() {
    for (int i = 0; i < 256; i++) {
      uint32_t crc = i;
      for (int j = 0; j < 8; j++) {
        if (crc & 1) {
          crc = (crc >> 1) ^ 0xD419CC15;
        }
        else {
          crc >>= 1;
        }
      }
      CRC32DTable[i] = crc;
    }
  }

  inline uint32_t getCRC32(const void* buf, uint16_t len) const {
    uint8_t *data = (uint8_t *)buf;
    uint32_t CRC32 = 0xFFFFFFFF;
    for (int i = 0; i < len; i++) {
      uint32_t t = (CRC32 ^ data[i]) & 0xFF;
      CRC32 = ((CRC32 >> 8) & 0xFFFFFF) ^ CRC32Table[t];
    }
    CRC32 ^= 0xFFFFFFFF;
    return CRC32;
  }

  inline uint32_t getCRC32(void* buf, const uint16_t len, uint32_t seed) const {
    uint8_t *data = (uint8_t *)buf;
    uint32_t CRC32 = 0xFFFFFFFF;
    // Process data
    for (int i = 0; i < len; i++) {
      uint32_t t = (CRC32 ^ data[i]) & 0xFF;
      CRC32 = ((CRC32 >> 8) & 0xFFFFFF) ^ CRC32Table[t];
    }
    // Process seed
    uint32_t t = (CRC32 ^ *((uint8_t *)&seed)) & 0xFF;
    CRC32 = ((CRC32 >> 8) & 0xFFFFFF) ^ CRC32Table[t];
    // for (int i = 0; i < 4; i++) {
    //   uint32_t t = (CRC32 ^ ((uint8_t *)&seed)[i]) & 0xFF;
    //   CRC32 = ((CRC32 >> 8) & 0xFFFFFF) ^ CRC32Table[t];
    // }
    CRC32 ^= 0xFFFFFFFF;
    // printf("Key: 0x%08x, Seed: 0x%08x, CRC32: 0x%08x\n", *(uint32_t *)buf, seed, CRC32);
    return CRC32;
  }

  inline uint32_t getCRC32C(const void* buf, uint16_t len) const {
    uint8_t *data = (uint8_t *)buf;
    uint32_t CRC32C = 0xFFFFFFFF;
    for (int i = 0; i < len; i++) {
      uint32_t t = (CRC32C ^ data[i]) & 0xFF;
      CRC32C = ((CRC32C >> 8) & 0xFFFFFF) ^ CRC32CTable[t];
    }
    CRC32C ^= 0xFFFFFFFF;
    return CRC32C;
  }

  inline uint32_t getCRC32C(void* buf, const uint16_t len, uint32_t seed) const {
    uint8_t *data = (uint8_t *)buf;
    uint32_t CRC32C = 0xFFFFFFFF;
    // Process data
    for (int i = 0; i < len; i++) {
      uint32_t t = (CRC32C ^ data[i]) & 0xFF;
      CRC32C = ((CRC32C >> 8) & 0xFFFFFF) ^ CRC32CTable[t];
    }
    // Process seed
    uint32_t t = (CRC32C ^ *((uint8_t *)&seed)) & 0xFF;
    CRC32C = ((CRC32C >> 8) & 0xFFFFFF) ^ CRC32CTable[t];
    // for (int i = 0; i < 4; i++) {
    //   uint32_t t = (CRC32C ^ ((uint8_t *)&seed)[i]) & 0xFF;
    //   CRC32C = ((CRC32C >> 8) & 0xFFFFFF) ^ CRC32CTable[t];
    // }
    CRC32C ^= 0xFFFFFFFF;
    // printf("Key: 0x%08x, Seed: 0x%08x, CRC32C: 0x%08x\n", *(uint32_t *)buf, seed, CRC32C);
    return CRC32C;
  }

  inline uint32_t getCRC32D(const void* buf, uint16_t len) const {
    uint8_t *data = (uint8_t *)buf;
    uint32_t CRC32D = 0xFFFFFFFF;
    for (int i = 0; i < len; i++) {
      uint32_t t = (CRC32D ^ data[i]) & 0xFF;
      CRC32D = ((CRC32D >> 8) & 0xFFFFFF) ^ CRC32DTable[t];
    }
    CRC32D ^= 0xFFFFFFFF;
    return CRC32D;
  }

  inline uint32_t getCRC32D(void* buf, const uint16_t len, uint32_t seed) const {
    uint8_t *data = (uint8_t *)buf;
    uint32_t CRC32D = 0xFFFFFFFF;
    // Process data
    for (int i = 0; i < len; i++) {
      uint32_t t = (CRC32D ^ data[i]) & 0xFF;
      CRC32D = ((CRC32D >> 8) & 0xFFFFFF) ^ CRC32DTable[t];
    }
    // Process seed
    uint32_t t = (CRC32D ^ *((uint8_t *)&seed)) & 0xFF;
    CRC32D = ((CRC32D >> 8) & 0xFFFFFF) ^ CRC32DTable[t];
    // for (int i = 0; i < 4; i++) {
    //   uint32_t t = (CRC32D ^ ((uint8_t *)&seed)[i]) & 0xFF;
    //   CRC32D = ((CRC32D >> 8) & 0xFFFFFF) ^ CRC32DTable[t];
    // }
    CRC32D ^= 0xFFFFFFFF;
    // printf("Key: 0x%08x, Seed: 0x%08x, CRC32D: 0x%08x\n", *(uint32_t *)buf, seed, CRC32D);
    return CRC32D;
  }

  inline uint64_t operator()(const K &k0) const {
    void *base = this -> template getBase<K>(k0);
    const uint16_t keyByteLength = this -> template getKeyByteLength<K>(k0);
    uint32_t h[2];
    
    // h[0] = getCRC32C(base, keyByteLength, this->s);
    // h[1] = getCRC32D(base, keyByteLength, this->s);
    h[0] = h[1] = this->getCRC32(base, keyByteLength, this->s);
    h[0] ^= this->getCRC32C(base, keyByteLength, this->s);
    h[1] ^= this->getCRC32D(base, keyByteLength, this->s);
 
    // printf("Bucket Index - Key: 0x%08x, Seed: 0x%08x, Hash: 0x%016lx\n", k0, this->s, *(uint64_t*)h);
 
    return *(uint64_t*)h;
  }
};

/*
//! \brief A hash function that hashes keyType to uint32_t. When SSE4.2 support is found, use sse4.2 instructions, otherwise use default hash function  std::hash.
template<class K>
class FastHasher64 : public Hasher64<K> {
public :
public:
  FastHasher64()
    : Hasher64<K>(0xe2211e2211) {
  }
  
  explicit FastHasher64(uint64_t _s)
    : Hasher64<K>(_s) {
  }
  
  inline uint64_t operator()(const K &k0) const {
    void *base = this -> template getBase<K>(k0);
    const uint16_t keyByteLength = this -> template getKeyByteLength<K>(k0);
    uint32_t h[2];
    *(uint64_t*)h = this->s;
    
    HashUtil::BobHash(base, keyByteLength, h, h+1);
    return *(uint64_t*)h;
  }
};
*/

template<class K>
class FastHasher64 : public CRCHasher64<K> {
public :
public:
  FastHasher64()
    : CRCHasher64<K>(0xe2211e2211) {
  }
  
  explicit FastHasher64(uint64_t _s)
    : CRCHasher64<K>(_s) {
  }

  inline uint64_t operator()(const K &k0) const {
    void *base = this -> template getBase<K>(k0);
    const uint16_t keyByteLength = this -> template getKeyByteLength<K>(k0);
    uint32_t h[2];
    
    h[0] = h[1] = this->getCRC32(base, keyByteLength, this->s);
    h[1] += this->getCRC32C(base, keyByteLength, this->s);
    h[1] += this->getCRC32D(base, keyByteLength, this->s);
 
    // printf("Slot Locator - Key: 0x%08x, Seed: 0x%08x, Hash: 0x%016lx, Slot: %lu\n", k0, this->s, *(uint64_t*)h, *(uint64_t*)h >> 62);
 
    return *(uint64_t*)h;
  }
};

template<class K>
class OthelloHasher64 : public CRCHasher64<K> {
public :
public:
  OthelloHasher64()
    : CRCHasher64<K>(0xe2211e2211) {
  }
  
  explicit OthelloHasher64(uint64_t _s)
    : CRCHasher64<K>(_s) {
  }

  inline uint64_t operator()(const K &k0) const {
    void *base = this -> template getBase<K>(k0);
    const uint16_t keyByteLength = this -> template getKeyByteLength<K>(k0);
    uint32_t h[2];

    h[0] = h[1] = this->getCRC32(base, keyByteLength, this->s);
    h[0] += this->getCRC32C(base, keyByteLength, this->s);
    h[1] += this->getCRC32D(base, keyByteLength, this->s);
 
    // printf("Bucket Locator - Key: 0x%08x, Seed: 0x%08x, Hash: 0x%016lx\n", k0, this->s, *(uint64_t*)h);
 
    return *(uint64_t*)h;
  }
};
