/**
 * @file: md5.c
 * @description: This is a source file that contains the implementation of MD5 algorithm.
 * @author: WAHAHA
 * @Date: 2024/4/7 10:30
 * @FilePath: Serendipity/src/encode/md5.c
 * @category: encode-algorithm
 */

#include <stdlib.h>
#include <encode/md5.h>
#include <encode/hex.h>
#include <misc/endian.h>

#define set_mask_u32(i, j) (((1u << ((j) - (i) + 1)) - 1) << (i))

/**
 * @Funticon name: md5_padding
 * @description: This function is used to pad the data to a multiple of 512 bits.
 * @Author: WAHAHA
 * @Date: 2024-4-7 10:32:27
 * @Note: Every 8-bits is interpreted as a byte with the high-order bit first.
 * @param {const byte *} data: The data to be processed.
 * @param {size_t} data_bit_count: The size of the data in bits.
 * @param {size_t *} block_size: The block count after padding.
 * @return {uint32_t *}: The data after padding.
 */
uint32_t *md5_padding(const byte *data, size_t data_bit_count, size_t *block_count) {
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
        data_padding[data_byte_size >> 2] &= ~set_mask_u32(
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
 * @Funticon name: md5
 * @description: This function is used to calculate the MD5 hash value of the data.
 * @Author: WAHAHA
 * @Date: 2024-4-7 10:40:14
 * @Note: md5() will pad the data to a multiple of 512 bits.
 * @param {const byte *} data: The data to be processed.
 * @param {size_t} data_bit_size: The size of the data in bits.
 * @return {status}: The status of the function execution.
 */
status md5(const byte *data, size_t data_bit_size, char *digest) {
    /* check the input data */
    ASSERT(data != NULL, error);
    ASSERT(digest != NULL, error);
    ASSERT(data_bit_size > 0, error);

    /* padding the data */
    size_t block_count = 0;
    uint32_t *data_padding = md5_padding(data, data_bit_size, &block_count);

    /* initialize the md5 register */
    // low-order byte first
    uint32_t A = 0x67452301;
    uint32_t B = 0xefcdab89;
    uint32_t C = 0x98badcfe;
    uint32_t D = 0x10325476;

    /* main loop */
    for (size_t i = 0; i < block_count; i++) {
        /* copy the md5 register */
        uint32_t AA = A;
        uint32_t BB = B;
        uint32_t CC = C;
        uint32_t DD = D;

        /* ROUND 1 */
        FF(A, B, C, D, data_padding[i * 16 + 0], 7, 0XD76AA478);
        FF(D, A, B, C, data_padding[i * 16 + 1], 12, 0XE8C7B756);
        FF(C, D, A, B, data_padding[i * 16 + 2], 17, 0X242070DB);
        FF(B, C, D, A, data_padding[i * 16 + 3], 22, 0XC1BDCEEE);

        FF(A, B, C, D, data_padding[i * 16 + 4], 7, 0XF57C0FAF);
        FF(D, A, B, C, data_padding[i * 16 + 5], 12, 0X4787C62A);
        FF(C, D, A, B, data_padding[i * 16 + 6], 17, 0XA8304613);
        FF(B, C, D, A, data_padding[i * 16 + 7], 22, 0XFD469501);

        FF(A, B, C, D, data_padding[i * 16 + 8], 7, 0X698098D8);
        FF(D, A, B, C, data_padding[i * 16 + 9], 12, 0X8B44F7AF);
        FF(C, D, A, B, data_padding[i * 16 + 10], 17, 0XFFFF5BB1);
        FF(B, C, D, A, data_padding[i * 16 + 11], 22, 0X895CD7BE);

        FF(A, B, C, D, data_padding[i * 16 + 12], 7, 0X6B901122);
        FF(D, A, B, C, data_padding[i * 16 + 13], 12, 0XFD987193);
        FF(C, D, A, B, data_padding[i * 16 + 14], 17, 0XA679438E);
        FF(B, C, D, A, data_padding[i * 16 + 15], 22, 0X49B40821);
        /* ROUND 2 */
        GG(A, B, C, D, data_padding[i * 16 + 1], 5, 0XF61E2562);
        GG(D, A, B, C, data_padding[i * 16 + 6], 9, 0XC040B340);
        GG(C, D, A, B, data_padding[i * 16 + 11], 14, 0X265E5A51);
        GG(B, C, D, A, data_padding[i * 16 + 0], 20, 0XE9B6C7AA);

        GG(A, B, C, D, data_padding[i * 16 + 5], 5, 0XD62F105D);
        GG(D, A, B, C, data_padding[i * 16 + 10], 9, 0X2441453);
        GG(C, D, A, B, data_padding[i * 16 + 15], 14, 0XD8A1E681);
        GG(B, C, D, A, data_padding[i * 16 + 4], 20, 0XE7D3FBC8);

        GG(A, B, C, D, data_padding[i * 16 + 9], 5, 0X21E1CDE6);
        GG(D, A, B, C, data_padding[i * 16 + 14], 9, 0XC33707D6);
        GG(C, D, A, B, data_padding[i * 16 + 3], 14, 0XF4D50D87);
        GG(B, C, D, A, data_padding[i * 16 + 8], 20, 0X455A14ED);

        GG(A, B, C, D, data_padding[i * 16 + 13], 5, 0XA9E3E905);
        GG(D, A, B, C, data_padding[i * 16 + 2], 9, 0XFCEFA3F8);
        GG(C, D, A, B, data_padding[i * 16 + 7], 14, 0X676F02D9);
        GG(B, C, D, A, data_padding[i * 16 + 12], 20, 0X8D2A4C8A);
        /* ROUND 3 */
        HH(A, B, C, D, data_padding[i * 16 + 5], 4, 0XFFFA3942);
        HH(D, A, B, C, data_padding[i * 16 + 8], 11, 0X8771F681);
        HH(C, D, A, B, data_padding[i * 16 + 11], 16, 0X6D9D6122);
        HH(B, C, D, A, data_padding[i * 16 + 14], 23, 0XFDE5380C);

        HH(A, B, C, D, data_padding[i * 16 + 1], 4, 0XA4BEEA44);
        HH(D, A, B, C, data_padding[i * 16 + 4], 11, 0X4BDECFA9);
        HH(C, D, A, B, data_padding[i * 16 + 7], 16, 0XF6BB4B60);
        HH(B, C, D, A, data_padding[i * 16 + 10], 23, 0XBEBFBC70);

        HH(A, B, C, D, data_padding[i * 16 + 13], 4, 0X289B7EC6);
        HH(D, A, B, C, data_padding[i * 16 + 0], 11, 0XEAA127FA);
        HH(C, D, A, B, data_padding[i * 16 + 3], 16, 0XD4EF3085);
        HH(B, C, D, A, data_padding[i * 16 + 6], 23, 0X4881D05);

        HH(A, B, C, D, data_padding[i * 16 + 9], 4, 0XD9D4D039);
        HH(D, A, B, C, data_padding[i * 16 + 12], 11, 0XE6DB99E5);
        HH(C, D, A, B, data_padding[i * 16 + 15], 16, 0X1FA27CF8);
        HH(B, C, D, A, data_padding[i * 16 + 2], 23, 0XC4AC5665);
        /* ROUND 4 */
        II(A, B, C, D, data_padding[i * 16 + 0], 6, 0XF4292244);
        II(D, A, B, C, data_padding[i * 16 + 7], 10, 0X432AFF97);
        II(C, D, A, B, data_padding[i * 16 + 14], 15, 0XAB9423A7);
        II(B, C, D, A, data_padding[i * 16 + 5], 21, 0XFC93A039);

        II(A, B, C, D, data_padding[i * 16 + 12], 6, 0X655B59C3);
        II(D, A, B, C, data_padding[i * 16 + 3], 10, 0X8F0CCC92);
        II(C, D, A, B, data_padding[i * 16 + 10], 15, 0XFFEFF47D);
        II(B, C, D, A, data_padding[i * 16 + 1], 21, 0X85845DD1);

        II(A, B, C, D, data_padding[i * 16 + 8], 6, 0X6FA87E4F);
        II(D, A, B, C, data_padding[i * 16 + 15], 10, 0XFE2CE6E0);
        II(C, D, A, B, data_padding[i * 16 + 6], 15, 0XA3014314);
        II(B, C, D, A, data_padding[i * 16 + 13], 21, 0X4E0811A1);

        II(A, B, C, D, data_padding[i * 16 + 4], 6, 0XF7537E82);
        II(D, A, B, C, data_padding[i * 16 + 11], 10, 0XBD3AF235);
        II(C, D, A, B, data_padding[i * 16 + 2], 15, 0X2AD7D2BB);
        II(B, C, D, A, data_padding[i * 16 + 9], 21, 0XEB86D391);

        /* update the md5 register */
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