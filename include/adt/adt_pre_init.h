/**
 * @file adt_pre_init.h
 * @brief This is a header file that contains the declaration of pre-initialization of ADT.
 * @author WAHAHA
 * @category data-structure
 * @date 2024
 */

#ifndef ADT_PRE_INIT_H
#define ADT_PRE_INIT_H

#include <stdio.h>

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
#define ASSERT(expr,code)                                       \
if(!(expr)) {                                                   \
    printf("[%s]:%s:%d is failed! error code: %d\r\n", \
        __FILE__,__FUNCTION__,__LINE__,code);                   \
    return code;                                                \
}
#endif

#endif // ADT_PRE_INIT_H