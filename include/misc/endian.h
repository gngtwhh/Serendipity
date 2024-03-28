/**
 * @file: endian.h
 * @description: This header file contains macros for endian conversion.
 * @author: WAHAHA
 * @Date: 2024/3/28 14:38
 * @LastEditTime: 2024/3/28 14:38
 * @FilePath: Serendipity/include/misc/endian.h
 * @category: misc
 */

#ifndef SERENDIPITY_ENDIAN_H
#define SERENDIPITY_ENDIAN_H

/*
 * Convert 4 bytes of data to uint32_t in big-endian or little-endian
 */
/* big-endian */
#define BE_BYTES_TO_UINT32(b)                        \
    ( (uint32_t)((b)[0]) << 24                       \
    | (uint32_t)((b)[1]) << 16                       \
    | (uint32_t)((b)[2]) <<  8                       \
    | (uint32_t)((b)[3]) )
#define BE_UINT32_TO_BYTES(b, u)                     \
    do {                                             \
        (b)[0] = (unsigned char)((u) >> 24);         \
        (b)[1] = (unsigned char)((u) >> 16);         \
        (b)[2] = (unsigned char)((u) >>  8);         \
        (b)[3] = (unsigned char)( u       );         \
    } while(0)

/* little-endian */
#define LE_BYTES_TO_UINT32(b)                        \
    ( (uint32_t)((b)[3]) << 24                       \
    | (uint32_t)((b)[2]) << 16                       \
    | (uint32_t)((b)[1]) <<  8                       \
    | (uint32_t)((b)[0]) )
#define LE_UINT32_TO_BYTES(b, u)                     \
    do {                                             \
        (b)[3] = (unsigned char)((u) >> 24);         \
        (b)[2] = (unsigned char)((u) >> 16);         \
        (b)[1] = (unsigned char)((u) >>  8);         \
        (b)[0] = (unsigned char)( u       );         \
    } while(0)


#endif //SERENDIPITY_ENDIAN_H
