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
const byte *base64_default_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/* base64 encoder */
typedef struct base64_encoder {
    const byte *b64_table;
    status(*reset)(void);
    status(*encode)(const byte *input, byte *output, const byte *b64_table);
    status(*decode)(const byte *input, byte *output, const byte *b64_table);
} base64_encoder;

/* base64 encoder constructor and destructor */
base64_encoder *new_base64(const byte *b64_table);
status free_base64(base64_encoder *encoder);

/* base64 operations */
status base64_reset(void);
status base64_encode(const byte *input, byte *output, const byte *b64_table);
status base64_decode(const byte *input, byte *output, const byte *b64_table);

#endif