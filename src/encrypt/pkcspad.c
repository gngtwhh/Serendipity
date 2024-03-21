/**
 * @file: pkcspad.c
 * @description: This is a source file that contains the implementation of PKCSPAD algorithm.
 * @author: WAHAHA
 * @Date: 2024/3/19 2:29
 * @LastEditTime: 2024/3/19 2:29
 * @FilePath: Serendipity/src/encrypt/pkcspad.c
 * @category: encrypt-algorithm
 */

#include <encrypt/pkcspad.h>
//#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @Funticon name: pkcs7_pad
 * @description: padding the data with PKCS7
 * @Author: WAHAHA
 * @Date: 2024-3-21 15:34:37
 * @Note: This function will return a new memory block,which should be freed by the caller.
 * @param {byte} *data
 * @param {size_t} data_len
 * @param {size_t} block_size
 * @return {byte *}
 */
byte *pkcs7_pad(byte *data, size_t data_len, size_t block_size) {
    if (data == NULL)
        return NULL;

    byte pad_value = block_size - (data_len % block_size);
    size_t pad_data_len = data_len + pad_value;
    byte *output = (byte *) malloc(sizeof(byte) * pad_data_len);
    if (output == NULL)
        return NULL;

    memcpy(output, data, data_len);
    memset(output + data_len, pad_value, pad_value);

    return output;
}

/**
 * @Funticon name: pkck7_unpad
 * @description: unpadding the data with PKCS7
 * @Author: WAHAHA
 * @Date: 2024-3-21 15:36:26
 * @Note: This function will return a new memory block,which should be freed by the caller.
 * @param {byte} *data
 * @param {size_t} data_len
 * @param {size_t} block_size
 * @return {byte *}
 */
byte *pkcs7_unpad(byte *data, size_t data_len, size_t block_size) {
    if (data == NULL)
        return NULL;

    byte pad_value = data[data_len - 1];
    /* check the padding value */
    if (pad_value >= block_size)
        return NULL;

    size_t unpad_data_len = data_len - pad_value;
    byte *output = (byte *) malloc(sizeof(byte) * unpad_data_len);
    if (output == NULL)
        return NULL;

    memcpy(output, data, unpad_data_len);

    return output;
}

/* PKCS5 padding and unpadding */
byte *pkcs5_pad(byte *data, size_t data_len, size_t block_size);

byte *pkcs5_unpad(byte *data, size_t data_len, size_t block_size);