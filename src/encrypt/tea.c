/**
 * @file  tea.c
 * @brief  TEA encryption algorithm implementation
 * @author  WAHAHA
 * @category  encrypt-algorithm
 * @date    2024
 */

#include <encrypt/tea.h>
#include <stdlib.h>
#include <stdio.h>

#define DELTA 0x9e3779b9
#define ROUND 32

 /* TEA encipher */
tea_encipher *new_tea(uint32_t delta, uint32_t key[4], int rounds) {
    /* check the key and rounds */
    if (rounds < 0 || key == NULL) {
        printf("new_tea error: Invalid key or rounds\n");
        return NULL;
    }
    /* create a tea_encipher */
    tea_encipher *tea = (tea_encipher *)malloc(sizeof(tea_encipher));
    if (tea == NULL)
        return NULL;
    tea->delta = (delta == 0) ? DELTA : delta;
    for (int i = 0; i < 4; i++) {
        tea->key[i] = key[i];
    }
    tea->rounds = rounds;
    return tea;
}
status free_tea(tea_encipher *tea) {
    ASSERT(tea != NULL, error);
    free(tea);
    return true;
}

/* common TEA encrytion */
status tea_encrypt(tea_encipher *tea, uint32_t *plain, uint32_t *cipher) {
    ASSERT(tea != NULL && plain != NULL && cipher != NULL, error);
    uint32_t v0 = plain[0], v1 = plain[1], sum = 0;
    for (int i = 0; i < tea->rounds; i++) {
        sum += tea->delta;
        v0 += ((v1 << 4) + tea->key[0]) ^ (v1 + sum) ^ ((v1 >> 5) + tea->key[1]);
        v1 += ((v0 << 4) + tea->key[2]) ^ (v0 + sum) ^ ((v0 >> 5) + tea->key[3]);
    }
    cipher[0] = v0;
    cipher[1] = v1;
    return true;
}

status tea_decrypt(tea_encipher *tea, uint32_t *cipher, uint32_t *plain){
    ASSERT(tea != NULL && plain != NULL && cipher != NULL, error);
    uint32_t v0 = cipher[0], v1 = cipher[1], sum = tea->delta * tea->rounds;
    for (int i = 0; i < tea->rounds; i++) {
        v1 -= ((v0 << 4) + tea->key[2]) ^ (v0 + sum) ^ ((v0 >> 5) + tea->key[3]);
        v0 -= ((v1 << 4) + tea->key[0]) ^ (v1 + sum) ^ ((v1 >> 5) + tea->key[1]);
        sum -= tea->delta;
    }
    plain[0] = v0;
    plain[1] = v1;
    return true;
}

/* XTEA encrytion */
status xtea_encrypt(tea_encipher *tea, uint32_t *plain, uint32_t *cipher);
status xtea_decrypt(tea_encipher *tea, uint32_t *cipher, uint32_t *plain);

/* XXTEA encrytion */
status xxtea_encrypt(tea_encipher *tea, uint32_t *plain, uint32_t *cipher);
status xxtea_decrypt(tea_encipher *tea, uint32_t *cipher, uint32_t *plain);
