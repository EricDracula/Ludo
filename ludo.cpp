/*************************************************************************
    > File Name: ludo.cpp
    > Author: 
    > Mail: 
    > Created Time: Tue 06 Apr 2021 03:09:20 PM CST
 ************************************************************************/

#include "cstdlib"
#include "ludo.h"
#include "MinimalPerfectCuckoo/minimal_perfect_cuckoo.h"

void ludo(Key* keys, Val* values, uint32_t entryCount, uint32_t ludoSize, ExportLudo* exportLudo) {
    ControlPlaneMinimalPerfectCuckoo<Key, Val, Vlen> cp(ludoSize);

    for (int idx = 0; idx < entryCount; idx++) {
        cp.insert(keys[idx], values[idx]);
    }

    cp.prepareToExport();

    DataPlaneMinimalPerfectCuckoo<Key, Val, Vlen> dp(cp, &exportLudo->bucket_seeds, &exportLudo->buckets);
    exportLudo->bucket_index_seed = dp.h.s & 0xFF;
    exportLudo->bucket_locator_seed = dp.locator.hab.s & 0xFF;
    exportLudo->bucket_locator_a_len = dp.locator.ma;
    exportLudo->bucket_locator_b_len = dp.locator.mb;
    exportLudo->bucket_num = dp.num_buckets_;

    printf("Bucket number: %u\n", dp.num_buckets_);
    printf("Cuckoo seed: 0x%02hx\n", *((uint8_t *)&dp.h.s));
    printf("Othello seed: 0x%02hx\n", *((uint8_t *)&dp.locator.hab.s));

    /*
     * uint32_t checksum = 0;
     * for (int idx = 0; idx < dp.num_buckets_; idx++) {
     *     DataPlaneMinimalPerfectCuckoo<Key, Val, Vlen>::Bucket bucket;
     *     bucket = dp.readBucket(idx);
     *     printf(
     *         "Bucket %5d -- Seed: 0x%02x -- Slots: %5u%5u%5u%5u\n", idx, bucket.seed,
     *         bucket.values[0], bucket.values[1], bucket.values[2], bucket.values[3]
     *     );
     *     checksum += bucket.values[0];
     *     checksum += bucket.values[1];
     *     checksum += bucket.values[2];
     *     checksum += bucket.values[3];
     * }
     * printf("Checksum: %u\n", checksum);
     * 
     * printf("Othello Bitarray A Len: %d\n", dp.locator.ma);
     * printf("Othello Bitarray B Len: %d\n", dp.locator.mb);
     * // dp.lookUp(k, v);
     * // printf("LookUp Test: Key %u - Value %u\n", k, v);
     */
}
