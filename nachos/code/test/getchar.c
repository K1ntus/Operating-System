#include "syscall.h"

int main(void) {
    char c = '\0';

    PutString("Press `$` to quit\n\n");
    while (c != '$') {        
        c = GetChar();
        PutChar(c);
    }

    return 0;
}
