#include <encrypt/tea.h>
#include <string.h>
#include <stdio.h>

int main()
{
    /* uint32_t key[] = { 1,2,3,4 };
    tea_encipher *tea = new_tea(0x12345678, key, 31);
    char plain[100] = "Hello world!";

    printf("XTEA encrypt test:\n");
    printf("plain: %s\n",plain);

    int len = (strlen(plain) / sizeof(uint32_t)) + (strlen(plain) % sizeof(uint32_t) != 0);
    len += len % 2;
    tea->n = len;
    uint32_t enc[len];
    xtea_encrypt(tea, (uint32_t *)plain, enc);
    printf("ciper: ");
    for (int i = 0; i < len; i++) {
        printf("%x ", enc[i]);
    }

    printf("\n");
    memset(plain, 0, sizeof(plain));
    xtea_decrypt(tea, enc, (uint32_t *)plain);
    printf("decrypt from ciper: %s\n", plain); */
    uint32_t key[4] = {
        22,33,44,55
    };
    uint32_t del = -0x543210DD;
    tea_encipher *tea = new_tea(del, key, 32);
    tea->n = 10;
    char c[] = {
        0x20,0x69,0xb3,0xe4,0xd0,0x24,0x69,0x93,0x44,0xd1,0x16,0xa8,0xf5,0xd5,0x82,0xaa,
        0xda,0xf0,0x79,0x36,0x06,0xfd,0x32,0x7f,0xd3,0xc0,0x60,0x34,0x39,0x49,0x21,0xb7,
        0xa2,0x69,0x72,0xe5,0xfa,0x51,0x6a,0x83
    };
    uint32_t * ciper = (uint32_t *)c;
    uint32_t plain[10];
    tea_decrypt(tea, ciper, plain);
    for (int i = 0;i < 10;++i)
        for (int j = 0;j < 4;++j)
            putchar(((char *)(&plain[i]))[j]);
    return 0;
}