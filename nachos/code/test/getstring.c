#include "syscall.h"

#define SIZE 11

int
main() {
    char s[SIZE] = "Hello W0rld\0";

    PutString(s);

    GetString(s, SIZE);

    PutChar('\n');

    return 0;
}
