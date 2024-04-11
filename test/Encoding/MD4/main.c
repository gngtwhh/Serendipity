#include "encode/md4.h"

#include <stdio.h>
#include <string.h>


int main() {
//    byte data[] = "123456";
//    data[6] = 0xF0;
//    size_t data_bit_size = 48 + 4;

    byte data[] = "Hello, world!";
    size_t data_bit_size = strlen((char *) data) * 8;

    size_t block_count = 0;

    // debug print of md4_padding
//    uint32_t *data_padding = md4_padding(data, data_bit_size, &block_count);
//    for (size_t i = 0; i < block_count * 16; i++) {
//        byte* p = (byte *) &data_padding[i];
//        printf("%08x ", data_padding[i]);
//        if ((i + 1) % 4 == 0) {
//            printf("\r\n");
//        }
//    }
//    uint64_t len = *(uint64_t *) (&data_padding[block_count * 16 - 2]);
//    printf("len: %016llx\r\n", len);

    char digest[33] = {0};
    md4(data, data_bit_size, digest);
    printf("original: \"%s\"\r\n", data);
    printf("md4: %s\r\n", digest);

    return 0;
}