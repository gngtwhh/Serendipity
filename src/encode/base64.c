/**
 * @file base64.c
 * @brief base64 implementation
 * @author WAHAHA
 * @category encode-algorithm
 * @date 2024
 */

#include <encode/base64.h>
#include <stdlib.h>

 /**
 typedef struct base64_encoder {
     const byte *b64_table;
     status(*reset)(void);
     status(*encode)(const byte *input, byte *output, const byte *b64_table);
     status(*decode)(const byte *input, byte *output, const byte *b64_table);
 } base64_encoder;
 */

 /* base64 encoder constructor and destructor */
base64_encoder *new_base64(const byte *b64_table) {
    base64_encoder *encoder = (base64_encoder *)malloc(sizeof(base64_encoder));
    if (encoder == NULL)
        return NULL;

    /* set the b64_table */
    if (b64_table == NULL)
        encoder->b64_table = base64_default_table;
    else
        encoder->b64_table = b64_table;
    return encoder;
}

status free_base64(base64_encoder *encoder) {
    ASSERT(encoder != NULL, error);
    free(encoder);
    return true;
}


/* base64 operations */
status generate_reverse_table(const byte *b64_table, byte *reverse_table) {
    for (int i = 0; i < 64; i++) {
        reverse_table[b64_table[i]] = i;
    }
    return true;
}

status base64_change_table(base64_encoder *encoder, const byte *b64_table) {
    ASSERT(encoder != NULL, error);
    encoder->b64_table = b64_table;
    return true;
}

status base64_reset(base64_encoder *encoder) {
    ASSERT(encoder != NULL, error);
    encoder->output_len = 0;
    encoder->b64_table = base64_default_table;
    return true;
}

status base64_encode(base64_encoder *encoder, const byte *input, int in_len,
    byte *output, int *out_len) {
    /* check the parameters */
    ASSERT(input != NULL, error);
    ASSERT(in_len > 0, error);
    ASSERT(output != NULL, error);
    // ASSERT(out_len != NULL, error);

    /* calculate the length of output */
    int pad_len = 0;
    if (in_len % 3 != 0) {
        pad_len = 3 - in_len % 3;
    }
    *out_len = in_len / 3 * 4 + pad_len;
    output[*out_len] = '\0';

    const byte *table = encoder->b64_table;

    /* encode the input */
    for (int i = 0, j = 0; i < in_len; i += 3, j += 4) {
        /* common case */
        output[j] = table[input[i] >> 2];
        output[j + 1] = table[(input[i] & 0x03) << 4 | (input[i + 1] >> 4)];
        output[j + 2] = table[(input[i + 1] & 0x0f) << 2 | (input[i + 2] >> 6)];
        output[j + 3] = table[input[i + 2] & 0x3f];
    }
    /* fix the padding */
    if (pad_len == 1) {
        output[*out_len - 1] = '=';
    } else if (pad_len == 2) {
        output[*out_len - 1] = '=';
        output[*out_len - 2] = '=';
    }

    return true;
}

status base64_decode(base64_encoder *encoder, const byte *input, int in_len,
    byte *output, int *out_len) {
    
}
