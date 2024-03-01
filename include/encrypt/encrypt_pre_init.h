/**
 * @file encrypt_pre_init.h
 * @brief This is a header file that contains the declaration of pre-initialization of encrypt algorithm.
 * @author WAHAHA
 * @category encrypt-algorithm
 * @date 2024
 */

#ifndef _ENCRYPT_PRE_INIT_
#define _ENCRYPT_PRE_INIT_

 /* define bit operation macro */
#define set_bit(x, i) (x |= (1 << i))
#define clear_bit(x, i) (x &= ~(1 << i))
#define get_bit(x, i) ((x >> i) & 1)
#define bits_of(type) (sizeof(type)<<3)

/**
 * The following macros should be used for unsigned numbers
 * to avoid arithmetic shifts
 */

/* shift left and right */
#define SHL_NBIT(data,bits) (data<<bits)
#define SLR_NBIT(data,bits) (data>>bits)

/* cycle shift left and right */
#define CYCLE_SHL_SIZE_NBIT(data,bits,type)        \
    ((data << bits) | (data >> (bits_of(type) - bits)))
#define CYCLE_SHR_SIZE_NBIT(data,bits,type)        \
    ((data >> bits) | (data << (bits_of(type) - bits)))

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


#endif