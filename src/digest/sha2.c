/**
 * @file: sha2.c
 * @description: This is a source file that contains the implementation of xxx
 * @author: WAHAHA
 * @Date: 2024/4/16 14:50
 * @FilePath: Serendipity/src/digest/sha2.c
 * @category:
 */

#include <digest/sha2.h>
#include <string.h>
#include "misc/bitwise_utils.h"
#include "misc/endian.h"

/* sha224 and sha256 logic functions */
#define SHA256_CH(x, y, z)  (((x) & (y)) ^ ((~(x)) & (z)))
#define SHA256_MAJ(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define SHA256_BSIG0(x) \
    (CYCLE_SHR_SIZE_NBIT(x,2 ,uint32_t) ^ CYCLE_SHR_SIZE_NBIT(x,13,uint32_t) ^ CYCLE_SHR_SIZE_NBIT(x,22,uint32_t))
#define SHA256_BSIG1(x) \
    (CYCLE_SHR_SIZE_NBIT(x,6 ,uint32_t) ^ CYCLE_SHR_SIZE_NBIT(x,11,uint32_t) ^ CYCLE_SHR_SIZE_NBIT(x,25,uint32_t))
#define SHA256_SSIG0(x) \
    (CYCLE_SHR_SIZE_NBIT(x,7 ,uint32_t) ^ CYCLE_SHR_SIZE_NBIT(x,18,uint32_t) ^ SHR_NBIT(x,3 ))
#define SHA256_SSIG1(x) \
    (CYCLE_SHR_SIZE_NBIT(x,17,uint32_t) ^ CYCLE_SHR_SIZE_NBIT(x,19,uint32_t) ^ SHR_NBIT(x,10))

/* sha384, sha512, sha512/224, sha512/256 logic functions */
#define SHA512_CH(x, y, z)  (((x) & (y)) ^ ((~(x)) & (z)))
#define SHA512_MAJ(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define SHA512_BSIG0(x) \
    (CYCLE_SHR_SIZE_NBIT(x,28,uint64_t) ^ CYCLE_SHR_SIZE_NBIT(x,34,uint64_t) ^ CYCLE_SHR_SIZE_NBIT(x,39,uint64_t))
#define SHA512_BSIG1(x) \
    (CYCLE_SHR_SIZE_NBIT(x,14,uint64_t) ^ CYCLE_SHR_SIZE_NBIT(x,18,uint64_t) ^ CYCLE_SHR_SIZE_NBIT(x,41,uint64_t))
#define SHA512_SSIG0(x) \
    (CYCLE_SHR_SIZE_NBIT(x,1 ,uint64_t) ^ CYCLE_SHR_SIZE_NBIT(x,8 ,uint64_t) ^ SHR_NBIT(x,7 ))
#define SHA512_SSIG1(x) \
    (CYCLE_SHR_SIZE_NBIT(x,19,uint64_t) ^ CYCLE_SHR_SIZE_NBIT(x,61,uint64_t) ^ SHR_NBIT(x,6 ))

/* 128-bit word operations */
static uint128_t uint128_add_uint64(uint128_t a, uint64_t b) {
    uint64_t low = (a.low + b) & 0xffffffffffffffff;
    if (low < a.low) {
        a.high++;
    }
    a.low = low;
    return a;
}

/* sha224 and sha256 constants */
static const uint32_t SHA256_K[64] = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

/* sha384 and sha512 constants */
static const uint64_t SHA512_K[80] = {
        0x428A2F98D728AE22, 0x7137449123EF65CD, 0xB5C0FBCFEC4D3B2F, 0xE9B5DBA58189DBBC,
        0x3956C25BF348B538, 0x59F111F1B605D019, 0x923F82A4AF194F9B, 0xAB1C5ED5DA6D8118,
        0xD807AA98A3030242, 0x12835B0145706FBE, 0x243185BE4EE4B28C, 0x550C7DC3D5FFB4E2,
        0x72BE5D74F27B896F, 0x80DEB1FE3B1696B1, 0x9BDC06A725C71235, 0xC19BF174CF692694,
        0xE49B69C19EF14AD2, 0xEFBE4786384F25E3, 0x0FC19DC68B8CD5B5, 0x240CA1CC77AC9C65,
        0x2DE92C6F592B0275, 0x4A7484AA6EA6E483, 0x5CB0A9DCBD41FBD4, 0x76F988DA831153B5,
        0x983E5152EE66DFAB, 0xA831C66D2DB43210, 0xB00327C898FB213F, 0xBF597FC7BEEF0EE4,
        0xC6E00BF33DA88FC2, 0xD5A79147930AA725, 0x06CA6351E003826F, 0x142929670A0E6E70,
        0x27B70A8546D22FFC, 0x2E1B21385C26C926, 0x4D2C6DFC5AC42AED, 0x53380D139D95B3DF,
        0x650A73548BAF63DE, 0x766A0ABB3C77B2A8, 0x81C2C92E47EDAEE6, 0x92722C851482353B,
        0xA2BFE8A14CF10364, 0xA81A664BBC423001, 0xC24B8B70D0F89791, 0xC76C51A30654BE30,
        0xD192E819D6EF5218, 0xD69906245565A910, 0xF40E35855771202A, 0x106AA07032BBD1B8,
        0x19A4C116B8D2D0C8, 0x1E376C085141AB53, 0x2748774CDF8EEB99, 0x34B0BCB5E19B48A8,
        0x391C0CB3C5C95A63, 0x4ED8AA4AE3418ACB, 0x5B9CCA4F7763E373, 0x682E6FF3D6B2B8A3,
        0x748F82EE5DEFB2FC, 0x78A5636F43172F60, 0x84C87814A1F0AB72, 0x8CC702081A6439EC,
        0x90BEFFFA23631E28, 0xA4506CEBDE82BDE9, 0xBEF9A3F7B2C67915, 0xC67178F2E372532B,
        0xCA273ECEEA26619C, 0xD186B8C721C0C207, 0xEADA7DD6CDE0EB1E, 0xF57D4F7FEE6ED178,
        0x06F067AA72176FBA, 0x0A637DC5A2C898A6, 0x113F9804BEF90DAE, 0x1B710B35131C471B,
        0x28DB77F523047D84, 0x32CAAB7B40C72493, 0x3C9EBE0A15C9BEBC, 0x431D67C49C100D4C,
        0x4CC5D4BECB3E42B6, 0x597F299CFC657E2A, 0x5FCB6FAB3AD6FAEC, 0x6C44198C4A475817
};

/* sha2 functions */
/**
 * @Funticon name: sha2_init
 * @description: This function is used to initialize the sha2 context.
 * @Author: WAHAHA
 * @Date: 2024-5-17 9:4:31
 * @Note: None
 * @param {sha2_ctx *} ctx: The sha2 context.
 * @param {SHA2_MODE} mode: The sha2 mode.
 * @return {status}: The status of the sha2 initialization.
 */
status sha2_init(sha2_ctx *ctx, SHA2_MODE mode) {
    ASSERT(ctx != NULL, error);
    ASSERT(mode >= SHA224 && mode <= SHA512_256, error);
    ctx->mode = mode;
    ctx->data_len = 0;
    ctx->bit_len = 0;
    ctx->total_len.high = 0;
    ctx->total_len.low = 0;

    switch (mode) {
        case SHA224:
            ctx->state.s32[0] = 0xc1059ed8;
            ctx->state.s32[1] = 0x367cd507;
            ctx->state.s32[2] = 0x3070dd17;
            ctx->state.s32[3] = 0xf70e5939;
            ctx->state.s32[4] = 0xffc00b31;
            ctx->state.s32[5] = 0x68581511;
            ctx->state.s32[6] = 0x64f98fa7;
            ctx->state.s32[7] = 0xbefa4fa4;
            ctx->buffer_len = 64;
            break;
        case SHA256:
            ctx->state.s32[0] = 0x6a09e667;
            ctx->state.s32[1] = 0xbb67ae85;
            ctx->state.s32[2] = 0x3c6ef372;
            ctx->state.s32[3] = 0xa54ff53a;
            ctx->state.s32[4] = 0x510e527f;
            ctx->state.s32[5] = 0x9b05688c;
            ctx->state.s32[6] = 0x1f83d9ab;
            ctx->state.s32[7] = 0x5be0cd19;
            ctx->buffer_len = 64;
            break;
        case SHA384:
            ctx->state.s64[0] = 0xcbbb9d5dc1059ed8;
            ctx->state.s64[1] = 0x629a292a367cd507;
            ctx->state.s64[2] = 0x9159015a3070dd17;
            ctx->state.s64[3] = 0x152fecd8f70e5939;
            ctx->state.s64[4] = 0x67332667ffc00b31;
            ctx->state.s64[5] = 0x8eb44a8768581511;
            ctx->state.s64[6] = 0xdb0c2e0d64f98fa7;
            ctx->state.s64[7] = 0x47b5481dbefa4fa4;
            ctx->buffer_len = 128;
            break;
        case SHA512:
            ctx->state.s64[0] = 0x6a09e667f3bcc908;
            ctx->state.s64[1] = 0xbb67ae8584caa73b;
            ctx->state.s64[2] = 0x3c6ef372fe94f82b;
            ctx->state.s64[3] = 0xa54ff53a5f1d36f1;
            ctx->state.s64[4] = 0x510e527fade682d1;
            ctx->state.s64[5] = 0x9b05688c2b3e6c1f;
            ctx->state.s64[6] = 0x1f83d9abfb41bd6b;
            ctx->state.s64[7] = 0x5be0cd19137e2179;
            ctx->buffer_len = 128;
            break;
        case SHA512_224:
            ctx->state.s64[0] = 0x8C3D37C819544DA2;
            ctx->state.s64[1] = 0x73E1996689DCD4D6;
            ctx->state.s64[2] = 0x1DFAB7AE32FF9C82;
            ctx->state.s64[3] = 0x679DD514582F9FCF;
            ctx->state.s64[4] = 0x0F6D2B697BD44DA8;
            ctx->state.s64[5] = 0x77E36F7304C48942;
            ctx->state.s64[6] = 0x3F9D85A86A1D36C8;
            ctx->state.s64[7] = 0x1112E6AD91D692A1;
            ctx->buffer_len = 128;
            break;
        case SHA512_256:
            ctx->state.s64[0] = 0x22312194fc2bf72c;
            ctx->state.s64[1] = 0x9f555fa3c84c64c2;
            ctx->state.s64[2] = 0x2393b86b6f53b151;
            ctx->state.s64[3] = 0x963877195940eabd;
            ctx->state.s64[4] = 0x96283ee2a88effe3;
            ctx->state.s64[5] = 0xbe5e1e2553863992;
            ctx->state.s64[6] = 0x2b0199fc2c85b8aa;
            ctx->state.s64[7] = 0x0eb72ddc81c52ca2;
            ctx->buffer_len = 128;
            break;
    }
    return true;
}

/**
 * @Funticon name: sha2_update
 * @description: This function is used to update the sha2 context with the data.
 * @Author: WAHAHA
 * @Date: 2024-5-17 9:44:8
 * @Note: None
 * @param {sha2_ctx *} ctx: The sha2 context.
 * @param {const byte *} data: The data to be processed.
 * @param {size_t} data_len: The size of the data.
 * @return {status}: The status of the sha2 update.
 */
status sha2_update(sha2_ctx *ctx, const byte *data, size_t data_len) {
    ASSERT(ctx != NULL, error);
    ASSERT(data != NULL, error);
    ASSERT(data_len > 0, error);

    size_t i;
    size_t space = ctx->buffer_len; // total space of the buffer, depending on the mode(64 or 128)
    for (i = 0; i < data_len; i++) {
        if (ctx->mode == SHA224 || ctx->mode == SHA256) {
            ctx->buffer.buf32[ctx->data_len] = data[i];
            ctx->data_len++;
            if (ctx->data_len == space) {
                sha224_256_transform(ctx, ctx->buffer.buf32);
                ctx->bit_len += space * 8;
                ctx->data_len = 0;
            }
        } else {
            ctx->buffer.buf64[ctx->data_len] = data[i];
            ctx->data_len++;
            if (ctx->data_len == space) {
                sha384_512_transform(ctx, ctx->buffer.buf64);
                ctx->total_len = uint128_add_uint64(ctx->total_len, (uint64_t) (space) * 8);
                ctx->data_len = 0;
            }
        }

    }
    return true;
}

/**
 * @Funticon name: sha2_final
 * @description: This function is used to finalize the sha2 context and get the digest.
 * @Author: WAHAHA
 * @Date: 2024-5-17 9:59:24
 * @Note: None
 * @param {sha2_ctx *} ctx: The sha2 context.
 * @param {char *} digest: The digest.
 * @return {status}: The status of the sha2 finalization.
 */
status sha2_final(sha2_ctx *ctx, byte *digest) {
    ASSERT(ctx != NULL, error);
    ASSERT(digest != NULL, error);

//    size_t space = ctx->buffer_len; // total space of the buffer, depending on the mode(64 or 128)
    size_t i = ctx->data_len;
    /* pad the data in the buffer */
    if (ctx->mode == SHA224 || ctx->mode == SHA256) {
        // SHA224 and SHA256
        if (i < 56) {
            ctx->buffer.buf32[i++] = 0x80;
            while (i < 56) {
                ctx->buffer.buf32[i++] = 0x00;
            }
        } else {
            ctx->buffer.buf32[i++] = 0x80;
            while (i < 64) {
                ctx->buffer.buf32[i++] = 0x00;
            }
            sha224_256_transform(ctx, ctx->buffer.buf32);
            memset(ctx->buffer.buf32, 0, 56);
        }
        ctx->bit_len += ctx->data_len * 8;
        ctx->buffer.buf32[56] = (ctx->bit_len >> 56) & 0xff;
        ctx->buffer.buf32[57] = (ctx->bit_len >> 48) & 0xff;
        ctx->buffer.buf32[58] = (ctx->bit_len >> 40) & 0xff;
        ctx->buffer.buf32[59] = (ctx->bit_len >> 32) & 0xff;
        ctx->buffer.buf32[60] = (ctx->bit_len >> 24) & 0xff;
        ctx->buffer.buf32[61] = (ctx->bit_len >> 16) & 0xff;
        ctx->buffer.buf32[62] = (ctx->bit_len >> 8) & 0xff;
        ctx->buffer.buf32[63] = ctx->bit_len & 0xff;
        sha224_256_transform(ctx, ctx->buffer.buf32);
    } else {
        // SHA384 and SHA512 and SHA512_224 and SHA512_256
        if (i < 112) {
            ctx->buffer.buf64[i++] = 0x80;
            while (i < 112) {
                ctx->buffer.buf64[i++] = 0x00;
            }
        } else {
            ctx->buffer.buf64[i++] = 0x80;
            while (i < 128) {
                ctx->buffer.buf64[i++] = 0x00;
            }
            sha384_512_transform(ctx, ctx->buffer.buf64);
            memset(ctx->buffer.buf64, 0, 112);
        }
        ctx->total_len = uint128_add_uint64(ctx->total_len, (uint64_t) (ctx->data_len) * 8);
        ctx->buffer.buf64[112] = (ctx->total_len.high >> 56) & 0xff;
        ctx->buffer.buf64[113] = (ctx->total_len.high >> 48) & 0xff;
        ctx->buffer.buf64[114] = (ctx->total_len.high >> 40) & 0xff;
        ctx->buffer.buf64[115] = (ctx->total_len.high >> 32) & 0xff;
        ctx->buffer.buf64[116] = (ctx->total_len.high >> 24) & 0xff;
        ctx->buffer.buf64[117] = (ctx->total_len.high >> 16) & 0xff;
        ctx->buffer.buf64[118] = (ctx->total_len.high >> 8) & 0xff;
        ctx->buffer.buf64[119] = ctx->total_len.high & 0xff;
        ctx->buffer.buf64[120] = (ctx->total_len.low >> 56) & 0xff;
        ctx->buffer.buf64[121] = (ctx->total_len.low >> 48) & 0xff;
        ctx->buffer.buf64[122] = (ctx->total_len.low >> 40) & 0xff;
        ctx->buffer.buf64[123] = (ctx->total_len.low >> 32) & 0xff;
        ctx->buffer.buf64[124] = (ctx->total_len.low >> 24) & 0xff;
        ctx->buffer.buf64[125] = (ctx->total_len.low >> 16) & 0xff;
        ctx->buffer.buf64[126] = (ctx->total_len.low >> 8) & 0xff;
        ctx->buffer.buf64[127] = ctx->total_len.low & 0xff;
        sha384_512_transform(ctx, ctx->buffer.buf64);
    }

    // copy the digest
    // @Note: Since the SHA use big-endian,
    // transform the hash value from big-endian to little-endian
    switch (ctx->mode) {
        case SHA224:
            for (i = 0; i < 7; ++i)
                BE_UINT32_TO_BYTES((byte *) digest + i * 4, ctx->state.s32[i]);
            break;
        case SHA256:
            for (i = 0; i < 8; ++i)
                BE_UINT32_TO_BYTES((byte *) digest + i * 4, ctx->state.s32[i]);
            break;
        case SHA384:
            for (i = 0; i < 6; ++i)
                BE_UINT64_TO_BYTES((byte *) digest + i * 8, ctx->state.s64[i]);
            break;
        case SHA512:
            for (i = 0; i < 8; ++i)
                BE_UINT64_TO_BYTES((byte *) digest + i * 8, ctx->state.s64[i]);
            break;
        case SHA512_224:
            for (i = 0; i < 3; ++i)
                BE_UINT64_TO_BYTES((byte *) digest + i * 8, ctx->state.s64[i]);
            uint32_t temp = ctx->state.s64[3] >> 32;
            BE_UINT32_TO_BYTES((byte *) digest + 24, temp);
            break;
        case SHA512_256:
            for (i = 0; i < 4; ++i)
                BE_UINT64_TO_BYTES((byte *) digest + i * 8, ctx->state.s64[i]);
            break;
    }
    return true;
}

/* sha2 transform functions */
/**
 * @Funticon name: sha224_256_transform
 * @description: Do one SHA-224/256 transformation, processing a 32-byte chunk.
 * @Author: WAHAHA
 * @Date: 2024-5-23 21:2:4
 * @Note: None
 * @param {sha2_ctx *} ctx: the SHA-224/256 context
 * @param {const byte *} data: the data to be transformed
 * @return {void}
 */
static void sha224_256_transform(sha2_ctx *ctx, const byte *data) {
    uint32_t a, b, c, d, e, f, g, h, m[64];
    uint32_t t1, t2;

    /* Initialize the first 16 words in the array m */
    for (int i = 0, j = 0; i < 16; ++i, j += 4) {
        m[i] = (data[j] << 24) | (data[j + 1] << 16) | (data[j + 2] << 8) | (data[j + 3]);
    }
    for (int i = 16; i < 64; ++i) {
        m[i] = SHA256_SSIG1(m[i - 2]) + m[i - 7] + SHA256_SSIG0(m[i - 15]) + m[i - 16];
    }

    /* Initialize the working variables */
    a = ctx->state.s32[0];
    b = ctx->state.s32[1];
    c = ctx->state.s32[2];
    d = ctx->state.s32[3];
    e = ctx->state.s32[4];
    f = ctx->state.s32[5];
    g = ctx->state.s32[6];
    h = ctx->state.s32[7];

    /* The main loop */
    for (int i = 0; i < 64; ++i) {
        t1 = h + SHA256_BSIG1(e) + SHA256_CH(e, f, g) + SHA256_K[i] + m[i];
        t2 = SHA256_BSIG0(a) + SHA256_MAJ(a, b, c);
        h = g;
        g = f;
        f = e;
        e = d + t1;
        d = c;
        c = b;
        b = a;
        a = t1 + t2;
    }

    /* Add the working variables back into the state */
    ctx->state.s32[0] += a;
    ctx->state.s32[1] += b;
    ctx->state.s32[2] += c;
    ctx->state.s32[3] += d;
    ctx->state.s32[4] += e;
    ctx->state.s32[5] += f;
    ctx->state.s32[6] += g;
    ctx->state.s32[7] += h;
}

/**
 * @Funticon name: sha384_512_transform
 * @description: Do one SHA-384/512 transformation, processing a 64-byte chunk.
 * @Author: WAHAHA
 * @Date: 2024-5-27 19:53:41
 * @Note: None
 * @param {sha2_ctx *} ctx: the SHA-384/512 context
 * @param {const byte *} data: the data to be transformed
 * @return {void}
 */
static void sha384_512_transform(sha2_ctx *ctx, const byte *data) {
    uint64_t a, b, c, d, e, f, g, h, m[80];
    uint64_t t1, t2;

    /* Initialize the first 16 words in the array m */
    for (int i = 0, j = 0; i < 16; ++i, j += 8) {
        m[i] = ((uint64_t) data[j] << 56) | ((uint64_t) data[j + 1] << 48)
               | ((uint64_t) data[j + 2] << 40) | ((uint64_t) data[j + 3] << 32)
               | ((uint64_t) data[j + 4] << 24) | ((uint64_t) data[j + 5] << 16)
               | ((uint64_t) data[j + 6] << 8) | ((uint64_t) data[j + 7]);
    }
    for (int i = 16; i < 80; ++i) {
        m[i] = SHA512_SSIG1(m[i - 2]) + m[i - 7] + SHA512_SSIG0(m[i - 15]) + m[i - 16];
    }

    /* Initialize the working variables */
    a = ctx->state.s64[0];
    b = ctx->state.s64[1];
    c = ctx->state.s64[2];
    d = ctx->state.s64[3];
    e = ctx->state.s64[4];
    f = ctx->state.s64[5];
    g = ctx->state.s64[6];
    h = ctx->state.s64[7];

    /* The main loop */
    for (int i = 0; i < 80; ++i) {
        t1 = h + SHA512_BSIG1(e) + SHA512_CH(e, f, g) + SHA512_K[i] + m[i];
        t2 = SHA512_BSIG0(a) + SHA512_MAJ(a, b, c);
        h = g;
        g = f;
        f = e;
        e = d + t1;
        d = c;
        c = b;
        b = a;
        a = t1 + t2;
    }

    /* Add the working variables back into the state */
    ctx->state.s64[0] += a;
    ctx->state.s64[1] += b;
    ctx->state.s64[2] += c;
    ctx->state.s64[3] += d;
    ctx->state.s64[4] += e;
    ctx->state.s64[5] += f;
    ctx->state.s64[6] += g;
    ctx->state.s64[7] += h;
}
