/**
 * @file hex.c
 * @brief hex transform implementation
 * @author WAHAHA
 * @category encode-algorithm
 * @date 2024
 */

#include <encode/hex.h>
#include <stdlib.h>

 /* hex transform */
status hex_to_bytes(const char *hex, size_t in_len,
    byte *bytes, size_t *out_len) {
    ASSERT(hex != NULL && bytes != NULL && out_len != NULL, error);
    ASSERT(in_len % 2 == 0, error);

    *out_len = in_len / 2;
    for (size_t i = 0;i < in_len;i += 2) {
        
    }
}

status bytes_to_hex(const byte *bytes, size_t in_len,
    char *hex, size_t *out_len);
