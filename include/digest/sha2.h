/**
 * @file: sha2.h
 * @description: This is a header file that contains the declaration of SHA-2 algorithm.
 * @author: WAHAHA
 * @Date: 2024/4/16 14:48
 * @FilePath: Serendipity/include/digest/sha2.h
 * @category: digest-algorithm
 */

/****************************************************************
 * Module Name: SHA-2
 * Description: This module provides the implementation of SHA-2 algorithm.
 * Inclusive functions:
 *     SHA-224, SHA-256, SHA-384
 *     SHA-512, SHA-512/224, SHA-512/256
 * RFC Reference: https://www.rfc-editor.org/info/rfc6234
 * NIST Reference: https://csrc.nist.gov/pubs/fips/180-4/upd1/final
 ***************************************************************/

#ifndef SERENDIPITY_SHA2_H
#define SERENDIPITY_SHA2_H

/* pre-initialization of digest */
#include "digest/digest_pre_init.h"

/* basic sha2 data size */
#define SHA224_DIGEST_SIZE 28
#define SHA256_DIGEST_SIZE 32
#define SHA384_DIGEST_SIZE 48
#define SHA512_DIGEST_SIZE 64
#define SHA512_224_DIGEST_SIZE 28
#define SHA512_256_DIGEST_SIZE 32

/* 128-bit word structure */
typedef struct {
    uint64_t high, low;
} uint128_t;
/* 128-bit word operations */
static uint128_t uint128_add_uint64(uint128_t a, uint64_t b);

/* SHA-2 mode */
typedef enum {
    SHA224 = 0,
    SHA256,
    SHA384,
    SHA512,
    SHA512_224,
    SHA512_256
} SHA2_MODE;

/* SHA-2 Context */
typedef struct {
    SHA2_MODE mode; // SHA-2 mode
    uint32_t buffer_len; // buffer length
    uint32_t data_len; // data length
    uint64_t bit_len; // bit length
    uint128_t total_len; // bit length for 512-bit hash
    union {
        uint32_t s32[8]; // 32-bit hash value
        uint64_t s64[8]; // 64-bit hash value
    } state;
    union {
        byte buf32[64]; // 32-bit buffer
        byte buf64[128]; // 64-bit buffer
    } buffer;
} sha2_ctx;

/* sha2 functions */
status sha2_init(sha2_ctx *ctx, SHA2_MODE mode);
status sha2_update(sha2_ctx *ctx, const byte *data, size_t data_len);
status sha2_final(sha2_ctx *ctx, byte *digest);

/* sha2 transform functions */
static void sha224_256_transform(sha2_ctx *ctx, const byte *data);
static void sha384_512_transform(sha2_ctx *ctx, const byte *data);

#endif //SERENDIPITY_SHA2_H
