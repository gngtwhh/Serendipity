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

/* TEA encrytion interface and subroutines */
/* TEA block encrytion */
status tea_block_encrypt(tea_encipher *tea, uint32_t *plain, uint32_t *cipher) {
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

/* TEA block decrytion */
status tea_block_decrypt(tea_encipher *tea, uint32_t *cipher, uint32_t *plain) {
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

/* TEA encrytion interface */
status tea_encrypt(tea_encipher *tea, uint32_t *plain, uint32_t *cipher) {
    /* check the input */
    ASSERT(tea != NULL && plain != NULL && cipher != NULL, error);
    /* check if the plain text is valid */
    ASSERT(tea->n & 1 == 0, false);
    /* start to encrypt */
    status ret = true;
    for (int i = 0; i < tea->n; i += 2) {
        ret = tea_block_encrypt(tea, plain + i, cipher + i);
    }
    return ret;
}

/* TEA decrytion interface */
status tea_decrypt(tea_encipher *tea, uint32_t *cipher, uint32_t *plain) {
    /* check the input */
    ASSERT(tea != NULL && plain != NULL && cipher != NULL, error);
    /* check if the cipher text is valid */
    ASSERT(tea->n & 1 == 0, false);
    /* start to decrypt */
    status ret = true;
    for (int i = 0; i < tea->n; i += 2) {
        ret = tea_block_decrypt(tea, cipher + i, plain + i);
    }
    return ret;
}


/* XTEA encrytion interface and subroutines */
/* XTEA block encrytion */
status xtea_block_encrypt(tea_encipher *tea, uint32_t *plain, uint32_t *cipher) {
    ASSERT(tea != NULL && plain != NULL && cipher != NULL, error);
    uint32_t v0 = plain[0], v1 = plain[1], sum = 0;
    for (int i = 0; i < tea->rounds; i++) {
        v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + tea->key[sum & 3]);
        sum += tea->delta;
        v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + tea->key[(sum >> 11) & 3]);
    }
    cipher[0] = v0;
    cipher[1] = v1;
    return true;
}

/* XTEA block decrytion */
status xtea_block_decrypt(tea_encipher *tea, uint32_t *cipher, uint32_t *plain) {
    ASSERT(tea != NULL && plain != NULL && cipher != NULL, error);
    uint32_t v0 = cipher[0], v1 = cipher[1], sum = tea->delta * tea->rounds;
    for (int i = 0; i < tea->rounds; i++) {
        v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + tea->key[(sum >> 11) & 3]);
        sum -= tea->delta;
        v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + tea->key[sum & 3]);
    }
    plain[0] = v0;
    plain[1] = v1;
    return true;
}

/* XTEA encrytion interface */
status xtea_encrypt(tea_encipher *tea, uint32_t *plain, uint32_t *cipher) {
    /* check the input */
    ASSERT(tea != NULL && plain != NULL && cipher != NULL, error);
    /* check if the plain text is valid */
    ASSERT(tea->n & 1 == 0, false);
    /* start to encrypt */
    status ret = true;
    for (int i = 0; i < tea->n; i += 2) {
        ret = xtea_block_encrypt(tea, plain + i, cipher + i);
    }
    return ret;
}

/* XTEA decrytion interface */
status xtea_decrypt(tea_encipher *tea, uint32_t *cipher, uint32_t *plain) {
    /* check the input */
    ASSERT(tea != NULL && plain != NULL && cipher != NULL, error);
    /* check if the cipher text is valid */
    ASSERT(tea->n & 1 == 0, false);
    /* start to decrypt */
    status ret = true;
    for (int i = 0; i < tea->n; i += 2) {
        ret = xtea_block_decrypt(tea, cipher + i, plain + i);
    }
    return ret;
}

/* XXTEA encrytion interface */
/* XXTEA encrytion interface */
status xxtea_encrypt(tea_encipher *tea, uint32_t *plain, uint32_t *cipher) {
    ASSERT(tea != NULL && plain != NULL && cipher != NULL, error);
    uint32_t e, sum = 0, y = plain[0], z = plain[tea->n - 1];
    int rounds = 6 + 52 / (tea->n);

    /* start to encrypt */
    for (int i = 0;i < rounds;++i) {
        sum += tea->delta;
        e = (sum >> 2) & 3;
        for (int p = 0; p < tea->n - 1; p++) {
            y = plain[p + 1];
            plain[p] += ((z >> 5 ^ y << 2) + (y >> 3 ^ z << 4)) ^ ((sum ^ y) + (tea->key[(p & 3) ^ e] ^ z));
            z = plain[p];
        }
        y = plain[0];
        plain[tea->n - 1] += ((z >> 5 ^ y << 2) + (y >> 3 ^ z << 4)) ^ ((sum ^ y) + (tea->key[((tea->n - 1) & 3) ^ e] ^ z));
        z = plain[tea->n - 1];
    }
    return true;
}

/* XXTEA decrytion interface */
status xxtea_decrypt(tea_encipher *tea, uint32_t *cipher, uint32_t *plain) {
    ASSERT(tea != NULL && plain != NULL && cipher != NULL, error);
    uint32_t e, sum, y = cipher[0], z = cipher[tea->n - 1];
    int rounds = 6 + 52 / (tea->n);
    sum = rounds * tea->delta;

    /* start to decrypt */
    for (int i = 0; i < rounds; i++) {
        e = (sum >> 2) & 3;
        for (int p = tea->n - 1; p > 0; p--) {
            z = cipher[p - 1];
            cipher[p] -= ((z >> 5 ^ y << 2) + (y >> 3 ^ z << 4)) ^ ((sum ^ y) + (tea->key[(p & 3) ^ e] ^ z));
            y = cipher[p];
        }
        z = cipher[tea->n - 1];
        cipher[0] -= ((z >> 5 ^ y << 2) + (y >> 3 ^ z << 4)) ^ ((sum ^ y) + (tea->key[(0 & 3) ^ e] ^ z));
        y = cipher[0];
        sum -= tea->delta;
    }
    return true;
}