#include <stdio.h>
#include "misc/bf.h"

const char* code_file_name = "D:/Data/code/cpp/Serendipity/test/misc/bf_runner/bf_code.bf";

void get_code(char** code, int* len) {
    FILE* code_file = fopen(code_file_name, "r");
    if (code_file == NULL) {
        printf("[ERROR] Failed to open code file %s\n", code_file_name);
        return;
    }
    fseek(code_file, 0, SEEK_END);
    *len = ftell(code_file);
    *code = malloc(*len + 1);
    fseek(code_file, 0, SEEK_SET);
    fread(*code, 1, *len, code_file);
    (*code)[*len] = '\0';
    fclose(code_file);
}

int main() {
    /* Initialize BF environment */
    unsigned char* input = NULL;
    unsigned char* output = malloc(1024);
    char* code = NULL;
    int len = 0;
    get_code(&code, &len);
    if (code == NULL) {
        printf("[ERROR] Failed to read BF code\n");
    }

    bf_ctx_t* ctx = new_ctx(input, output);
    ctx_bind_code(ctx, code, len);

    /* Run BF code */
    printf("[INFO] Running BF code...\n");

    int result = run_bf(ctx);
    printf("[INFO] Output data:\n");
    const size_t output_len = ctx->output_ptr;
    for (size_t i = 0; i < output_len; i++) {
        printf("%c", ctx->output[i]);
    }
    printf("\n");

    printf("[INFO] BF code exits with code %d\n", result);

    /* Free resources */
    free(code);
    free_ctx(ctx);

    return 0;
}
