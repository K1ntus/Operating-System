#include "syscall.h"

#define SIZE_1 12
#define SIZE_2 6
#define SIZE_3 11
#define SIZE_3 11

int
main() {
    int *int_1 = 42;
    int *int_2 = 1234567890;

    PutInt(int_1);
    GetInt(int_1);

    PutInt(int_2);
    GetInt(int_2);

    PutChar('\n');

    Halt();
}
