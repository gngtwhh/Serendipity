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
    char table[] = "0123456789XYZabcdefghijklABCDEFGHIJKLMNOPQRSTUVWmnopqrstuvwxyz+/=";
    base64_encoder *b64 = new_base64((uint8_t *) table);
    char *input = "hello";
    byte output[100];
    base64_encode(b64, input, strlen(input), output, NULL);
    puts(output);

    return 0;
}