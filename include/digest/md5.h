/**
 * @file: md5.h
 * @description: This is a header file that contains the declaration of MD5 algorithm.
 * @author: WAHAHA
 * @Date: 2024/4/7 9:36
 * @LastEditTime: 2024/4/7 9:36
 * @FilePath: Serendipity/include/digest/md5.h
 * @category: digest-algorithm
 */

#ifndef SERENDIPITY_MD5_H
#define SERENDIPITY_MD5_H

/* pre-initialization of digest */
#include "digest/digest_pre_init.h"

/* basic md5 data size */
#define MD5_DIGEST_SIZE 16

/* md5 data */
/* // The table that is used to calculate the md5
 * static const uint32_t T[64] = {
        0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
        0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
        0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
        0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
        0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
        0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
        0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
        0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
        0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
        0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
        0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
        0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
        0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
        0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
        0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
        0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};*/

/* md5 auxiliary functions */
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

#define FF(a, b, c, d, mj, s, ti) \
    (a = b + ( CYCLE_SHL_SIZE_NBIT(a + F(b, c, d) + mj + ti, s, uint32_t)))
#define GG(a, b, c, d, mj, s, ti) \
    (a = b + ( CYCLE_SHL_SIZE_NBIT(a + G(b, c, d) + mj + ti, s, uint32_t)))
#define HH(a, b, c, d, mj, s, ti) \
    (a = b + ( CYCLE_SHL_SIZE_NBIT(a + H(b, c, d) + mj + ti, s, uint32_t)))
#define II(a, b, c, d, mj, s, ti) \
    (a = b + ( CYCLE_SHL_SIZE_NBIT(a + I(b, c, d) + mj + ti, s, uint32_t)))

/* md5 function */
static uint32_t *md5_padding(const byte *data, size_t data_bit_count, size_t *block_size);

status md5(const byte *data, size_t data_bit_size, char *digest);

#endif //SERENDIPITY_MD5_H
