#include <encrypt/rc4.h>
#include <string.h>

int main() {
    rc4_encipher *rc4 = new_rc4();
    byte key[5] = {0x12, 0x34};
    rc4_set_key(rc4, key, 2);
    byte *plain = "hello world";
    int len = strlen((char *) plain);
    byte cipher[len + 1];
    rc4_crypt(rc4, plain, len, cipher);
    for (int i = 0; i < len; i++)
        printf("%02x ", cipher[i]);
    byte dec[len + 1];
    rc4_crypt(rc4, cipher, len, dec);
    printf("\n%s\n", dec);
    free_rc4(rc4);

    return 0;
}