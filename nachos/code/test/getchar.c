/* getchar.c
 *	Simple program to test whether the GetChar works. 
 *  Also supposed that the PutString and PutChar syscalls 
 *  are working.
 *	
 *	It is looping, trying to Getchar, then Put it in the simulated console
 *  To exit the looping, you had to send the character '$'.
 */


#ifdef CHANGED

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

#endif //CHANGED