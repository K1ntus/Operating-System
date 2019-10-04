#include "syscall.h"


void print(int n) {
    int i;
    #if 1
    for (i = 0; i < n; i++) {
        PutInt(i);
        //PutChar(",");
        //PutChar(" ");
    }
#endif
}



int main() {
    PutString("\nChiffres de 0 à 3 (inclus):\n> \0");
    print(4);
    PutString("\n\0");

    PutString("\nNombre 'classique':\n> \0");
    PutInt(1234567890);
    PutString("\n\0");

    PutString("\nMAX_INT:\n> \0");
    PutInt(2147483647);
    PutString("\n\0");

    PutString("\nNombre beaucoup trop grand:\n> \0");
    PutInt(99999999999999999999999999999999999999); //Should return -1 because it's clearly too large for a signed integer
    PutString("\n\n\0");

    // Halt();
}