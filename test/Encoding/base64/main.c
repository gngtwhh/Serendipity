/**
 * @file: File name
 * @description: Briefly describe the file
 * @author: WAHAHA
 * @Date: 2024-02-28 11:06:35
 * @LastEditTime: 2024-03-06 00:42:03
 * @FilePath: \Serendipity\test\Encoding\base64\main.c
 * @category: File category
 */
#include "encode/base64.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    base64_encoder *b64 = new_base64(NULL);
    char str[] = "hello world";
    int len = strlen(str);
    char dec[100];
    base64_encode(b64, str, len, dec, NULL);
    puts(dec);
    printf("len = %d\n", b64->output_len);
    char str2[100];
    base64_decode(b64, dec, 16, str2, NULL);
    puts(str2);
    printf("len = %d\n", b64->output_len);

    return 0;
}