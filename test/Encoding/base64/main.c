#include "encode/base64.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
    base64_encoder *b64 = new_base64(NULL);
    byte str[] = "hello world!";
    byte enc[20] = { 0 };
    int res_len;
    base64_encode(b64, str, strlen((char *)str), enc, &res_len);
    printf("encoded: %s\n", enc);

    return 0;
}