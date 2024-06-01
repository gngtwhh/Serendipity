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
// u: uint32_t, b: unsigned char *
#define BE_BYTES_TO_UINT32(u, b)                     \
    ((u) = (uint32_t)((b)[0]) << 24                  \
         | (uint32_t)((b)[1]) << 16                  \
         | (uint32_t)((b)[2]) <<  8                  \
         | (uint32_t)((b)[3])                        \
    )

// b: unsigned char *, u: uint32_t
#define BE_UINT32_TO_BYTES(b, u)                     \
    do {                                             \
        (b)[0] = (unsigned char)((u) >> 24);         \
        (b)[1] = (unsigned char)((u) >> 16);         \
        (b)[2] = (unsigned char)((u) >>  8);         \
        (b)[3] = (unsigned char)( u       );         \
    } while(0)

// b: unsigned char *, u: uint64_t
#define BE_BYTES_TO_UINT64(b, u)                     \
    ((u) = (uint64_t)((b)[0]) << 56                  \
         | (uint64_t)((b)[1]) << 48                  \
         | (uint64_t)((b)[2]) << 40                  \
         | (uint64_t)((b)[3]) << 32                  \
         | (uint64_t)((b)[4]) << 24                  \
         | (uint64_t)((b)[5]) << 16                  \
         | (uint64_t)((b)[6]) <<  8                  \
         | (uint64_t)((b)[7])                        \
    )

// u: uint64_t, b: unsigned char *
#define BE_UINT64_TO_BYTES(b, u)                     \
    do {                                             \
        (b)[0] = (unsigned char)((u) >> 56);         \
        (b)[1] = (unsigned char)((u) >> 48);         \
        (b)[2] = (unsigned char)((u) >> 40);         \
        (b)[3] = (unsigned char)((u) >> 32);         \
        (b)[4] = (unsigned char)((u) >> 24);         \
        (b)[5] = (unsigned char)((u) >> 16);         \
        (b)[6] = (unsigned char)((u) >>  8);         \
        (b)[7] = (unsigned char)( u       );         \
    } while(0)

/* little-endian */
// u: uint32_t, b: unsigned char *
#define LE_BYTES_TO_UINT32(u, b)                     \
    ((u) = (uint32_t)((b)[3]) << 24                  \
         | (uint32_t)((b)[2]) << 16                  \
         | (uint32_t)((b)[1]) <<  8                  \
         | (uint32_t)((b)[0])                        \
    )

// b: unsigned char *, u: uint32_t
#define LE_UINT32_TO_BYTES(b, u)                     \
    do {                                             \
        (b)[3] = (unsigned char)((u) >> 24);         \
        (b)[2] = (unsigned char)((u) >> 16);         \
        (b)[1] = (unsigned char)((u) >>  8);         \
        (b)[0] = (unsigned char)( u       );         \
    } while(0)

// b: unsigned char *, u: uint64_t
#define LE_BYTES_TO_UINT64(b, u)                     \
    ((u) = (uint64_t)((b)[7]) << 56                  \
         | (uint64_t)((b)[6]) << 48                  \
         | (uint64_t)((b)[5]) << 40                  \
         | (uint64_t)((b)[4]) << 32                  \
         | (uint64_t)((b)[3]) << 24                  \
         | (uint64_t)((b)[2]) << 16                  \
         | (uint64_t)((b)[1]) <<  8                  \
         | (uint64_t)((b)[0])                        \
    )

// u: uint64_t, b: unsigned char *
#define LE_UINT64_TO_BYTES(b, u)                     \
    do {                                             \
        (b)[7] = (unsigned char)((u) >> 56);         \
        (b)[6] = (unsigned char)((u) >> 48);         \
        (b)[5] = (unsigned char)((u) >> 40);         \
        (b)[4] = (unsigned char)((u) >> 32);         \
        (b)[3] = (unsigned char)((u) >> 24);         \
        (b)[2] = (unsigned char)((u) >> 16);         \
        (b)[1] = (unsigned char)((u) >>  8);         \
        (b)[0] = (unsigned char)( u       );         \
    } while(0)

#endif //SERENDIPITY_ENDIAN_H
