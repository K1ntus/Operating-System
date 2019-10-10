/* putchar.c
 *	Simple program to test whether the PutChar Syscall works. 
 *  The user do not have anything to do, except analysis the output. 
 *  
 *	It is calling multiple PutChar, to test multiple case:
 *      \* character 'a' to 'a'+4
 *      \* ten times 'a'
 *      \* \n
 *      \* \0
 * 
 */

#include "syscall.h"

void print1(char c, int n) {
    int i;
    #if 1
    for (i = 0; i < n; i++) {
        PutChar(c + i);
    }
    PutChar('\n');
#endif
}


void print2(char c, int n) {
    int i;
    #if 1
    for (i = 0; i < n; i++) {
        PutChar(c);
    }
    PutChar('\n');
#endif
}

/*
Putchar(char c){

    return 'a';
}*/


int main() {
    print1('a',4);
    print2('a',10);  
    PutChar('\n');
    PutChar('\0');
}