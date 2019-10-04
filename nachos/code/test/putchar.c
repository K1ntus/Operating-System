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

Putchar(char c){

    return 'a';
}


int main() {
    print1('a',4);
    print2('a',10);  
}