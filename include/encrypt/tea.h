/**
 * @file  tea.c
 * @brief  This is a header file that contains the declaration of TEA encryption algorithm.
 * @author  WAHAHA
 * @category  encrypt-algorithm
 * @date  2024
 */


#ifndef ENCRYPT_TEA
#define ENCRYPT_TEA

/* pre-initialization of encrypt */
#include <encrypt/encrypt_pre_init.h>
#include <stdint.h>

/* TEA encipher */
typedef struct tea_encipher {
    uint32_t delta;
    int rounds; // not available for XXTEA
    int n; // the count of blocks
    uint32_t key[4];
} tea_encipher;

tea_encipher *new_tea(uint32_t delta, const uint32_t key[4], int rounds);

status free_tea(tea_encipher *tea);

/* common TEA encryption */
status tea_encrypt(tea_encipher *tea, const uint32_t *plain, uint32_t *cipher);

status tea_decrypt(tea_encipher *tea, const uint32_t *cipher, uint32_t *plain);

static status tea_block_encrypt(tea_encipher *tea, const uint32_t *plain, uint32_t *cipher);

static status tea_block_decrypt(tea_encipher *tea, const uint32_t *cipher, uint32_t *plain);

/* XTEA encryption */
status xtea_encrypt(tea_encipher *tea, const uint32_t *plain, uint32_t *cipher);

status xtea_decrypt(tea_encipher *tea, const uint32_t *cipher, uint32_t *plain);

static status xtea_block_encrypt(tea_encipher *tea, const uint32_t *plain, uint32_t *cipher);

static status xtea_block_decrypt(tea_encipher *tea, const uint32_t *cipher, uint32_t *plain);

/* XXTEA encryption */
status xxtea_encrypt(tea_encipher *tea, const uint32_t *plain, uint32_t *cipher);

status xxtea_decrypt(tea_encipher *tea, const uint32_t *cipher, uint32_t *plain);

#endif // ENCRYPT_TEA