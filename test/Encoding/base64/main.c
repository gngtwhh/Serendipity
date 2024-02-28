#include "encode/base64.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    byte table[64];
    for (int i = 0;i < 64;++i) {
        table[i] = i + 128 + 40;
    }
    for (int i = 0;i < 64;++i)
        printf("\\x%2x", table[i]);
    printf("\n");
    base64_encoder *b64 = new_base64(table);
    byte str[] = "Hello World!";
    byte enc[20] = { 0 };
    int res_len;
    base64_encode(b64, str, strlen((char *)str), enc, &res_len);
    printf("encoded: ");
    for (int i = 0;i < res_len;++i)
        printf("\\x%2x", enc[i]);
    printf("\n");
    base64_decode(b64, enc, b64->output_len, str, &res_len);
    printf("decoded: %s\n", str);
    free_base64(b64);
    return 0;
}