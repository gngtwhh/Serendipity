#include "encode/base64.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char table[] = "0123456789XYZabcdefghijklABCDEFGHIJKLMNOPQRSTUVWmnopqrstuvwxyz+/=";
    base64_encoder *b64 = new_base64((uint8_t *) table);
    char input[] = "hello";
    byte output[100];

    base64_encode(b64, input, strlen(input), output);
    puts(output);
    base64_decode(b64, output, strlen(output), input);
    puts(input);
    free_base64(b64);

    return 0;
}