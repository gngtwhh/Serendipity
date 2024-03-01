/**
 * @file  tea.c
 * @brief  This is a header file that contains the declaration of TEA encryption algorithm.
 * @author  WAHAHA
 * @category  encrypt-algorithm
 * @date  2024
 */


#ifndef _ENCRIPT_TEA_
#define _ENCRIPT_TEA_

/* pre-initialization of encrypt */
#include <encrypt/encrypt_pre_init.h>
#include <stdint.h>

/* TEA encipher */
typedef struct tea_encipher {
    uint32_t delta;
    int rounds; // not available for XXTEA
    uint32_t key[4];
} tea_encipher;

tea_encipher* new_tea(uint32_t delta, uint32_t key[4], int rounds);
status free_tea(tea_encipher* tea);

/* common TEA encrytion */
status tea_encrypt(tea_encipher* tea, uint32_t* plain, uint32_t* cipher);
status tea_decrypt(tea_encipher* tea, uint32_t* cipher, uint32_t* plain);

/* XTEA encrytion */
status xtea_encrypt(tea_encipher* tea, uint32_t* plain, uint32_t* cipher);
status xtea_decrypt(tea_encipher* tea, uint32_t* cipher, uint32_t* plain);

/* XXTEA encrytion */
status xxtea_encrypt(tea_encipher* tea, uint32_t* plain, uint32_t* cipher);
status xxtea_decrypt(tea_encipher* tea, uint32_t* cipher, uint32_t* plain);

#endif // _ENCRIPT_TEA_