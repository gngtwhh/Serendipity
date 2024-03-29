/**
 * @file base64.h
 * @brief This is a header file that contains the declaration of base64 encode and decode algorithm.
 * @author WAHAHA
 * @category encode-algorithm
 * @date 2024
 */

#ifndef ENCODE_BASE64_H
#define ENCODE_BASE64_H

/* pre-initialization of encode */
#include <encode/encode_pre_init.h>

/* base64 data */
static byte *base64_default_table = (unsigned char*)"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/* base64 encoder */
typedef struct base64_encoder {
    byte* b64_table;
    /**
     * The characters in b64_table may not be ASCII characters,
     * so we need to use 256
     */
    byte* reverse_table;
    int output_len;
} base64_encoder;

/* base64 encoder constructor and destructor */
base64_encoder *new_base64(const byte *b64_table);
status free_base64(base64_encoder *encoder);

/* base64 table operations */
static status generate_reverse_table(const byte *b64_table, byte *reverse_table);
status base64_change_table(base64_encoder *encoder, const byte *b64_table);

/* base64 operations */
status base64_reset(base64_encoder *encoder);
status base64_encode(base64_encoder *encoder, const byte *input, int in_len,
    byte *output);
status base64_decode(base64_encoder *encoder, const byte *input, int in_len,
    byte *output);

#endif // ENCODE_BASE64_H