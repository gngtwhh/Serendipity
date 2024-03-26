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
 * @Funticon name: sm4_gengrate_subkey
 * @description: generate the subkey of the sm4_encipher
 * @Author: WAHAHA
 * @Date: 2024-3-15 17:59:46
 * @Note: None
 * @param {sm4_encipher} *sm4
 * @return {status}
 */
static status sm4_gengrate_subkey(sm4_encipher *sm4) {
    ASSERT(sm4 != NULL, error);
    uint32_t *rk = sm4->rk;
    uint32_t *key = (uint32_t *) sm4->key;
    uint32_t mk[4];
    /* xor the key with the FK */
    for (int i = 0; i < 4; i++)
        mk[i] = key[i] ^ SM4_FK[i];

    /*
     * generate the subkey,
     * 4 round keys are processed per round cycle to improve efficiency.
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
    return sm4_gengrate_subkey(sm4);
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
status sm4_encrypt(sm4_encipher *sm4, const byte *in_data, int in_data_len, byte *out_data,
                   int *out_data_len) {
    /* check the parameters */
    ASSERT(sm4 != NULL && in_data != NULL && out_data != NULL && out_data_len != NULL, error);
    ASSERT(sm4->is_key_set, error);

    /* nessary variables */
    uint32_t *pad_data = NULL;
    int block_num;

    /* calculate the length of the data after padding, and set the block number */
    int pad_len = pkcs7_pad_len(in_data_len, SM4_BLOCK_SIZE);
    *out_data_len = in_data_len + pad_len;
    block_num = *out_data_len / SM4_BLOCK_SIZE;

    /* allocate the memory for the padded data */
    pad_data = (uint32_t *) pkcs7_pad(in_data, in_data_len, SM4_BLOCK_SIZE);
    if (pad_data == NULL)
        return failed; // memory allocation failed

    /*uint32_t *pad_data_uint32 = (uint32_t *) pad_data;
    for (int i = 0; i < block_num; i++) {
        pad_data_uint32[i] = BYTES_TO_UINT32(pad_data + i * SM4_BLOCK_SIZE);
    }*/

    /* encrypt the data block by block */
    for (int block_idx = 0; block_idx < block_num; block_idx++) {
        /* step 1: 32 rounds of encryption */
        sm4_crypt_block_round(sm4, pad_data + block_idx,
                              (uint32_t *) out_data + block_idx, SM4_ENCRYPT);
        /* step 2: reverse the data */
        sm4_crypt_block_reverse((uint32_t *) (out_data + block_idx));
    }

    /* free the memory */
    free(pad_data);
    return true;
}

status sm4_decrypt(sm4_encipher *sm4, const byte *in_data, int in_data_len, byte *out_data,
                   int *out_data_len);

status sm4_crypt_block_round(sm4_encipher *sm4, const uint32_t *in_data, uint32_t *out_data,
                             int mode) {
    /* check the parameters */
    ASSERT(sm4 != NULL && in_data != NULL && out_data != NULL, error);
    ASSERT(mode == SM4_ENCRYPT || mode == SM4_DECRYPT, error);
    /* nessary variables */
    uint32_t *rk = sm4->rk;
    uint32_t x[SM4_BLOCK_SIZE / sizeof(uint32_t)];
    int i, step = mode;
    i = mode == SM4_ENCRYPT ? 0 : SM4_ROUND - 1;
    /* copy the data */
    memcpy(x, in_data, SM4_BLOCK_SIZE);
    /* 32 rounds of encryption */
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
    /* copy the data */
    memcpy(out_data, x, SM4_BLOCK_SIZE);
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