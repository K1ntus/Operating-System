#include "syscall.h"

int main(void) {
    char c = '\0';

    while (c != 'q') {
        PutString("Press `$` to quit\n\n");
        
        c = GetChar();
        PutChar(c);
    }

    return 0;
}
