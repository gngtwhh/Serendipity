/**
 * @file: pkcspad.h
 * @description: This is a header file that contains the declaration of PKCSPAD algorithm.
 * @author: WAHAHA
 * @Date: 2024/3/19 2:29
 * @LastEditTime: 2024/3/19 2:29
 * @FilePath: Serendipity/include/encrypt/pkcspad.h
 * @category: encrypt-algorithm
 */

#ifndef SERENDIPITY_PKCSPAD_H
#define SERENDIPITY_PKCSPAD_H

#include <encrypt/encrypt_pre_init.h>


/* PKCS7 padding and unpadding */
byte *pkcs7_pad(byte *data, size_t data_len, size_t block_size);

byte *pkcs7_unpad(byte *data, size_t data_len, size_t block_size);

/* PKCS5 padding and unpadding */
byte *pkcs5_pad(byte *data, size_t data_len, size_t block_size);

byte *pkcs5_unpad(byte *data, size_t data_len, size_t block_size);

#endif //SERENDIPITY_PKCSPAD_H
