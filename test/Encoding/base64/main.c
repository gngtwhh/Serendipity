/*
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
    char table[] = "qaCpwYM2tO/RP0XeSZv8kLd6nfA7UHJ1No4gF5zr3VsBQbl9juhEGymc+WTxIiDK";
    base64_encoder *b64 = new_base64(table);
    char str[] = "AMHo7dLxUEabf6Z3PdWr6cOy75i4fdfeUzL17kaV7rG=";
    int len = strlen(str);
    char dec[100];
    base64_decode(b64,str,len,dec,NULL);
    puts(dec);
    return 0;
}