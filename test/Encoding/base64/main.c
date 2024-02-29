#include "encode/base64.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    base64_encoder *b64 = new_base64(NULL);
    byte str[] = "Hello World!";
    byte enc[20] = { 0 };
    int res_len;
    base64_encode(b64, str, strlen((char *)str), enc, &res_len);
    printf("encoded: ");
    for (int i = 0;i < res_len;++i)
        printf("\\x%2x", enc[i]);
    printf("\nencoded: %s\n", enc);
    printf("\n");
    base64_decode(b64, enc, b64->output_len, str, &res_len);
    printf("decoded: %s\n", str);
    free_base64(b64);
    return 0;
}