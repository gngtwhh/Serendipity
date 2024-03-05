/*
 * @file: rc4.h
 * @description: This is a header file that contains the declaration of the RC4 encryption algorithm.
 * @author: WAHAHA
 * @Date: 2024-03-05 14:15:32
 * @LastEditTime: 2024-03-05 14:45:28
 * @FilePath: \Serendipity\include\encrypt\rc4.h
 * @category: encrypt-algorithm
 */

#ifndef _RC4_H_
#define _RC4_H_

 /* pre-initialization of encrypt */
#include <encrypt/encrypt_pre_init.h>
#include <stdint.h>

/* RC4 encipher */
typedef struct rc4_encipher {
    uint8_t sbox[256]; // the sbox of RC4
    uint8_t *key;      // the key of RC4
    int key_len;      // the length of the key
} rc4_encipher;

rc4_encipher *new_rc4(NULL);
status free_rc4(rc4_encipher *rc4);

/* RC4 functions */
status rc4_set_key(rc4_encipher *rc4, uint8_t *key, int key_len);
status rc4_crypt(rc4_encipher *rc4, uint8_t *data, int data_len, uint8_t *out_data);


#endif // _RC4_H_