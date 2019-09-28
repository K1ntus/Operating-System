#include "syscall.h"

#define SIZE_1 12
#define SIZE_2 6
#define SIZE_3 11
#define SIZE_3 11

int
main() {
    int int_1 = 0;
    int int_2 = 0;

    GetInt(&int_2);

    
    GetInt(&int_1);

    PutChar('\n');

    Halt();
}
