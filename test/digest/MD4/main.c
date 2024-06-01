#include "digest/md4.h"

#include <stdio.h>
#include <string.h>


int main() {
    byte data0[] = "Hello, world!";
    byte data1[] = "abcdefghijklmnopqrstuvwxyz";
    byte data2[] = "12345678901234567890";

    char expected0[] = "0abe9ee1f376caa1bcecad9042f16e73";
    char expected1[] = "d79e1c308aa5bbcdeea8ed63df412da9";
    char expected2[] = "3fee688b3e2a76a7eb5f78e840ebd67d";

    size_t data_bit_size0 = strlen((char *) data0) * 8;
    size_t data_bit_size1 = strlen((char *) data1) * 8;
    size_t data_bit_size2 = strlen((char *) data2) * 8;

    char digest[33] = {0};

    md4(data0, data_bit_size0, digest);
    if (strcmp(digest, expected0) != 0) {
        printf("data0: failed\n");
    } else {
        printf("data0: passed\n");
    }

    md4(data1, data_bit_size1, digest);
    if (strcmp(digest, expected1) != 0) {
        printf("data1: failed\n");
    } else {
        printf("data1: passed\n");
    }

    md4(data2, data_bit_size2, digest);
    if (strcmp(digest, expected2) != 0) {
        printf("data2: failed\n");
    } else {
        printf("data2: passed\n");
    }


    return 0;
}