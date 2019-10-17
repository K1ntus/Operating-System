/* putint.c
 *	Simple program to test whether the PutInt Syscall works. 
 *  Also supposed that the PutString, PutChar syscall is
 *  working.
 * 
 *  The user do not have anything to do, except analysis the output. 
 *  
 *	It is calling multiple PutChar, to test multiple case:
 *      \* Int from 0 to 3
 *      \* 'Lambda' int: 1234567890
 *      \* The 'a' character
 *      \* NULL (0x0) value
 *      \* The string "123456"
 *      \* Int equals to MAX_SIGNED_INTEGER
 *      \* Incredibly large integer
 *      \* \0
 * 
 */

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

    PutString("\nUn caractere:\n> \0");
    PutInt('a');
    PutString("\n\0");

    PutString("\nvaleur NULL:\n> \0");
    PutInt(0x0);
    PutString("\n\0");

    PutString("\nUne chaine de caracteres:\n> \0");
    PutInt("123456");
    PutString("\n\0");

    PutString("\nMAX_INT:\n> \0");
    PutInt(2147483647);
    PutString("\n\0");

    PutString("\nNombre beaucoup trop grand:\n> \0");
    PutInt(99999999999999999999999999999999999999); //Should return -1 because it's clearly too large for a signed integer
    PutString("\n\n\0");

    // Halt();
}
