#include <encrypt/sm4.h>
#include <encrypt/pkcspad.h>
#include <string.h>
#include <stdlib.h>

int main() {
    sm4_encipher* sm4 = new_sm4();
    byte key[16] = {
        0x12, 0x34, 0x56, 0x78, 0x90, 0xab, 0xcd, 0xef,
        0x12, 0x34, 0x56, 0x78, 0x90, 0xab, 0xcd, 0xef
    };
    sm4_init(sm4, key);

    byte data[] = "hello world!";
    byte* pad_data = pkcs7_pad(data, strlen((char*)data), 16);
    int data_len = strlen(data);
    int pad_data_len = strlen(data) + pkcs7_pad_len(data_len, 16);

    byte* out_data = (byte*)malloc(sizeof(byte) * (pad_data_len));

    printf("origin data:      ");
    for (int i = 0; i < data_len; i++)
        printf("%02x ", data[i]);
    printf("(%s)\n",(char*)data);

    sm4_crypt(sm4, pad_data, pad_data_len, out_data, SM4_ENCRYPT);
    printf("SM4 encrypt data: ");
    for (int i = 0; i < pad_data_len; i++) {
        printf("%02x ", out_data[i]);
    }
    sm4_crypt(sm4, out_data, pad_data_len, pad_data, SM4_DECRYPT);

    memset(data, 0, sizeof(pad_data));
    putchar('\n');
    printf("SM4 decrypt data: ");
    for (int i = 0; i < data_len; i++) {
        printf("%02x ", pad_data[i]);
    }
    putchar('(');
    for (int i = 0; i < data_len; i++) {
        printf("%c", pad_data[i]);
    }
    putchar(')');
    free_sm4(sm4);
    return 0;
}
