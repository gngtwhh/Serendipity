/**
 * @file: md5.h
 * @description: This is a header file that contains the declaration of MD4 algorithm.
 * @author: WAHAHA
 * @Date: 2024/4/11 14:52
 * @LastEditTime: 2024/4/11 14:52
 * @FilePath: Serendipity/include/digest/md4.h
 * @category: digest-algorithm
 */

#ifndef SERENDIPITY_MD4_H
#define SERENDIPITY_MD4_H

/* pre-initialization of encode */
#include "digest/digest_pre_init.h"

/* basic md4 data size */
#define MD4_DIGEST_SIZE 16

/* md4 auxiliary functions */
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (y)) | ((x) & (z)) | ((y) & (z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))

#define FF(a, b, c, d, mi, s) \
    (a = ( CYCLE_SHL_SIZE_NBIT(a + F(b, c, d) + mi, s, uint32_t)))
#define GG(a, b, c, d, mj, s) \
    (a = ( CYCLE_SHL_SIZE_NBIT(a + G(b, c, d) + mj + 0x5A827999, s, uint32_t)))
#define HH(a, b, c, d, mj, s) \
    (a = ( CYCLE_SHL_SIZE_NBIT(a + H(b, c, d) + mj + 0x6ED9EBA1, s, uint32_t)))

/* md4 function */
uint32_t *md4_padding(const byte *data, size_t data_bit_count, size_t *block_size);

status md4(const byte *data, size_t data_bit_size, char *digest);

#endif //SERENDIPITY_MD4_H
