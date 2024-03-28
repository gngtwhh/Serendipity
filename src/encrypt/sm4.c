/**
 * @file: SM4.c
 * @description: This is a source file that contains the implementation of RC4 encryption algorithm.
 * @author: WAHAHA
 * @Date: 2024/3/15 15:49
 * @LastEditTime: 2024/3/15 15:49
 * @FilePath: Serendipity/src/encrypt/SM4.c
 * @category: encrypt-algorithm
 */

#include <encrypt/sm4.h>
#include <encrypt/pkcspad.h>
#include <misc/endian.h>
#include <stdlib.h>
#include <string.h>

/**
 * @Funticon name: new_sm4
 * @description: new a sm4_encipher object
 * @Author: WAHAHA
 * @Date: 2024-3-15 17:23:20
 * @Note: None
 * @return {rc4_encipher *}
 */
sm4_encipher *new_sm4() {
    sm4_encipher *new_sm4 = (sm4_encipher *) malloc(sizeof(sm4_encipher));
    /* check the memory */
    if (new_sm4 == NULL)
        return NULL;
    new_sm4->is_key_set = false;
    /* the memory of "key" and "rk" will be allocated in the function of sm4_init */
    new_sm4->key = NULL;
    new_sm4->rk = NULL;
    return new_sm4;
}

/**
 * @Funticon name: free_sm4
 * @description: free a sm4_encipher object
 * @Author: WAHAHA
 * @Date: 2024-3-15 17:47:58
 * @Note: None
 * @param {sm4_encipher} *sm4
 * @return {status}
 */
status free_sm4(sm4_encipher *sm4) {
    ASSERT(sm4 != NULL, error);
    if (sm4->key != NULL)
        free(sm4->key);
    if (sm4->rk != NULL)
        free(sm4->rk);
    free(sm4);
    return true;
}

/**
 * @Funticon name: sm4_generate_subkey
 * @description: generate the subkey of the sm4_encipher
 * @Author: WAHAHA
 * @Date: 2024-3-15 17:59:46
 * @Note: None
 * @param {sm4_encipher} *sm4
 * @return {status}
 */
static status sm4_generate_subkey(sm4_encipher *sm4) {
    ASSERT(sm4 != NULL, error);
    uint32_t *rk = sm4->rk;
//    uint32_t *key = (uint32_t *) sm4->key;
    uint32_t mk[4];

    /*
     * copy the key
     * @Note: the key is stored in the big-endian format
     */
    for (int i = 0, j = 0; i < 16; i += 4, j++)
        BE_BYTES_TO_UINT32(mk[j], sm4->key + i);

    /* xor the key with the FK */
    for (int i = 0; i < 4; ++i)
        mk[i] ^= SM4_FK[i];

    /*
     * generate the subkey
     * @Note: 4 round keys are processed per round cycle to improve efficiency.
     */
    uint32_t i = 0;
    do {
        rk[i] = (mk[0] ^= SM4_KEYGEN_T(mk[1] ^ mk[2] ^ mk[3] ^ SM4_CK[i]));
        i++;
        rk[i] = (mk[1] ^= SM4_KEYGEN_T(mk[2] ^ mk[3] ^ mk[0] ^ SM4_CK[i]));
        i++;
        rk[i] = (mk[2] ^= SM4_KEYGEN_T(mk[3] ^ mk[0] ^ mk[1] ^ SM4_CK[i]));
        i++;
        rk[i] = (mk[3] ^= SM4_KEYGEN_T(mk[0] ^ mk[1] ^ mk[2] ^ SM4_CK[i]));
        i++;
    } while (i < SM4_ROUND);
    return true;
}

/**
 * @Funticon name: sm4_init
 * @description: initialize the sm4_encipher object with a 128-bit key
 * @description:
 * @Author: WAHAHA
 * @Date: 2024-3-15 17:52:5
 * @Note: the caller should make sure that the length of the key is 16 bytes
 * @param {sm4_encipher} *sm4
 * @return {status}
 */
status sm4_init(sm4_encipher *sm4, const byte *key) {
    /* check the parameters */
    ASSERT(sm4 != NULL && key != NULL, error);
    /* allocate the memory for the key and rk */
    sm4->key = (byte *) malloc(SM4_KEY_SIZE);
    sm4->rk = (uint32_t *) malloc(SM4_ROUND * sizeof(uint32_t));
    if (sm4->key == NULL || sm4->rk == NULL)
        return failed;
    /* copy the key */
    memcpy(sm4->key, key, SM4_KEY_SIZE);
    sm4->is_key_set = true;
    /* generate the subkey,and return the status */
    return sm4_generate_subkey(sm4);
}

/**
 * @Funticon name: sm4_encrypt
 * @description: encrypt the data with the sm4_encipher object
 * @Author: WAHAHA
 * @Date: 2024-3-19 1:55:28
 * @param {sm4_encipher} *sm4
 * @param {byte} *in_data
 * @param {int} data_len
 * @param {byte} *out_data
 * @param {int} *out_data_len
 * @return {status}
 */
status sm4_encrypt(sm4_encipher *sm4, const byte *in_data, int in_data_len, byte *out_data) {
    /* check the parameters */
    ASSERT(sm4 != NULL && in_data != NULL && out_data != NULL, error);
    ASSERT(sm4->is_key_set, error);
    // the length of the data should be a multiple of 16
    // caller should make sure the length of the data is a multiple of 16
    ASSERT(in_data_len % SM4_BLOCK_SIZE == 0, error);

    /* necessary variables */
    uint32_t block_data[4];

    for (int i = 0; i < in_data_len; i += 16) {
        /* copy the data */
        for (int j = 0; j < 4; ++j)
            BE_BYTES_TO_UINT32(block_data[j], in_data + i + j * 4);
        sm4_crypt_block_round(sm4, block_data,
                              (uint32_t *) (out_data + i), SM4_ENCRYPT);
        sm4_crypt_block_reverse((uint32_t *) (out_data + i));
    }

    return true;
}

status sm4_decrypt(sm4_encipher *sm4, const byte *in_data, int in_data_len, byte *out_data,
                   int *out_data_len);

status sm4_crypt_block_round(sm4_encipher *sm4, const uint32_t *in_data, uint32_t *out_data,
                             int mode) {
    /* check the parameters */
    ASSERT(sm4 != NULL && in_data != NULL && out_data != NULL, error);
    ASSERT(mode == SM4_ENCRYPT || mode == SM4_DECRYPT, error);
    /* necessary variables */
    uint32_t *rk = sm4->rk;
    uint32_t x[SM4_BLOCK_SIZE / sizeof(uint32_t)];
    int i, step = mode;
    /*
     * copy the data
     * @Note: the data is stored in the big-endian format
     */
//    for (i = 0; i < 4; ++i)
//        BE_BYTES_TO_UINT32(x[i], in_data + i);
    for (i = 0; i < 4; ++i)
        x[i] = in_data[i];

    /* 32 rounds of encryption */
    i = mode == SM4_ENCRYPT ? 0 : SM4_ROUND - 1;
    do {
        x[0] ^= SM4_ROUND_T(x[1] ^ x[2] ^ x[3] ^ rk[i]);
        i += step;
        x[1] ^= SM4_ROUND_T(x[2] ^ x[3] ^ x[0] ^ rk[i]);
        i += step;
        x[2] ^= SM4_ROUND_T(x[3] ^ x[0] ^ x[1] ^ rk[i]);
        i += step;
        x[3] ^= SM4_ROUND_T(x[0] ^ x[1] ^ x[2] ^ rk[i]);
        i += step;
    } while (mode == SM4_ENCRYPT ? (i < SM4_ROUND) : (i >= 0));
    /*
     * copy the data
     * @Note: the data is stored in the big-endian format
     */
    for (i = 0; i < 4; ++i)
        BE_UINT32_TO_BYTES((byte *) out_data + i*4, x[i]);

    return true;
}

status sm4_crypt_block_reverse(uint32_t *data) {
    /* check the parameters */
    ASSERT(data != NULL, error);
    /* reverse the data */
    uint32_t tmp;
    tmp = data[0];
    data[0] = data[3];
    data[3] = tmp;
    tmp = data[1];
    data[1] = data[2];
    data[2] = tmp;
    return true;
}