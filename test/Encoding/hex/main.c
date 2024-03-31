#include "encode/hex.h"

#include <stdio.h>
#include <string.h>

int main() {
    byte bytes[] = "hello world!";
    size_t out_len;
    char hex_test1[100];
    bytes_to_hex(bytes, strlen((char *) bytes), hex_test1, &out_len);
    puts(hex_test1);
    hex_to_bytes(hex_test1, strlen(hex_test1), bytes, &out_len);
    bytes[out_len] = '\0';
    puts((char *) bytes);

    char hex_test2[] = "68656c6c6f20776fk26c6421";
    hex_to_bytes(hex_test2, strlen(hex_test2), bytes, &out_len);
    bytes[out_len] = '\0';
    puts((char *) bytes);
    return 0;
}