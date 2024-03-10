/**
 * @file: rc4.c
 * @description: RC4 encryption algorithm implementation
 * @author: WAHAHA
 * @Date: 2024-03-05 14:15:45
 * @LastEditTime: 2024-03-05 14:46:00
 * @FilePath: \Serendipity\src\encrypt\rc4.c
 * @category: encrypt-algorithm
 */

#include <encrypt/rc4.h>
#include <stdlib.h>

/**
 * @Funticon name: new_rc4
 * @description: new a rc4_encipher object
 * @Author: WAHAHA
 * @Date: 2024-3-10 20:40:22
 * @Note: None
 * @return {rc4_encipher *}
 */
rc4_encipher *new_rc4() {
    rc4_encipher *rc4 = (rc4_encipher *) malloc(sizeof(rc4_encipher));
    if (rc4 == NULL)
        return NULL;
    for (int i = 0; i < 256; i++)
        rc4->sbox[i] = i;
    rc4->key = NULL;
    rc4->key_len = 0;
    return rc4;
}

/**
 * @Funticon name: free_rc4
 * @description: free a rc4_encipher object
 * @Author: WAHAHA
 * @Date: 2024-3-10 21:14:23
 * @Note: None
 * @param {rc4_encipher} *rc4
 * @return {status}
 */
status free_rc4(rc4_encipher *rc4) {
    ASSERT(rc4 != NULL, error);
    if (rc4->key != NULL)
        free(rc4->key);
    free(rc4);
    return true;
}

/**
 * @Funticon name: rc4_set_key
 * @description: set the key of the rc4_encipher
 * @Author: WAHAHA
 * @Date: 2024-3-10 21:15:3
 * @Note: None
 * @param {rc4_encipher} *rc4
 * @param {byte} *key
 * @param {int} key_len
 * @return {status}
 */
status rc4_set_key(rc4_encipher *rc4, const byte *key, int key_len) {
    ASSERT(rc4 != NULL && key != NULL, error);

    /* if the key is not NULL, free it */
    if (rc4->key != NULL)
        free(rc4->key);
    /* alloc the memory for the new key */
    rc4->key = (uint8_t *) malloc(key_len);
    if (rc4->key == NULL)
        return error;

    /* set the key */
    for (int i = 0; i < key_len; i++)
        rc4->key[i] = key[i];
    rc4->key_len = key_len;

    /* generate the sbox */
    return rc4_generate_sbox(rc4);
}

/**
 * @Funticon name: rc4_generate_sbox
 * @description: generate the sbox of the rc4_encipher
 * @Author: WAHAHA
 * @Date: 2024-3-10 21:26:25
 * @Note: None
 * @param {rc4_encipher} *rc4
 * @return {status}
 */
status rc4_generate_sbox(rc4_encipher *rc4) {
    ASSERT(rc4 != NULL, error);
    int j = 0;
    for (int i = 0; i < 256; i++) {
        j = (j + rc4->sbox[i] + rc4->key[i % rc4->key_len]) % 256;
        byte temp = rc4->sbox[i];
        rc4->sbox[i] = rc4->sbox[j];
        rc4->sbox[j] = temp;
    }
    return true;
}

/**
 * @Funticon name: rc4_crypt
 * @description: crypt the data using the rc4_encipher
 * @Author: WAHAHA
 * @Date: 2024-3-10 21:28:2
 * @Note: the length of the out_data is equal to the data_len
 * @param {rc4_encipher} *rc4
 * @param {byte} *in_data
 * @param {int} data_len
 * @param {byte} *out_data
 * @return {status}
 */
status rc4_crypt(rc4_encipher *rc4, const byte *in_data, int data_len, byte *out_data) {
    ASSERT(rc4 != NULL && in_data != NULL && out_data != NULL, error);
    int i = 0, j = 0;
    for (int k = 0; k < data_len; k++) {
        /* update i and j */
        i = (i + 1) % 256;
        j = (j + rc4->sbox[i]) % 256;
        /* swap sbox[i] and sbox[j] */
        byte temp = rc4->sbox[i];
        rc4->sbox[i] = rc4->sbox[j];
        rc4->sbox[j] = temp;
        /* crypt the data */
        int t = (rc4->sbox[i] + rc4->sbox[j]) % 256;
        out_data[k] = in_data[k] ^ rc4->sbox[t];
    }
    return true;
}
