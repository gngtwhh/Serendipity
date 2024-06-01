#include "digest/md5.h"

#include <stdio.h>
#include <string.h>


int main() {
    byte data0[] = "Hello, world!";
    byte data1[] = "abcdefghijklmnopqrstuvwxyz";
    byte data2[] = "12345678901234567890";

    char expected0[] = "6cd3556deb0da54bca060b4c39479839";
    char expected1[] = "c3fcd3d76192e4007dfb496cca67e13b";
    char expected2[] = "fd85e62d9beb45428771ec688418b271";

    size_t data_bit_size0 = strlen((char *) data0) * 8;
    size_t data_bit_size1 = strlen((char *) data1) * 8;
    size_t data_bit_size2 = strlen((char *) data2) * 8;

    char digest[33] = {0};

    md5(data0, data_bit_size0, digest);
    if (strcmp(digest, expected0) != 0) {
        printf("data0: failed\n");
    } else {
        printf("data0: passed\n");
    }

    md5(data1, data_bit_size1, digest);
    if (strcmp(digest, expected1) != 0) {
        printf("data1: failed\n");
    } else {
        printf("data1: passed\n");
    }

    md5(data2, data_bit_size2, digest);
    if (strcmp(digest, expected2) != 0) {
        printf("data2: failed\n");
    } else {
        printf("data2: passed\n");
    }

    return 0;
}