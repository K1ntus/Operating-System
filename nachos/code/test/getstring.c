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
    
    PutString("Chaine de taille 12:\n> \0");
    GetString(s1, SIZE_1); //Can test with MAX_STRING_SIZE string
    
    PutString("Chaine de taille 6:\n> \0");
    GetString(s2, SIZE_2); //Can test with MAX_STRING_SIZE string
    
    PutString("Chaine de taille 11:\n> \0");
    GetString(s3, SIZE_3); //Can test with MAX_STRING_SIZE string
    
    PutString("Chaine de taille 15:\n> \0");
    GetString(s4, SIZE_4); //Can test with MAX_STRING_SIZE string

}
