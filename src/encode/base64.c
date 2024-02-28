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

    /* set the reverse_table */
    encoder->reverse_table = (byte *)malloc(sizeof(byte) * 128);
    generate_reverse_table(encoder->b64_table, encoder->reverse_table);

    return encoder;
}

status free_base64(base64_encoder *encoder) {
    ASSERT(encoder != NULL, error);
    free(encoder->reverse_table);
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
    generate_reverse_table(b64_table, encoder->reverse_table);
    return true;
}

status base64_reset(base64_encoder *encoder) {
    ASSERT(encoder != NULL, error);
    encoder->output_len = 0;
    encoder->b64_table = base64_default_table;
    generate_reverse_table(base64_default_table, encoder->reverse_table);
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
    encoder->output_len = *out_len;
    output[*out_len] = '\0';

    const byte *table = encoder->b64_table;
    int i, j;
    /* encode the input */
    for (i = 0, j = 0; i + 3 <= in_len; i += 3, j += 4) {
        /* common case */
        output[j] = table[input[i] >> 2];
        output[j + 1] = table[(input[i] & 0x03) << 4 | (input[i + 1] >> 4)];
        output[j + 2] = table[(input[i + 1] & 0x0f) << 2 | (input[i + 2] >> 6)];
        output[j + 3] = table[input[i + 2] & 0x3f];
    }
    /* fix the padding */
    if (i < in_len) {
        /* 2 bytes left */
        if (pad_len == 1) {
            output[j++] = table[input[i] >> 2];
            output[j++] = table[(input[i] & 0x03) << 4 | (input[i + 1] >> 4)];
            output[j++] = table[(input[i + 1] & 0x0f) << 2];
            output[*out_len - 1] = '=';
        }
        /* 1 byte left */
        else if (pad_len == 2) {
            output[j++] = table[input[i] >> 2];
            output[j++] = table[(input[i] & 0x03) << 4];
            output[*out_len - 1] = '=';
            output[*out_len - 2] = '=';
        }
    }
    return true;
}

status base64_decode(base64_encoder *encoder, const byte *input, int in_len,
    byte *output, int *out_len) {
    /* check the parameters */
    ASSERT(input != NULL, error);
    ASSERT(in_len > 0, error);
    ASSERT(output != NULL, error);
    // ASSERT(out_len != NULL, error);

    /* calculate the length of output */
    int pad_len = 0;
    if (input[in_len - 1] == '=') {
        pad_len++;
        if (input[in_len - 2] == '=') {
            pad_len++;
        }
    }
    *out_len = in_len / 4 * 3 - pad_len;
    encoder->output_len = *out_len;
    output[*out_len] = '\0';

    const byte *re_table = encoder->reverse_table;
    int i, j;

    /* decode the input */
    // 000000 00|1111 1111|00 000000
    // 000000|00 1111|1111 00|000000
    // a      b       c       d
    for (i = 0, j = 0;i + 4 <= in_len;i += 4, j += 3) {
        output[j] = (re_table[input[i]] << 2) | (re_table[input[i + 1]] >> 4);
        output[j + 1] = (re_table[input[i + 1]] << 4) | (re_table[input[i + 2]] >> 2);
        output[j + 2] = (re_table[input[i + 2]] << 6) | re_table[input[i + 3]];
    }
    /* fix the padding */
    /* 1 '=' , 2 byte left */
    if (pad_len == 1) {
        output[j++] = (re_table[input[i]] << 2) | (re_table[input[i + 1]] >> 4);
        output[j++] = (re_table[input[i + 1]] << 4) | (re_table[input[i + 2]] >> 2);
    }
    /* 2 '=' , 1 byte left */
    else if (pad_len == 2) {
        output[j++] = (re_table[input[i]] << 2) | (re_table[input[i + 1]] >> 4);
    }
    output[j] = '\0';
    return true;
}
