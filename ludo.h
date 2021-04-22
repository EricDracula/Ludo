/*************************************************************************
    > File Name: ludo.h
    > Author: 
    > Mail: 
    > Created Time: Mon 12 Apr 2021 10:20:13 PM CST
 ************************************************************************/

#ifndef _LUDO_H
#define _LUDO_H

#include <stdint.h>

#define Vlen 8

typedef uint32_t Key;
// typedef uint8_t Key;
typedef uint8_t Val;

typedef struct ExportLudo {
    uint32_t  bucket_num;
    uint8_t   bucket_index_seed;
    uint32_t  bucket_locator_a_len;
    uint32_t  bucket_locator_b_len;
    uint8_t   bucket_locator_seed;
    uint64_t* bucket_locator;
    uint8_t*  bucket_seeds;
    uint32_t* buckets;
} ExportLudo;

extern "C" {
void ludo_construct(Key* keys, Val* values, uint32_t entryCount, 
                    uint32_t ludoSize, ExportLudo* exportLudo);
}

#endif
