/**
 * @file base64.h
 * @brief This is a header file that contains the declaration of base64 encode and decode algorithm.
 * @author WAHAHA
 * @category encode-algorithm
 * @date 2024
 */

#ifndef _BASE64_H_
#define _BASE64_H_

 /* pre-initialization of encode */
#include "encode/encode_pre_init.h"

/* base64 data */
static const byte *base64_default_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static byte base64_global_reverse_table[128] = { 0 };

/* base64 encoder */
typedef struct base64_encoder {
    const byte *b64_table;
    byte *reverse_table;
    int output_len;
} base64_encoder;

/* base64 encoder constructor and destructor */
base64_encoder *new_base64(const byte *b64_table);
status free_base64(base64_encoder *encoder);

/* base64 table operations */
status generate_reverse_table(const byte *b64_table, byte *reverse_table);
status base64_change_table(base64_encoder *encoder, const byte *b64_table);

/* base64 operations */
status base64_reset(base64_encoder *encoder);
status base64_encode(base64_encoder *encoder, const byte *input, int in_len,
    byte *output, int *out_len);
status base64_decode(base64_encoder *encoder, const byte *input, int in_len,
    byte *output, int *out_len);

#endif