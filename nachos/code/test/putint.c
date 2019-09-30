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

    PutInt(1234567890);
    PutInt(2147483647);
    PutInt(99999999999999999999999999999999999999); //Should return -1 because it's clearly too large for a signed integer
    Halt();
}