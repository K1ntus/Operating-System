#ifdef CHANGED
/* thread.c
 *	Simple program to test whether the GetChar works. 
 *  Also supposed that the PutString and PutChar syscalls 
 *  are working.
 *	
 *	It is looping, trying to Getchar, then Put it in the simulated console
 *  To exit the looping, you had to send the character '$'.
 */
#include "syscall.h"

void print1(char c) {
    int n = 12;
    int i;
    for (i = 0; i < n; i++) {
        PutChar(c);
    // while(1);
    }
}


int main(void) {
    // fun_ptr is a pointer to function fun()  
    void (*fun_ptr)(int) = &print1; 
    print1('e');
    ThreadCreate(*fun_ptr,'u');
    while(1);
    
    return 0;
}
#endif