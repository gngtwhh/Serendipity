/**
 * @file: rc4.h
 * @description: This is a header file that contains the declaration of the RC4 encryption algorithm.
 * @author: WAHAHA
 * @Date: 2024-03-05 14:15:32
 * @LastEditTime: 2024-03-05 14:45:28
 * @FilePath: \Serendipity\include\encrypt\rc4.h
 * @category: encrypt-algorithm
 */

#ifndef SERENDIPITY_RC4_H
#define SERENDIPITY_RC4_H

/* pre-initialization of encrypt */
#include <encrypt/encrypt_pre_init.h>
#include <stdint.h>

/* RC4 encipher */
typedef struct rc4_encipher {
    byte sbox[256]; // the sbox of RC4
    byte *key;      // the key of RC4
    int key_len;    // the length of the key
} rc4_encipher;

/* rc4_encipher object */
rc4_encipher *new_rc4();

status free_rc4(rc4_encipher *rc4);

/* RC4 functions */
status rc4_set_key(rc4_encipher *rc4,const byte *key, int key_len);

status rc4_generate_sbox(rc4_encipher *rc4);

status rc4_crypt(rc4_encipher *rc4,const byte *in_data, int data_len, byte *out_data);


#endif // SERENDIPITY_RC4_H