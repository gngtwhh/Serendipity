#include "encode/hex.h"

#include <stdio.h>
#include <string.h>

int main() {
    char text[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_+{}[]|\\:;\"'<>,.?/~`";
    size_t text_len, hex_len;
    byte hex[256] = {0};

    /* bytes to hex */
    bytes_to_hex(text, strlen(text), hex, &hex_len);
    for (int i = 0; i < hex_len; ++i)
        printf("%2X", hex[i]);
    putchar('\n');
    /* hex to bytes */
    memset(text, 0, strlen(text));
    hex_to_bytes(hex, hex_len, text, &text_len);
    for (int i = 0; i < text_len; ++i)
        putchar(text[i]);

    return 0;
}
