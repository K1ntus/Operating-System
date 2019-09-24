#include "syscall.h"


void print(int n) {
    int i;
    #if 1
    for (i = 0; i < n; i++) {
        PutInt(i);
    }
#endif
}



int main() {
    print(4);
    Halt();
}