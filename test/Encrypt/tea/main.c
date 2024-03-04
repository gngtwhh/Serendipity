#include <encrypt/tea.h>
#include <string.h>
#include <stdio.h>

int main()
{
    uint32_t key[] = { 1,2,3,4 };
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
    printf("decrypt from ciper: %s\n", plain);



    return 0;
}