/**
 * @file: load.h
 * @description: This is a header file that contains the declaration of bf
 * @author: WAHAHA
 * @Date: 2024/8/7 下午12:45
 * @FilePath: bf_runner/load.h
 * @category: misc-bf_runner
 */

#ifndef BF_RUNNER_BF_H
#define BF_RUNNER_BF_H

#include <stdlib.h>

#define KB (1024)
#define MB (1024 * KB)
#define GB (1024 * MB)

#define MAX_MEM_SIZE (1024 * KB)
#define BF_STATUS_RUNNING 0
#define BF_STATUS_ERROR 1
#define BF_STATUS_FINISHED 2

typedef unsigned char byte;

typedef struct bf_ctx_s {
    byte* array;
    char* code; // read all code from file
    size_t arr_size;
    size_t code_len;
    size_t ptr;
    size_t code_ptr;
    int status; // 0: running, 1: error, 2: finished
    size_t output_ptr;
    size_t input_ptr;
    byte* input;
    byte* output;
} bf_ctx_t;

// context operations
bf_ctx_t* new_ctx(unsigned char* input,unsigned char* output);
bf_ctx_t* copy_ctx(const bf_ctx_t* old_ctx);
void free_ctx(bf_ctx_t* ctx);
void ctx_bind_code(bf_ctx_t* ctx, char* code, const int len);

// run bf code
int run_bf(bf_ctx_t* ctx);
void interpret_command(bf_ctx_t* ctx, char command);

// vm commands
void vm_add_ptr(bf_ctx_t* ctx);
void vm_sub_ptr(bf_ctx_t* ctx);
void vm_add_val(bf_ctx_t* ctx);
void vm_sub_val(bf_ctx_t* ctx);
void vm_output(bf_ctx_t* ctx);
void vm_input(bf_ctx_t* ctx);
void vm_loop_start(bf_ctx_t* ctx);

#endif //BF_RUNNER_BF_H
