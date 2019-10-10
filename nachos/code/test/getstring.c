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

#include "syscall.h"

#define SIZE_1 12
#define SIZE_2 6
#define SIZE_3 11
#define SIZE_4 15//1024

int main() {
    char s1[SIZE_1];
    char s2[SIZE_2];
    char s3[SIZE_3];
    char s4[SIZE_4];
    char s5[1025];
    
    PutString("Chaine de taille 12:\n> \0");
    GetString(s1, SIZE_1); //Can test with MAX_STRING_SIZE string
    PutString(">> \0");
    PutString(s1);
    
    PutString("\nChaine de taille 6:\n> \0");
    GetString(s2, SIZE_2); //Can test with MAX_STRING_SIZE string
    PutString(">> \0");
    PutString(s2);
    PutString("\n");
    
    PutString("\nChaine de taille 11:\n> \0");
    GetString(s3, SIZE_3); //Can test with MAX_STRING_SIZE string
    PutString(">> \0");
    PutString(s3);
    PutString("\n");
    
    PutString("\nChaine de taille 15:\n> \0");
    GetString(s4, SIZE_4); //Can test with MAX_STRING_SIZE string
    PutString(">> \0");
    PutString(s4);
    PutString("\n");

/*
    PutString("\nChaine de taille 1025:\n> \0");    //MAX_STRING_SIZE set to 1024, so will return an error
    GetString(s5, 1025);
    PutString(">> \0");
    PutString(s5);
    PutString("\n");
*/

}
