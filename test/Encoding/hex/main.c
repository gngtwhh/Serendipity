#include "encode/hex.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    byte bytes[] = "hello world!";
    size_t out_len;
    char hex[100];
    bytes_to_hex(bytes, strlen(bytes), hex, &out_len);
    puts(hex);
    hex_to_bytes(hex, strlen(hex), bytes, &out_len);
    puts(bytes);
    return 0;
}