#include "syscall.h"

int
main() {
    char c = '\0';

    while (c != 'q') {
        PutString("Quit by pressing '$'\n\n");
        
        c = GetChar();
        PutChar(c);
    }

    return 0;
}
