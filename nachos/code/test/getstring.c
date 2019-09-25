#include "syscall.h"

#define SIZE_1 12
#define SIZE_2 6
#define SIZE_3 11
#define SIZE_3 11

int
main() {
    char s1[SIZE_1] = "Hello W0rld\0";
    char s2[SIZE_2] = "W0rld\0";

    PutString(s1);
    GetString(s1, SIZE_1);

    PutString(s2);
    GetString(s2, SIZE_2);

    PutChar('\n');

    Halt();
}
