#include <encrypt/sm4.h>
#include <encrypt/pkcspad.h>
#include <string.h>
#include <stdlib.h>

int main() {
    sm4_encipher *sm4 = new_sm4();
    byte key[16] = {
            0x12, 0x34, 0x56, 0x78, 0x90, 0xab, 0xcd, 0xef,
            0x12, 0x34, 0x56, 0x78, 0x90, 0xab, 0xcd, 0xef
    };
//    uint32_t key[] = {
//            0x12345678, 0x90abcdef, 0x12345678, 0x90abcdef
//    };
    printf("key: ");
    for(int i = 0; i < 16; i++)
        printf("%02x ", key[i]);
    putchar('\n');
    sm4_init(sm4, (byte *) key);

//    byte data[] = "hello world!";
//    int data_len = strlen((char *) data);

    byte data[17] = {
            0x12, 0x34, 0x56, 0x78, 0x90, 0xab, 0xcd, 0xef,
            0x12, 0x34, 0x56, 0x78, 0x90, 0xab, 0xcd, 0xef, 0
    };
    int data_len = sizeof(data) - 1;

//    uint32_t data[] = {
//            0x12345678,0x90abcdef, 0x12345678, 0x90abcdef
//    };
//    int data_len = sizeof(data);

    byte *out_data = (byte *) malloc(sizeof(byte) * (data_len + pkcs7_pad_len(data_len, 16) + 1));

    printf("origin data:");
    for (int i = 0; i < data_len; i++) {
        printf("%02x ", data[i]);
    }
    putchar('\n');

    printf("SM4 encrypt data: ");
    sm4_encrypt(sm4, (byte *) data, data_len, out_data, &data_len);

    for (int i = 0; i < data_len; i++) {
        printf("%02x ", out_data[i]);
    }

    free_sm4(sm4);
    return 0;
}