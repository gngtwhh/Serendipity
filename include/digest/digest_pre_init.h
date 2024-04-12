/**
 * @file: encode_pre_init.h
 * @description: This is a header file that contains the declaration of pre-initialization of encode.
 * @author: WAHAHA
 * @Date: 2024-02-28 11:06:35
 * @LastEditTime: 2024-03-04 15:22:36
 * @FilePath: \Serendipity\include\encode\encode_pre_init.h
 * @category: digest-algorithm
 */

#ifndef ENCODE_PRE_INIT_H
#define ENCODE_PRE_INIT_H

#include <stdio.h>
#include <stdint.h>
#include <misc/bitwise_utils.h>

/* declare byte type */
typedef uint8_t byte;

/* declare extended boolean type */
#ifndef SERENDIPITY_BOOL
#define SERENDIPITY_BOOL

typedef int status;
#define true 1 // correct execution
#define false 0 // The data to be processed or initialized is incorrect
#define error (-1) // user's usage error
#define failed (-2) // system's failure

#endif

/* define assert macro */
#ifndef ASSERT
#define ASSERT(expr, code)                                      \
if(!(expr)) {                                                   \
    printf("[%s]:%s:%d is failed! error code: %d\r\n",          \
        __FILE__,__FUNCTION__,__LINE__,code);                   \
    return code;                                                \
}
#endif

#endif // ENCODE_PRE_INIT_H