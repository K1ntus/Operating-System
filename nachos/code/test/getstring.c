#include "syscall.h"

#define SIZE_1 12
#define SIZE_2 6
#define SIZE_3 11
#define SIZE_3 11
#define MAX_STRING_SIZE 1024

int main() {
    char s1[SIZE_1];
    char s2[SIZE_2];
    char s3[MAX_STRING_SIZE];

    GetString(s1, SIZE_1);
    PutChar('\n');

    GetString(s1, SIZE_1-SIZE_2);   //Can test with out of bound string
    PutChar('\n');

    GetString(s2, SIZE_2);
    PutChar('\n');
    
    GetString(s3, MAX_STRING_SIZE); //Can test with MAX_STRING_SIZE string
    PutChar('\n');


    //>MAX_STRING_SIZE case not handled yet

    Halt();
}
