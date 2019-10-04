#include "syscall.h"

int main(void) {
    int int_1 = 0;
    int int_2 = 0;

    PutString("\n\0");
    GetInt(int_1);
    PutString("\n>> \0");
    PutInt(int_1);
    
    PutString("\n> \0");
    GetInt(int_2);
    PutString("\n>> \0");
    PutInt(int_2);

    // PutChar('\n');

    // Halt();
}
