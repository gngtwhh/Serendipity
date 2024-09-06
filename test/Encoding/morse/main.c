#include <encode/morse.h>
#include <string.h>

int main() {
    char input[1024];
    char res[1024];
    puts("input code: ");
    gets_s(input, sizeof(input));
    morse_decode(input, res, sizeof(res));
    printf("%s\n", res);

    puts("input string: ");
    gets_s(input, sizeof(input));
    morse_encode(input, res, sizeof(res));
    printf("%s\n", res);
    return 0;
}