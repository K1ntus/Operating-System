#ifdef CHANGED

#include "syscall.h"

int main(void)
{
    PutChar('$');
    PutChar('\n');
    PutString("String a tester");
    PutChar('\n');
    PutChar('$');
    PutChar('\n');
}
#endif