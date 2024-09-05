/**
 * @file: morse.h
 * @description: This is a header file that contains the declaration of the Morse code encoding function.
 * @author: WAHAHA
 * @Date: 2024/9/5 下午1:38
 * @FilePath: Serendipity/include/encode/morse.h
 * @category: encode
 */

#ifndef SERENDIPITY_MORSE_H
#define SERENDIPITY_MORSE_H

#include <stdio.h>
#include <encode/encode_pre_init.h>

// Morse Code Struct
typedef struct morse_tree_node_s {
    int ascii;
    struct morse_tree_node_s *left;
    struct morse_tree_node_s *right;
} morse_tree_node_t;

typedef struct morse_ctx_s {
    morse_tree_node_t *root; // morse tree root
    const char **morse_table_ascii; // morse to ascii
    char error_char; // error char
    int error_flag; // error flag
} morse_ctx_t;

// Decode Morse code to ASCII
status morse_decode(const char *str, char *buffer, size_t buffer_size);
// Encode ASCII to Morse code
status morse_encode(const char *str, char *buffer, size_t buffer_size);

#endif //SERENDIPITY_MORSE_H
