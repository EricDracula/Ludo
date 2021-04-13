/*************************************************************************
    > File Name: ludo.cpp
    > Author: 
    > Mail: 
    > Created Time: Tue 06 Apr 2021 03:09:20 PM CST
 ************************************************************************/

#include "cstdlib"
#include "ludo.h"
#include "MinimalPerfectCuckoo/minimal_perfect_cuckoo.h"

#define Vlen 8

typedef uint32_t Key;
// typedef uint8_t Key;
typedef uint8_t Val;

void ludo() {
// int main(int argc, char **argv) {
    ControlPlaneMinimalPerfectCuckoo<Key, Val, Vlen> cp(256);
    Key k = 128;
    Val v = 0;

    /*
    cp.insert(1, 0);
    cp.insert(10, 1);
    cp.insert(100, 2);
    cp.insert(1000, 3);
    cp.insert(10000, 4);
    cp.insert(100000, 5);
    */
    for (int i = 0; i <= 255; i++) {
        cp.insert(i, i);
    }

    cp.prepareToExport();

    DataPlaneMinimalPerfectCuckoo<Key, Val, Vlen> dp(cp);

    printf("Bucket number: %u\n", dp.num_buckets_);

    uint32_t checksum = 0;
    for (int idx = 0; idx < dp.num_buckets_; idx++) {
        DataPlaneMinimalPerfectCuckoo<Key, Val, Vlen>::Bucket bucket;
        bucket = dp.readBucket(idx);
        printf(
            "Bucket %5d -- Seed: 0x%05x -- Slots: %5u%5u%5u%5u\n", idx, bucket.seed,
            bucket.values[0], bucket.values[1], bucket.values[2], bucket.values[3]
        );
        checksum += bucket.values[0];
        checksum += bucket.values[1];
        checksum += bucket.values[2];
        checksum += bucket.values[3];
    }
    printf("Checksum: %u\n", checksum);
    
    printf("Othello Bitarray A Len: %d\n", dp.locator.ma);
    printf("Othello Bitarray B Len: %d\n", dp.locator.mb);
    dp.lookUp(k, v);
    printf("LookUp Test: Key %u - Value %u\n", k, v);

    // return 0;
}
