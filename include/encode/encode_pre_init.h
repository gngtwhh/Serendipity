/**
 * @file encode_pre_init.h
 * @brief This is a header file that contains the declaration of pre-initialization of encode algorithm.
 * @author WAHAHA
 * @category encode-algorithm
 * @date 2024
 */

#ifndef _ENCODE_PRE_INIT_H_
#define _ENCODE_PRE_INIT_H_

#include <stdio.h>

 /* declare byte type */
typedef unsigned char byte;

/* define bit operation macro */
#define set_bit(x, i) (x |= (1 << i))
#define clear_bit(x, i) (x &= ~(1 << i))
#define get_bit(x, i) ((x >> i) & 1)

/* declare extanded boolean type */
#ifndef _BOOL_
#define _BOOL_

typedef int status;
#define true 1
#define false 0
#define error -1 // user's usage error
#define failed -2 // system's failure

#endif

/* define assert macro */
#ifndef ASSERT
#define ASSERT(expr,code)                                       \
if(!(expr)) {                                                   \
    printf("[%s]:%s:%d is failed! error code: %d\r\n", \
        __FILE__,__FUNCTION__,__LINE__,code);                   \
    return code;                                                \
}
#endif

#ifndef container_of
#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - (unsigned long)(&((type *)0)->member)))
#endif

#endif