#include "syscall.h"

int main(void) {
    int int_value = 0;

    PutString("Send `666` to exit the program.\n\0");
    while (int_value != 666) {      
        PutString("\n> \0");
        GetInt(&int_value);
        PutString("\n>> \0");
        PutInt(int_value);
    }


    PutChar('\n');
    // Halt();
}
