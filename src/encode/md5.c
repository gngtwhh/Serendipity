/**
 * @file: md5.c
 * @description: This is a source file that contains the implementation of MD5 algorithm.
 * @author: WAHAHA
 * @Date: 2024/4/7 10:30
 * @FilePath: Serendipity/src/encode/md5.c
 * @category: encode-algorithm
 */

#include <encode/md5.h>

/**
 * @Funticon name: md5_padding
 * @description: This function is used to pad the data to a multiple of 512 bits.
 * @Author: WAHAHA
 * @Date: 2024-4-7 10:32:27
 * @Note: Every 8-bits is interpreted as a byte with the high-order bit first.
 * @param {const byte *} data: The data to be processed.
 * @param {size_t} data_bit_size: The size of the data in bits.
 * @param {size_t *} block_size: The block count after padding.
 * @return {uint32_t *}: The data after padding.
 */
uint32_t *md5_padding(const byte *data, size_t data_bit_size, size_t *block_count);

/**
 * @Funticon name: md5
 * @description: This function is used to calculate the MD5 hash value of the data.
 * @Author: WAHAHA
 * @Date: 2024-4-7 10:40:14
 * @Note: md5() will pad the data to a multiple of 512 bits.
 * @param {const byte *} data: The data to be processed.
 * @param {size_t} data_bit_size: The size of the data in bits.
 * @return {status}: The status of the function execution.
 */
status md5(const byte *data, size_t data_bit_size, byte *digest);