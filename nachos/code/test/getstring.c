#include "syscall.h"

#define SIZE_1 12
#define SIZE_2 6
#define SIZE_3 11
#define SIZE_3 11
#define MAX_STRING_SIZE 1024

int
main() {
    char s1[SIZE_1];
    char s2[SIZE_2];    //chaine trop longue en entrée
    char s3[MAX_STRING_SIZE];

    GetString(s1, SIZE_1);

    GetString(s2, SIZE_2);
    
    GetString(s3, MAX_STRING_SIZE);

    PutChar('\n');

    Halt();
}
