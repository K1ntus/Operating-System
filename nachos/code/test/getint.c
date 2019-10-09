#include "syscall.h"

int main(void) {
    int int_value = 0;

    PutString("Send `42` to exit the program.\n\0");
    while (int_value != 42) {      
        PutString("\n> \0");
        GetInt(&int_value);
        PutString(">> \0");
        PutInt(int_value);
        PutString("\n\0");
    }


    PutChar('\n');
    // Halt();
}
