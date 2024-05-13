/**
 * @file: md4.c
 * @description: This is a source file that contains the implementation of MD4 algorithm.
 * @author: WAHAHA
 * @Date: 2024/4/11 14:52
 * @FilePath: Serendipity/src/encode/md4.c
 * @category: encode-algorithm
 */

#include <stdlib.h>
#include "digest/md4.h"
#include "encode/hex.h"
#include "misc/endian.h"

/* set [j,j-1,...,i] bits to 1 */
#define set_mask(i, j) (((1u << ((j) - (i) + 1)) - 1) << (i))

/**
 * @Funticon name: md4_padding
 * @description: This function is used to pad the data to a multiple of 512 bits.
 * @Author: WAHAHA
 * @Date: 2024/4/11 14:52
 * @Note: Every 8-bits is interpreted as a byte with the high-order bit first.
 * @param {const byte *} data: The data to be processed.
 * @param {size_t} data_bit_count: The size of the data in bits.
 * @param {size_t *} block_size: The block count after padding.
 * @return {uint32_t *}: The data after padding.
 */
static uint32_t *md4_padding(const byte *data, size_t data_bit_count, size_t *block_count) {
    /* calculate the number of bytes */
    size_t data_byte_size = (data_bit_count + 7) / 8;
    /* calculate the number of the data after padding in blocks */
    *block_count = (data_bit_count + 64 + 511) / 512;
    /* calculate the number of the data after padding in uint32_t */
    size_t data_size = *block_count * 16;
    /* allocate memory for the data after padding */
    uint32_t *data_padding = (uint32_t *) calloc(data_size, sizeof(uint32_t));

    /* copy the original data to the data after padding with the low-order byte given first */
    for (size_t i = 0; i < data_byte_size; i++) {
        data_padding[i >> 2] |= data[i] << (i % 4 * 8);
    }
    /* clear the extra bits of the last byte */
    if (data_bit_count % 8 != 0) {
        data_padding[data_byte_size >> 2] &= ~set_mask(
                (data_byte_size % 4 - 1) * 8,
                (data_byte_size % 4) * 8 - (data_bit_count % 8) - 1);
    }

    /* add the 1 bit */
    // 0x80 = 10000000
    // (data_bit_count % 8) : the number of bits in the last byte
    if (data_bit_count % 8 == 0) {
        data_padding[data_byte_size >> 2] |= 0x80
                << ((data_byte_size % 4) * 8);
    } else {
        data_padding[data_byte_size >> 2] |= 0x80
                << ((data_byte_size % 4 - 1) * 8 - data_bit_count % 8);
    }
    /* add the length */
    uint64_t data_length = data_bit_count;
    data_padding[*block_count * 16 - 2] = data_length & 0xffffffff;
    data_padding[*block_count * 16 - 1] = (data_length >> 32) & 0xffffffff;

    return data_padding;
}

/**
 * @Funticon name: md4
 * @description: This function is used to calculate the MD4 hash value of the data.
 * @Author: WAHAHA
 * @Date: 2024/4/11 14:52
 * @Note: md4() will pad the data to a multiple of 512 bits.
 * @param {const byte *} data: The data to be processed.
 * @param {size_t} data_bit_size: The size of the data in bits.
 * @return {status}: The status of the function execution.
 */
status md4(const byte *data, size_t data_bit_size, char *digest) {
    /* check the input data */
    ASSERT(data != NULL, error);
    ASSERT(digest != NULL, error);
    ASSERT(data_bit_size > 0, error);

    /* padding the data */
    size_t block_count = 0;
    uint32_t *data_padding = md4_padding(data, data_bit_size, &block_count);

    /* initialize the md4 register */
    // low-order byte first
    uint32_t A = 0x67452301;
    uint32_t B = 0xefcdab89;
    uint32_t C = 0x98badcfe;
    uint32_t D = 0x10325476;

    /* main loop */
    for (size_t i = 0; i < block_count; i++) {
        /* copy the md4 register */
        uint32_t AA = A;
        uint32_t BB = B;
        uint32_t CC = C;
        uint32_t DD = D;

        /* ROUND 1 */
        FF(A, B, C, D, data_padding[i * 16 + 0], 3);
        FF(D, A, B, C, data_padding[i * 16 + 1], 7);
        FF(C, D, A, B, data_padding[i * 16 + 2], 11);
        FF(B, C, D, A, data_padding[i * 16 + 3], 19);

        FF(A, B, C, D, data_padding[i * 16 + 4], 3);
        FF(D, A, B, C, data_padding[i * 16 + 5], 7);
        FF(C, D, A, B, data_padding[i * 16 + 6], 11);
        FF(B, C, D, A, data_padding[i * 16 + 7], 19);

        FF(A, B, C, D, data_padding[i * 16 + 8], 3);
        FF(D, A, B, C, data_padding[i * 16 + 9], 7);
        FF(C, D, A, B, data_padding[i * 16 + 10], 11);
        FF(B, C, D, A, data_padding[i * 16 + 11], 19);

        FF(A, B, C, D, data_padding[i * 16 + 12], 3);
        FF(D, A, B, C, data_padding[i * 16 + 13], 7);
        FF(C, D, A, B, data_padding[i * 16 + 14], 11);
        FF(B, C, D, A, data_padding[i * 16 + 15], 19);
        /* ROUND 2 */
        GG(A, B, C, D, data_padding[i * 16 + 0], 3);
        GG(D, A, B, C, data_padding[i * 16 + 4], 5);
        GG(C, D, A, B, data_padding[i * 16 + 8], 9);
        GG(B, C, D, A, data_padding[i * 16 + 12], 13);

        GG(A, B, C, D, data_padding[i * 16 + 1], 3);
        GG(D, A, B, C, data_padding[i * 16 + 5], 5);
        GG(C, D, A, B, data_padding[i * 16 + 9], 9);
        GG(B, C, D, A, data_padding[i * 16 + 13], 13);

        GG(A, B, C, D, data_padding[i * 16 + 2], 3);
        GG(D, A, B, C, data_padding[i * 16 + 6], 5);
        GG(C, D, A, B, data_padding[i * 16 + 10], 9);
        GG(B, C, D, A, data_padding[i * 16 + 14], 13);

        GG(A, B, C, D, data_padding[i * 16 + 3], 3);
        GG(D, A, B, C, data_padding[i * 16 + 7], 5);
        GG(C, D, A, B, data_padding[i * 16 + 11], 9);
        GG(B, C, D, A, data_padding[i * 16 + 15], 13);
        /* ROUND 3 */
        HH(A, B, C, D, data_padding[i * 16 + 0], 3);
        HH(D, A, B, C, data_padding[i * 16 + 8], 9);
        HH(C, D, A, B, data_padding[i * 16 + 4], 11);
        HH(B, C, D, A, data_padding[i * 16 + 12], 15);

        HH(A, B, C, D, data_padding[i * 16 + 2], 3);
        HH(D, A, B, C, data_padding[i * 16 + 10], 9);
        HH(C, D, A, B, data_padding[i * 16 + 6], 11);
        HH(B, C, D, A, data_padding[i * 16 + 14], 15);

        HH(A, B, C, D, data_padding[i * 16 + 1], 3);
        HH(D, A, B, C, data_padding[i * 16 + 9], 9);
        HH(C, D, A, B, data_padding[i * 16 + 5], 11);
        HH(B, C, D, A, data_padding[i * 16 + 13], 15);

        HH(A, B, C, D, data_padding[i * 16 + 3], 3);
        HH(D, A, B, C, data_padding[i * 16 + 11], 9);
        HH(C, D, A, B, data_padding[i * 16 + 7], 11);
        HH(B, C, D, A, data_padding[i * 16 + 15], 15);

        /* update the md4 register */
        A += AA;
        B += BB;
        C += CC;
        D += DD;
    }

    /* free the memory */
    free(data_padding);

    /* generate the digest */
    byte temp_result[16] = {0};
    LE_UINT32_TO_BYTES(&temp_result[0], A);
    LE_UINT32_TO_BYTES(&temp_result[4], B);
    LE_UINT32_TO_BYTES(&temp_result[8], C);
    LE_UINT32_TO_BYTES(&temp_result[12], D);

    size_t out_len = 0;
    bytes_to_hex(temp_result, 16, digest, &out_len);

    digest[32] = '\0';

    return true;
}