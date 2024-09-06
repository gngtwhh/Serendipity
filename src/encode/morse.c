/**
 * @file: morse.c
 * @description: This is a source file that contains the implementation of the Morse code encoding function.
 * @author: WAHAHA
 * @Date: 2024/9/5 下午1:38
 * @FilePath: Serendipity/src/encode/morse.c
 * @category: encode
 */

#include <malloc.h>
#include <string.h>
#include "encode/morse.h"

// Used to replace error morse code
#define MORSE_ERROR_CHAR  '?'

// ASCII to Morse code
const char *MORSE_TABLE_ASCII[] = {
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, "-.-.--", ".-..-.", NULL, "...-..-", NULL, ".-...", ".----.",
        "-.--.", "-.--.-", NULL, ".-.-.", "--..--", "-....-", ".-.-.-", "-..-.", "-----", ".----",
        "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", "---...", "-.-.-.",
        NULL, "-...-", NULL, "..--..", ".--.-.", ".-", "-...", "-.-.", "-..", ".",
        "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---",
        ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--",
        "--..", NULL, NULL, NULL, NULL, "..--.-", NULL, ".-", "-...", "-.-.",
        "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--",
        "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--",
        "-..-", "-.--", "--..", NULL, NULL, NULL, NULL, NULL,
};

// Morse Context
static morse_ctx_t *ctx = NULL;

static int parse_init(const char *str, const char **start, const char **end) {
    *start = *end = str; // Initialize the start and end pointers to the first character of the string
    return 0;
}

static int parse_next(const char **start, const char **end) {
    if (*start == NULL || *end == NULL) {
        return -1;
    }

    // Skip any leading spaces
    *start = *end;
    while (**start == ' ') (*start)++;
    // Move the end pointer to the next space or '\0'
    *end = *start;
    while (**end != '\0' && **end != ' ') (*end)++;
    // Check if reached the end of the string
    if (**start == '\0')
        return 1; // End of string
    return 0;
}

static void tree_add_code(const char *code, int ch) {
    size_t len = strlen(code);
    morse_tree_node_t *cur = ctx->root;
    for (size_t i = 0; i < len; i++) {
        if (code[i] == '.') {
            if (cur->left == NULL) {
                cur->left = (morse_tree_node_t *) malloc(sizeof(morse_tree_node_t));
                cur->left->ascii = 0;
                cur->left->left = cur->left->right = NULL;
            }
            cur = cur->left;
        } else if (code[i] == '-') {
            if (cur->right == NULL) {
                cur->right = (morse_tree_node_t *) malloc(sizeof(morse_tree_node_t));
                cur->right->ascii = 0;
                cur->right->left = cur->right->right = NULL;
            }
            cur = cur->right;
        }
    }
    cur->ascii = ch;
}

static status init_morse_ctx() {
    ctx = (morse_ctx_t *) malloc(sizeof(morse_ctx_t));
    if (ctx == NULL) {
        return failed;
    }
    ctx->morse_table_ascii = MORSE_TABLE_ASCII;
    ctx->error_char = MORSE_ERROR_CHAR;
    ctx->error_flag = false;
    ctx->root = (morse_tree_node_t *) malloc(sizeof(morse_tree_node_t));
    if (ctx->root == NULL) {
        return failed;
    }
    ctx->root->ascii = 0;
    ctx->root->left = ctx->root->right = NULL;

    for (int i = 0; i < 128; i++) {
        if (ctx->morse_table_ascii[i] != NULL) {
            tree_add_code(ctx->morse_table_ascii[i], i);
        }
    }

    return true;
}

static int find(const char *code, size_t len) {
    if (code == NULL) {
        return -1;
    }
    morse_tree_node_t *cur = ctx->root;
    for (size_t i = 0; i < len; i++) {
        if (code[i] == '.') {
            cur = cur->left;
        } else if (code[i] == '-') {
            cur = cur->right;
        }
        if (cur == NULL) {
            return -1;
        }
    }
    if (cur->ascii == 0) {
        ctx->error_flag = true;
        return ctx->error_char;
    }
    return cur->ascii;
}

/**
 * @Funticon name: morse_decode
 * @description: Decode Morse code to ASCII
 * @Author: WAHAHA
 * @Date: 2024-9-5 14:26:42
 * @Note: None
 * @param {const char *} str - Morse code string
 * @param {char *} buffer - Buffer to store decoded ASCII string
 * @param {size_t} buffer_size - Size of buffer, must be large enough to store decoded string
 * @return {status} - Status of the operation
 */
status morse_decode(const char *str, char *buffer, size_t buffer_size) {
    ASSERT(buffer_size > 0, error);
    ASSERT(str != NULL && buffer != NULL, error);

    // Init context
    if (ctx == NULL) {
        init_morse_ctx();
    }

    // Start decoding
    const char *start, *end;
    size_t idx = 0;
    parse_init(str, &start, &end);
    while (!parse_next(&start, &end)) {
        if (idx >= buffer_size - 1) {
            return error;
        }
        buffer[idx++] = (char) find(start, end - start);
    }
    buffer[idx] = '\0';
    if (ctx->error_flag == true) {
        return false;
    }
    return true;
}


// Encode ASCII to Morse code
status morse_encode(const char *str, char *buffer, size_t buffer_size) {
    ASSERT(buffer_size > 0, error);
    ASSERT(str != NULL && buffer != NULL, error);
    if (ctx == NULL) {
        init_morse_ctx();
    }
    size_t idx = 0;
    buffer[0] = '\0';
    for (size_t i = 0; i < strlen(str); i++) {
        if (ctx->morse_table_ascii[str[i]] != NULL) {
            idx += strlen(ctx->morse_table_ascii[str[i]]);
            if (idx++ >= buffer_size - 1) {
                return error;
            }
            strcat(buffer, ctx->morse_table_ascii[str[i]]);
            strcat(buffer, " ");
        }
    }
    buffer[idx - 1] = '\0'; // Remove the last space
    return true;
}
