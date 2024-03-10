/**
 * @file: tea.c
 * @description: TEA encryption algorithm implementation
 * @author: WAHAHA
 * @Date: 2024-02-29 17:33:30
 * @LastEditTime: 2024-03-04 14:40:13
 * @FilePath: \Serendipity\src\encrypt\tea.c
 * @category: encrypt-algorithm
 */

#include <encrypt/tea.h>
#include <stdlib.h>
#include <stdio.h>

#define DELTA 0x9e3779b9
#define ROUND 32
#define XXTEA_MX (((z >> 5 ^ y << 2) + (y >> 3 ^ z << 4)) \
    ^ ((sum ^ y) + (tea->key[(p & 3) ^ e] ^ z)))

 /* TEA encipher */
 /**
  * @Funticon name: new_tea
  * @description: new a tea_encipher object
  * @Author: WAHAHA
  * @Date: 2024-03-04 12:00:44
  * @Note: the returned object pointer should be considered to have been properly initialized
  * @param {uint32_t} delta
  * @param {uint32_t} key
  * @param {int} rounds
  * @return {tea_encipher *}
  */
tea_encipher *new_tea(uint32_t delta, uint32_t key[4], int rounds)
{
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
    tea->rounds = (rounds <= 0) ? ROUND : rounds;
    return tea;
}

/**
 * @Funticon name: free_tea
 * @description: free the tea_encipher object
 * @Author: WAHAHA
 * @Date: 2024-03-04 12:03:44
 * @Note: None
 * @param {tea_encipher} *tea
 * @return {status}
 */
status free_tea(tea_encipher *tea)
{
    ASSERT(tea != NULL, error);
    free(tea);
    return true;
}

/* TEA encrytion interface and subroutines */
/**
 * @Funticon name: tea_block_encrypt
 * @description: encrypt a block of plain text(2 uint32_t) using TEA algorithm
 * @Author: WAHAHA
 * @Date: 2024-03-04 12:04:18
 * @Note: None
 * @param {tea_encipher} *tea
 * @param {uint32_t} *plain
 * @param {uint32_t} *cipher
 * @return {status}
 */
status tea_block_encrypt(tea_encipher *tea, uint32_t *plain, uint32_t *cipher)
{
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

/**
 * @Funticon name: tea_block_decrypt
 * @description: decrypt a block of cipher text(2 uint32_t) using TEA algorithm
 * @Author: WAHAHA
 * @Date: 2024-03-04 12:05:23
 * @Note: None
 * @param {tea_encipher} *tea
 * @param {uint32_t} *cipher
 * @param {uint32_t} *plain
 * @return {status}
 */
status tea_block_decrypt(tea_encipher *tea, uint32_t *cipher, uint32_t *plain)
{
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

/**
 * @Funticon name: tea_encrypt
 * @description: interface of TEA encrytion, encrypt the plain text using TEA algorithm
 * @Author: WAHAHA
 * @Date: 2024-03-04 12:06:48
 * @Note: the plain whill be checked if it is valid
 * @param {tea_encipher} *tea
 * @param {uint32_t} *plain
 * @param {uint32_t} *cipher
 * @return {status}
 */
status tea_encrypt(tea_encipher *tea, uint32_t *plain, uint32_t *cipher)
{
    /* check the input */
    ASSERT(tea != NULL && plain != NULL && cipher != NULL, error);
    /* check if the plain text is valid */
    ASSERT((tea->n & 1) == 0, false);
    /* start to encrypt every block */
    status ret = true;
    for (int i = 0; i < tea->n; i += 2) {
        ret = tea_block_encrypt(tea, plain + i, cipher + i);
    }
    return ret;
}

/**
 * @Funticon name: tea_decrypt
 * @description: interface of TEA decrytion, decrypt the cipher text using TEA algorithm
 * @Author: WAHAHA
 * @Date: 2024-03-04 12:09:02
 * @Note: the cipher whill be checked if it is valid
 * @param {tea_encipher} *tea
 * @param {uint32_t} *cipher
 * @param {uint32_t} *plain
 * @return {status}
 */
status tea_decrypt(tea_encipher *tea, uint32_t *cipher, uint32_t *plain)
{
    /* check the input */
    ASSERT(tea != NULL && plain != NULL && cipher != NULL, error);
    /* check if the cipher text is valid */
    ASSERT((tea->n & 1) == 0, false);
    /* start to decrypt every block */
    status ret = true;
    for (int i = 0; i < tea->n; i += 2) {
        ret = tea_block_decrypt(tea, cipher + i, plain + i);
    }
    return ret;
}


/* XTEA encrytion interface and subroutines */
/**
 * @Funticon name: xtea_block_encrypt
 * @description: encrypt a block of plain text(2 uint32_t) using XTEA algorithm
 * @Author: WAHAHA
 * @Date: 2024-03-04 12:10:24
 * @Note: None
 * @param {tea_encipher} *tea
 * @param {uint32_t} *plain
 * @param {uint32_t} *cipher
 * @return {status}
 */
status xtea_block_encrypt(tea_encipher *tea, uint32_t *plain, uint32_t *cipher)
{
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

/**
 * @Funticon name: xtea_block_decrypt
 * @description: decrypt a block of cipher text(2 uint32_t) using XTEA algorithm
 * @Author: WAHAHA
 * @Date: 2024-03-04 12:10:53
 * @Note: None
 * @param {tea_encipher} *tea
 * @param {uint32_t} *cipher
 * @param {uint32_t} *plain
 * @return {status}
 */
status xtea_block_decrypt(tea_encipher *tea, uint32_t *cipher, uint32_t *plain)
{
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

/**
 * @Funticon name: xtea_encrypt
 * @description: interface of XTEA encrytion, encrypt the plain text using XTEA algorithm
 * @Author: WAHAHA
 * @Date: 2024-03-04 12:11:23
 * @Note: the plain whill be checked if it is valid
 * @param {tea_encipher} *tea
 * @param {uint32_t} *plain
 * @param {uint32_t} *cipher
 * @return {status}
 */
status xtea_encrypt(tea_encipher *tea, uint32_t *plain, uint32_t *cipher)
{
    /* check the input */
    ASSERT(tea != NULL && plain != NULL && cipher != NULL, error);
    /* check if the plain text is valid */
    ASSERT((tea->n & 1) == 0, false);
    /* start to encrypt every block */
    status ret = true;
    for (int i = 0; i < tea->n; i += 2) {
        ret = xtea_block_encrypt(tea, plain + i, cipher + i);
    }
    return ret;
}

/**
 * @Funticon name: xtea_decrypt
 * @description: interface of XTEA decrytion, decrypt the cipher text using XTEA algorithm
 * @Author: WAHAHA
 * @Date: 2024-03-04 12:11:54
 * @Note: the cipher whill be checked if it is valid
 * @param {tea_encipher} *tea
 * @param {uint32_t} *cipher
 * @param {uint32_t} *plain
 * @return {status}
 */
status xtea_decrypt(tea_encipher *tea, uint32_t *cipher, uint32_t *plain)
{
    /* check the input */
    ASSERT(tea != NULL && plain != NULL && cipher != NULL, error);
    /* check if the cipher text is valid */
    ASSERT((tea->n & 1) == 0, false);
    /* start to decrypt every block */
    status ret = true;
    for (int i = 0; i < tea->n; i += 2) {
        ret = xtea_block_decrypt(tea, cipher + i, plain + i);
    }
    return ret;
}

/**
 * @Funticon name: xxtea_encrypt
 * @description: interface of XXTEA encrytion, encrypt the plain text using XXTEA algorithm
 * @Author: WAHAHA
 * @Date: 2024-03-04 12:12:31
 * @Note: None
 * @param {tea_encipher} *tea
 * @param {uint32_t} *plain
 * @param {uint32_t} *cipher
 * @return {status}
 */
status xxtea_encrypt(tea_encipher *tea, uint32_t *plain, uint32_t *cipher)
{
    ASSERT(tea != NULL && plain != NULL && cipher != NULL, error);
    uint32_t e, sum = 0, y = plain[0], z = plain[tea->n - 1];
    int rounds = 6 + 52 / (tea->n), p;

    /* start to encrypt */
    for (int i = 0;i < rounds;++i) {
        sum += tea->delta;
        e = (sum >> 2) & 3;
        for (p = 0; p < tea->n - 1; p++) {
            y = plain[p + 1];
            plain[p] += XXTEA_MX;
            z = plain[p];
        }
        y = plain[0];
        plain[tea->n - 1] += XXTEA_MX;
        z = plain[tea->n - 1];
    }
    return true;
}

/**
 * @Funticon name: xxtea_decrypt
 * @description: interface of XXTEA decrytion, decrypt the cipher text using XXTEA algorithm
 * @Author: WAHAHA
 * @Date: 2024-03-04 12:13:09
 * @Note: None
 * @param {tea_encipher} *tea
 * @param {uint32_t} *cipher
 * @param {uint32_t} *plain
 * @return {status}
 */
status xxtea_decrypt(tea_encipher *tea, uint32_t *cipher, uint32_t *plain)
{
    ASSERT(tea != NULL && plain != NULL && cipher != NULL, error);
    uint32_t e, sum, y = cipher[0], z = cipher[tea->n - 1];
    int rounds = 6 + 52 / (tea->n), p;
    sum = rounds * tea->delta;

    /* start to decrypt */
    for (int i = 0; i < rounds; i++) {
        e = (sum >> 2) & 3;
        for (p = tea->n - 1; p > 0; p--) {
            z = cipher[p - 1];
            cipher[p] -= XXTEA_MX;
            y = cipher[p];
        }
        z = cipher[tea->n - 1];
        cipher[0] -= XXTEA_MX;
        y = cipher[0];
        sum -= tea->delta;
    }
    return true;
}