/* getstring.c
 *	Simple program to test whether the GetString Syscall works. 
 *  Also supposed that the PutString syscall is working.
 * 
 *  
 *	It is calling multiple PutString,  with different size 
 *  for the buffer/first parameter to test multiple case:
 *      \* String of size 12
 *      \* String of size 6
 *      \* String of size 11
 *      \* String of size 15
 *      \* String with a size greater than 
 *          MAX_STRING_SIZE fixed into system.h
 * 
 */


#ifdef CHANGED


#include "syscall.h"

#define SIZE_1 12
#define SIZE_2 6
#define SIZE_3 11
#define SIZE_4 15//1024

int main() {
    int size = 8;
    char buffer[8];
    // while(buffer[0] != "q"){
    while(1){
        PutString("> \0");
        GetString(buffer, size);

    }
}


#endif //CHANGED