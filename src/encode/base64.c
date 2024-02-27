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
    /* set the pointers to the functions */
    encoder->reset = base64_reset;
    encoder->encode = base64_encode;
    encoder->decode = base64_decode;
    return encoder;
}

status free_base64(base64_encoder *encoder) {
    ASSERT(encoder != NULL, error);
    free(encoder);
    return true;
}

/* base64 operations */
status base64_reset(void){
    
}

status base64_encode(const byte *input, byte *output, const byte *b64_table);

status base64_decode(const byte *input, byte *output, const byte *b64_table);
