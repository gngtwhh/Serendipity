#include <encode/morse.h>
#include <string.h>

int main() {
    char test_code[1024];
    char res[1024];
    puts("input more code: ");
    gets_s(test_code, sizeof(test_code));
    morse_decode(test_code, res, sizeof(res));
    printf("%s\n", res);
    return 0;
}