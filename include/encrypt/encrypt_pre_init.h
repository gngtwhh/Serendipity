/**
 * @file: File name
 * @description: Briefly describe the file
 * @author: WAHAHA
 * @Date: 2024-02-29 17:32:55
 * @LastEditTime: 2024-03-05 13:45:09
 * @FilePath: \Serendipity\include\encrypt\encrypt_pre_init.h
 * @category: File category
 */

#ifndef ENCRYPT_PRE_INIT
#define ENCRYPT_PRE_INIT

#include <stdint.h>
#include <misc/bitwise_utils.h>

/* declare byte type */
typedef uint8_t byte;

/* declare extended boolean type */
#ifndef SERENDIPITY_BOOL
#define SERENDIPITY_BOOL

typedef int status;
#define true 1
#define false 0
#define error (-1) // user's usage error
#define failed (-2) // system's failure

#endif

/* define assert macro */
#ifndef ASSERT

#include <stdio.h>

#define ASSERT(expr, code)                                      \
if(!(expr)) {                                                   \
    printf("[%s]:%s:%d is failed! error code: %d\r\n",          \
        __FILE__,__FUNCTION__,__LINE__,code);                   \
    return code;                                                \
}
#endif


#endif // ENCRYPT_PRE_INIT