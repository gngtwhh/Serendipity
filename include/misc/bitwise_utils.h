/**
 * @file: bitwise_utils.h
 * @description: This header file contains utility functions or macros for bit operations.
 * @author: WAHAHA
 * @Date: 2024/4/7 10:00
 * @FilePath: Serendipity/include/misc/bitwise_utils.h
 * @category: misc
 */

#ifndef SERENDIPITY_BITWISE_UTILS_H
#define SERENDIPITY_BITWISE_UTILS_H

/**
 * Bit manipulation macros: setting, clearing, getting
 * a specific bit, and getting the number of bits of
 * a type.
 */
#define SET_BIT(x, i) (x |= (1 << i))
#define CLEAR_BIT(x, i) (x &= ~(1 << i))
#define GET_BIT(x, i) ((x >> i) & 1)
#define BITS_OF(type) (sizeof(type)<<3)

/**
 * The following macros should be used for unsigned numbers
 * to avoid arithmetic shifts
 */

/* shift left and right */
#define SHL_NBIT(data, bits) ((data)<<(bits))
#define SHR_NBIT(data, bits) ((data)>>(bits))

/* cycle shift left and right */
#define CYCLE_SHL_SIZE_NBIT(data, bits, type)                      \
    (((data) << (bits)) | ((data) >> (BITS_OF(type) - (bits))))
#define CYCLE_SHR_SIZE_NBIT(data, bits, type)                      \
    (((data) >> (bits)) | ((data) << (BITS_OF(type) - (bits))))

#endif //SERENDIPITY_BITWISE_UTILS_H
