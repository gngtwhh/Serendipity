/**
 * @file hex.h
 * @brief This is a header file that contains the declaration of hex encoding and decoding functions.
 * @author WAHAHA
 * @category encode-algorithm
 * @date 2024
 */

#ifndef _ENCODE_HEX_H_
#define _ENCODE_HEX_H_

/* pre-initialization of encode */
#include <encode/encode_pre_init.h>

/* hex transform */
status hex_to_bytes(const char *hex, size_t in_len, byte *bytes, size_t *out_len);

status bytes_to_hex(const byte *bytes, size_t in_len, char *hex, size_t *out_len);

#endif // _ENCODE_HEX_H_