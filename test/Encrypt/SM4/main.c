#include <encrypt/sm4.h>
#include <encrypt/pkcspad.h>
#include <string.h>
#include <stdlib.h>

int main() {
    sm4_encipher *sm4 = new_sm4();
//    byte key[16] = {
//            0x12,0x34,0x56,0x78,0x90,0xab,0xcd,0xef,
//            0x12,0x34,0x56,0x78,0x90,0xab,0xcd,0xef
//    };
    uint32_t key[]={
            0x01234567,0x89abcdef,0x01234567,0x89abcdef
    };
    sm4_init(sm4, (byte*)key);

//    byte data[] = "hello world!";
//    int data_len = strlen((char *) data);

    uint32_t data[]={
            0x01234567,0x89abcdef,0x01234567,0x89abcdef
    };
    int data_len = sizeof(data);

    byte *out_data = (byte *) malloc(sizeof(byte) * (data_len + pkcs7_pad_len(data_len, 16) + 1));
    printf("origin data: %s\n", (char*)data);
    printf("SM4 encrypt data: ");
    sm4_encrypt(sm4, (byte*)data, data_len, out_data, &data_len);
    for (int i = 0; i < data_len; i++) {
        printf("%02x ", out_data[i]);
    }
    printf("\n%s", data);
//    memset(data, 0, sizeof(data));
//    printf("\nSM4 decrypt data: ");
//    sm4_crypt(sm4, out_data, data_len + pkcs7_pad_len(data_len, 16), data, SM4_DECRYPT);
//    printf("\n%s\n", data);
    free_sm4(sm4);

    return 0;
}