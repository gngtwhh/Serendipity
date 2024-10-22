/**
 * @file: load.c
 * @description: This is a source file that contains the implementation of xxx
 * @author: WAHAHA
 * @Date: 2024/8/7 下午12:45
 * @FilePath: bf_runner/load.c
 * @category: misc-bf_runner
 */

#include <string.h>
#include <conio.h>
#include <stdio.h>
#include "misc/bf.h"

bf_ctx_t* new_ctx(unsigned char* input,unsigned char* output) {
    // fill with 0
    bf_ctx_t* ctx = (bf_ctx_t*)calloc(1, sizeof(bf_ctx_t));
    ctx->array = (byte*)calloc(1, sizeof(char) * MAX_MEM_SIZE);
    ctx->arr_size = MAX_MEM_SIZE;
    ctx->input = input;
    ctx->output = output;

    return ctx;
}

bf_ctx_t* copy_ctx(const bf_ctx_t* old_ctx) {
    bf_ctx_t* new_one = (bf_ctx_t*)malloc(sizeof(bf_ctx_t));
    *new_one = *old_ctx;
    return new_one;
}

void free_ctx(bf_ctx_t* ctx) {
    free(ctx->array);
    free(ctx);
    // NOTE: input and output fields should be freed by caller
}

void ctx_bind_code(bf_ctx_t* ctx, char* code, const int len) {
    ctx->code = code;
    ctx->code_len = len;
    // null terminate code array
    ctx->code[ctx->code_len] = '\0';
}

int run_bf(bf_ctx_t* ctx) {
    const char* code = ctx->code;
    while (ctx->code_ptr < ctx->code_len) {
        const char command = code[ctx->code_ptr];
        interpret_command(ctx, command);
        if (ctx->status == BF_STATUS_ERROR) {
            return -1;
        }
        ctx->code_ptr++;
    }
    return ctx->array[ctx->ptr];
}

void interpret_command(bf_ctx_t* ctx, const char command) {
    switch (command) {
    case '>':
        vm_add_ptr(ctx);
        break;
    case '<':
        vm_sub_ptr(ctx);
        break;
    case '+':
        vm_add_val(ctx);
        break;
    case '-':
        vm_sub_val(ctx);
        break;
    case '.':
        vm_output(ctx);
        break;
    case ',':
        vm_input(ctx);
        break;
    case '[':
        vm_loop_start(ctx);
        break;
    case ']':
        ctx->status = BF_STATUS_ERROR;
        break;
    case '\n': // ignore newlines
        break;
    case ' ': // ignore spaces
        break;
    default:
        ctx->status = BF_STATUS_ERROR;
    }
}

void vm_add_ptr(bf_ctx_t* ctx) {
    if (ctx->ptr < ctx->arr_size - 1) {
        ctx->ptr++;
    } else {
        ctx->status = BF_STATUS_ERROR;
    }
}

void vm_sub_ptr(bf_ctx_t* ctx) {
    if (ctx->ptr > 0) {
        ctx->ptr--;
    } else {
        ctx->status = BF_STATUS_ERROR;
    }
}

void vm_add_val(bf_ctx_t* ctx) {
    if (ctx->array[ctx->ptr] < 255) {
        ctx->array[ctx->ptr]++;
    } else {
        //        printf("[ERROR] Value overflow, cannot increment value\n");
        //        ctx->status = BF_STATUS_ERROR;
        ctx->array[ctx->ptr] = 0; // wrap around
    }
}

void vm_sub_val(bf_ctx_t* ctx) {
    if (ctx->array[ctx->ptr] > 0) {
        ctx->array[ctx->ptr]--;
    } else {
        //        printf("[ERROR] Value underflow, cannot decrement value\n");
        //        ctx->status = BF_STATUS_ERROR;
        ctx->array[ctx->ptr] = 255; // wrap around
    }
}

void vm_output(bf_ctx_t* ctx) {
    if (ctx->output != NULL) {
        ctx->output[ctx->output_ptr] = ctx->array[ctx->ptr];
        ctx->output_ptr++;
    } else {
        ctx->status = BF_STATUS_ERROR;
        // putchar(ctx->array[ctx->ptr]);
    }
}

void vm_input(bf_ctx_t* ctx) {
    if (ctx->input != NULL) {
        ctx->array[ctx->ptr] = ctx->input[ctx->input_ptr];
        ctx->input_ptr++;
    } else {
        ctx->status = BF_STATUS_ERROR;
        // ch = getch(); // get character from stdin without buffering
    }
}

void vm_loop_start(bf_ctx_t* ctx) {
    int cnt;
    /* find the matching ']' */
    size_t right_side = ctx->code_ptr;
    for (cnt = 1, right_side++; cnt != 0;) {
        if (right_side >= ctx->code_len) {
            ctx->status = BF_STATUS_ERROR;
            return;
        }
        if (ctx->code[right_side] == '[') {
            cnt++;
        } else if (ctx->code[right_side] == ']') {
            cnt--;
        }
        right_side++;
    }
    right_side--; // Locate the matching ']'

    /* check the condition */
    if (ctx->array[ctx->ptr] == 0) {
        // skip loop
        ctx->code_ptr = right_side;
    } else {
        // execute loop
        do {
            /* copy the current context */
            bf_ctx_t* cur_ctx = copy_ctx(ctx);
            cur_ctx->code_ptr = ctx->code_ptr + 1;
            cur_ctx->code = cur_ctx->code + cur_ctx->code_ptr;
            cur_ctx->code_len = right_side - cur_ctx->code_ptr;
            cur_ctx->code_ptr = 0; // reset the code pointer to 0 --- offset relative to the start of the loop
            /* run the loop */
            run_bf(cur_ctx); // run the loop
            /* copy the result back to the original context */
            ctx->ptr = cur_ctx->ptr;
            if (cur_ctx->status == BF_STATUS_ERROR) {
                ctx->status = BF_STATUS_ERROR;
            }
            /* free the copied context */
            free(cur_ctx); // just free the copied context obj, but don't free the context data(ctx still owns the data)
        } while (ctx->array[ctx->ptr] != 0);
        /* move the code pointer to the end of the loop */
        ctx->code_ptr = right_side;
    }
}
