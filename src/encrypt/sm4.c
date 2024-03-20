/**
 * @file: SM4.c
 * @description: This is a source file that contains the implementation of RC4 encryption algorithm.
 * @author: WAHAHA
 * @Date: 2024/3/15 15:49
 * @LastEditTime: 2024/3/15 15:49
 * @FilePath: Serendipity/src/encrypt/SM4.c
 * @category: 
 */

#include <encrypt/sm4.h>
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
    /* the memory of "key" and "sk" will be allocated in the function of sm4_init */
    new_sm4->key = NULL;
    new_sm4->sk = NULL;
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
    if (sm4->sk != NULL)
        free(sm4->sk);
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
    uint32_t *mk = (uint32_t *) sm4->key;
    uint32_t k[4];

    /* xor the mk with the FK */
    for (int i = 0; i < 4; i++)
        k[i] = mk[i] ^ SM4_FK[i];

    /* generate the subkey */
    /*
     * to prevent macros from expanding too long
     * use a temporary variable to store the result
     */
    uint32_t tmp;
    for (int i = 0; i < SM4_ROUND; i++) {
        tmp = k[1] ^ k[2] ^ k[3] ^ SM4_CK[i];
        k[0] ^= SM4_ROUND_T(tmp);
        rk[i] = k[0];
        k[0] = k[1];
        k[1] = k[2];
        k[2] = k[3];
        k[3] = rk[i];
    }
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
    ASSERT(sm4 != NULL && key != NULL, error);
    sm4->key = (byte *) malloc(SM4_KEY_SIZE);
    sm4->sk = (uint32_t *) malloc(SM4_ROUND * sizeof(uint32_t));
    if (sm4->key == NULL || sm4->rk == NULL)
        return failed;
    memcpy(sm4->key, key, SM4_KEY_SIZE);
    sm4->is_key_set = true;
    return sm4_gengrate_subkey(sm4);
}

status sm4_crypt(sm4_encipher *sm4, const byte *in_data, int data_len, byte *out_data, int mode);