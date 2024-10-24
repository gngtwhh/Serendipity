/**
 * @file: base64.c
 * @description: base64 implementation
 * @author: WAHAHA
 * @Date: 2024-02-28 11:06:35
 * @LastEditTime: 2024-03-06 00:48:03
 * @FilePath: \Serendipity\src\encode\base64.c
 * @category: encode-algorithm
 */

#include <encode/base64.h>
#include <stdlib.h>
#include <string.h>

/**
 typedef struct base64_encoder {
    const byte *b64_table;
        status(*reset)(void);
        status(*encode)(const byte *input, byte *output, const byte *b64_table);
        status(*decode)(const byte *input, byte *output, const byte *b64_table);
} base64_encoder;
*/

/* base64 encoder constructor and destructor */
/**
 * @Funticon name: new_base64
 * @description: create a new base64 encoder
 * @Author: WAHAHA
 * @Date: 2024-03-04 12:15:45
 * @Note: allow the b64_table to be NULL, if NULL, use the default table
 * @param {byte} *b64_table
 * @return {base64_encoder *}
 */
base64_encoder *new_base64(const byte *b64_table) {
    base64_encoder *encoder = (base64_encoder *) malloc(sizeof(base64_encoder));
    if (encoder == NULL)
        return NULL;
    /* alloc the b64_table and reverse_table */
    encoder->b64_table = (byte *) malloc(64 * sizeof(byte));
    encoder->reverse_table = (byte *) malloc(256 * sizeof(byte));
    // the parameter for free() is allowed to be NULL
    if (encoder->b64_table == NULL || encoder->reverse_table == NULL) {
        free(encoder->b64_table);
        free(encoder->reverse_table);
        free(encoder);
        return NULL;
    }

    /* set the b64_table */
    if (b64_table == NULL)
        memcpy(encoder->b64_table, base64_default_table, 64);
    else
        memcpy(encoder->b64_table, b64_table, 64);

    /* set the reverse_table */
    generate_reverse_table(encoder->b64_table, encoder->reverse_table);

    return encoder;
}

/**
 * @Funticon name: free_base64
 * @description: free the base64 encoder
 * @Author: WAHAHA
 * @Date: 2024-03-04 12:16:25
 * @Note: None
 * @param {base64_encoder} *encoder
 * @return {status}
 */
status free_base64(base64_encoder *encoder) {
    ASSERT(encoder != NULL, error);
    free(encoder->b64_table);
    free(encoder->reverse_table);
    free(encoder);
    return true;
}


/* base64 operations */
/**
 * @Funticon name: generate_reverse_table
 * @description: generate the reverse table of the base64 table
 * @Author: WAHAHA
 * @Date: 2024-03-04 12:17:25
 * @Note: None
 * @param {byte} *b64_table
 * @param {byte} *reverse_table
 * @return {status}
 */
static status generate_reverse_table(const byte *b64_table, byte *reverse_table) {
    /**
     * Fill with 0xff, so if 0xff is accessed later,
     * it means that this character is not in the base64 table,
     * used for error detection
     */
    memset(reverse_table, 0xff, 256 * sizeof(byte));
    for (int i = 0; i < 64; i++) {
        reverse_table[b64_table[i]] = i;
    }
    reverse_table['='] = 0; // padding character
    return true;
}

/**
 * @Funticon name: base64_change_table
 * @description: change the base64 table of the encoder
 * @Author: WAHAHA
 * @Date: 2024-03-04 12:18:23
 * @Note: also change the reverse table
 * @param {base64_encoder} *encoder
 * @param {byte} *b64_table
 * @return {status}
 */
status base64_change_table(base64_encoder *encoder, const byte *b64_table) {
    ASSERT(encoder != NULL, error);
    ASSERT(b64_table != NULL, error);
    memcpy(encoder->b64_table, b64_table, 64);
    generate_reverse_table(b64_table, encoder->reverse_table);
    return true;
}

/**
 * @Funticon name: base64_reset
 * @description: reset the base64 encoder
 * @Author: WAHAHA
 * @Date: 2024-03-04 12:19:07
 * @Note: None
 * @param {base64_encoder} *encoder
 * @return {status}
 */
status base64_reset(base64_encoder *encoder) {
    ASSERT(encoder != NULL, error);
    encoder->output_len = 0;
    memcpy(encoder->b64_table, base64_default_table, 64);
    generate_reverse_table(base64_default_table, encoder->reverse_table);
    return true;
}

/**
 * @Funticon name: base64_encode
 * @description: encode the input to base64
 * @Author: WAHAHA
 * @Date: 2024-03-04 12:19:32
 * @Note: length of output will be stored in encoder->output_len
 * @param {base64_encoder} *encoder
 * @param {byte} *input
 * @param {int} in_len
 * @param {byte} *output
 * @return {status}
 */
status base64_encode(base64_encoder *encoder, const byte *input, int in_len,
                     byte *output) {
    /* check the parameters */
    ASSERT(input != NULL, error);
    ASSERT(in_len > 0, error);
    ASSERT(output != NULL, error);
    // ASSERT(out_len != NULL, error);

    /* calculate the length of output */
    if (in_len % 3 != 0)
        encoder->output_len = (in_len / 3 + 1) * 4;
    else
        encoder->output_len = in_len / 3 * 4;


    output[encoder->output_len] = '\0';

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
        if (in_len % 3 == 2) {
            output[j++] = table[input[i] >> 2];
            output[j++] = table[(input[i] & 0x03) << 4 | (input[i + 1] >> 4)];
            output[j++] = table[(input[i + 1] & 0x0f) << 2];
            output[encoder->output_len - 1] = '=';
        }
            /* 1 byte left */
        else if (in_len == 1) {
            output[j++] = table[input[i] >> 2];
            output[j++] = table[(input[i] & 0x03) << 4];
            output[encoder->output_len - 1] = '=';
            output[encoder->output_len - 2] = '=';
        }
    }

    return true;
}

/**
 * @Funticon name: base64_decode
 * @description: decode the input from base64
 * @Author: WAHAHA
 * @Date: 2024-03-04 12:22:21
 * @Note: length of output will be stored in encoder->output_len
 * @param {base64_encoder} *encoder
 * @param {byte} *input
 * @param {int} in_len
 * @param {byte} *output
 * @return {status}
 */
status base64_decode(base64_encoder *encoder, const byte *input, int in_len,
                     byte *output) {
    /* check the parameters */
    ASSERT(input != NULL, error);
    ASSERT(in_len > 0, error);
    ASSERT(output != NULL, error);

    /* check that if the input is valid */
    if (in_len & 0x03) { // in_len % 4 != 0
        printf("base64_decode error: the length of input is not a multiple of 4\r\n");
        output[0] = '\0';
        return false;
    }
    status valid = true;
    for (int i = 0; i < in_len; i++) {
        if (encoder->reverse_table[input[i]] == 0xff) {
            valid = false;
            break;
        }
        if (input[i] == '=' && i < in_len - 2) {
            valid = false;
            break;
        }
    }
    if (!valid) {
        printf("base64_decode error: the input is not a valid base64 string\r\n");
        output[0] = '\0';
        return false;
    }


    /* calculate the length of output */
    int pad_len = 0;
    if (input[in_len - 1] == '=') {
        pad_len++;
        if (input[in_len - 2] == '=') {
            pad_len++;
        }
    }
    encoder->output_len = in_len / 4 * 3 - pad_len;

    output[encoder->output_len] = '\0';

    const byte *re_table = encoder->reverse_table;
    int i, j;

    /* decode the input */
    // 000000 00|1111 1111|00 000000
    // 000000|00 1111|1111 00|000000
    // a      b       c       d
    for (i = 0, j = 0; i + 4 <= in_len; i += 4, j += 3) {
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
