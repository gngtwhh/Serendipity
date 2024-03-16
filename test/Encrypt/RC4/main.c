#include <encrypt/rc4.h>
#include <string.h>

int main() {
    rc4_encipher *rc4 = new_rc4();
    byte key[] = "Thi5_1S_key?";
    byte enc[] = {
            0xf, 0x3c, 0x41, 0x75, 0x72, 0x42, 0x53, 0x6, 0x5d, 0x4c, 0x32, 0x1d, 0x2a, 0x5c, 0x49,
            0x26, 0x22, 0x4b, 0x69, 0x22
    };
    byte dec[21]={0};
    rc4_init(rc4, key, strlen((char *) key), 128);
    rc4_crypt(rc4, enc, 20, dec);
    puts((char *) dec);
    memset(enc, 0, 21);
    rc4_crypt(rc4, dec, 20, enc);
    for(int i=0;i<20;i++)
        printf("%x ",enc[i]);

    return 0;
}