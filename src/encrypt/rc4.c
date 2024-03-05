/*
 * @file: rc4.c
 * @description: RC4 encryption algorithm implementation
 * @author: WAHAHA
 * @Date: 2024-03-05 14:15:45
 * @LastEditTime: 2024-03-05 14:46:00
 * @FilePath: \Serendipity\src\encrypt\rc4.c
 * @category: encrypt-algorithm
 */

#include <encrypt/rc4.h>



rc4_encipher *new_rc4(NULL){}
status free_rc4(rc4_encipher *rc4);

status rc4_set_key(rc4_encipher *rc4, uint8_t *key, int key_len);
status rc4_crypt(rc4_encipher *rc4, uint8_t *data, int data_len, uint8_t *out_data);
