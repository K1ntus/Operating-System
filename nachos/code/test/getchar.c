#include "syscall.h"

int
main() {
    char c;

    c = '\51';

    PutChar(c);
    PutChar('\n');
    PutString("Pour sortir de la boucle taper q\n");

    while (c != 'q') {
        c = GetChar();
        PutChar(c);
    }

    return 0;
}
