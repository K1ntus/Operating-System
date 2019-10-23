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
    int n = 150;
    int i;
    for (i = 0; i < n; i++) {
        PutChar(c);
    // while(1);
    }
    ThreadExit();
}

void print_principal(char c) {
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
    print_principal('0');
    ThreadCreate(*fun_ptr,'1');
    ThreadCreate(*fun_ptr,'2');
    ThreadCreate(*fun_ptr,'3');
    // ThreadCreate(*fun_ptr,'4');
    // ThreadCreate(*fun_ptr,'5');
    // ThreadCreate(*fun_ptr,'6');
    // while(1);
    
    ThreadExit();   //ThreadPrincipal
    return 0;
}
#endif