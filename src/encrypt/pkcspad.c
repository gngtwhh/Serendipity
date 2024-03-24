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
byte *pkcs7_pad(const byte *data, size_t data_len, size_t block_size) {
    if (data == NULL)
        return NULL;

    byte pad_value = pkcs7_pad_len(data_len, block_size);
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
byte *pkcs7_unpad(const byte *data, size_t data_len, size_t block_size) {
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

/**
 * @Funticon name: pkcs5_pad
 * @description: padding the data with PKCS5
 * @Author: WAHAHA
 * @Date: 2024-3-21 16:1:26
 * @Note: This function will return a new memory block,which should be freed by the caller.
 * @param {byte} *data
 * @param {size_t} data_len
 * @return {byte *}
 */
byte *pkcs5_pad(const byte *data, size_t data_len){
    return pkcs7_pad(data, data_len, PKCS5_BLOCK_SIZE);
}

/**
 * @Funticon name: pkcs5_unpad
 * @description: unpadding the data with PKCS5
 * @Author: WAHAHA
 * @Date: 2024-3-21 16:4:35
 * @Note: This function will return a new memory block,which should be freed by the caller.
 * @param {byte} *data
 * @param {size_t} data_len
 * @return {byte *}
 */
byte *pkcs5_unpad(const byte *data, size_t data_len){
    return pkcs7_unpad(data, data_len, PKCS5_BLOCK_SIZE);
}