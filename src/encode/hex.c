/**
 * @file hex.c
 * @brief hex transform implementation
 * @author WAHAHA
 * @category encode-algorithm
 * @date 2024
 */


#include <encode/hex.h>
#include <stdio.h>
#include <string.h>

 /* hex transform */
status hex_to_bytes(const char *hex, size_t in_len,
    byte *bytes, size_t *out_len) {
    ASSERT(hex != NULL && bytes != NULL && out_len != NULL, error);
    ASSERT(in_len % 2 == 0, error);

    memset(bytes, 0, in_len / 2 + 1);
    *out_len = in_len / 2;
    for (size_t i = 0;i < in_len;++i) {
        char c = hex[i];
        int value = 0;
        if (c >= '0' && c <= '9')
            value = c - '0';
        else if (c >= 'a' && c <= 'f')
            value = c - 'a' + 10;
        else if (c >= 'A' && c <= 'F')
            value = c - 'A' + 10;
        else {
            printf("hex_to_bytes error: incorrect hex character\r\n");
            return false;
        }
        bytes[i / 2] += value << (4 * (1 - (i & 1)));
    }
    bytes[*out_len] = '\0';
    return true;
}

status bytes_to_hex(const byte *bytes, size_t in_len,
    char *hex, size_t *out_len) {
    ASSERT(bytes != NULL && hex != NULL && out_len != NULL, error);
    ASSERT(in_len > 0, error);

    const char *hex_table = "0123456789abcdef";

    *out_len = in_len * 2;
    size_t out_idx = 0;
    for (size_t i = 0;i < in_len;++i) {
        hex[out_idx++] = hex_table[bytes[i] >> 4];
        hex[out_idx++] = hex_table[bytes[i] & 0x0f];
    }
    hex[out_idx] = '\0';
    return true;
}
