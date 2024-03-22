#include <encrypt/sm4.h>
#include <encrypt/pkcspad.h>
#include <string.h>
#include <stdlib.h>

int main() {

    sm4_encipher *sm4 = new_sm4();
    byte key[16] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
                    0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10};
    sm4_init(sm4, key);

//    byte data[] = "hello world!";
    byte data[] = "1111111111111111";
    int data_len = strlen((char *) data);
    byte *out_data = (byte *) malloc(sizeof(byte) * (data_len + pkcs7_pad_len(data_len, 16)));
    printf("origin data: %s\n", data);
    printf("SM4 encrypt data: ");
    sm4_crypt(sm4, data, data_len, out_data, SM4_ENCRYPT);
    for (int i = 0; i < data_len + pkcs7_pad_len(data_len, 16); i++) {
        printf("%02x ", out_data[i]);
    }
    memset(data, 0, sizeof(data));
    printf("\nSM4 decrypt data: ");
    sm4_crypt(sm4, out_data, data_len + pkcs7_pad_len(data_len, 16), data, SM4_DECRYPT);
    printf("\n%s\n", data);

    return 0;
}