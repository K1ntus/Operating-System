#ifdef CHANGED

//#include "syscall.h"
#include <stdarg.h>
//#include "vsprintf.c"



int main () {
   int i = 5;
   char str[50];
   char hello[50];

   strcpy(str, "Ceci est une chaine de caractères à printf !\n\0");
   strcpy(hello, "Hello World\n\0");

   printf("Entier 1(6) -> %d;\nEntier 2(5) -> %d;\nChaine de caracteres: %s\n", i+1, i, str);
   printf("Printf de 'Hello World'\n", hello);
   printf("Printf du caractere C -> %c\n", 'C');
   //PutString(buffer);
   
}


#endif //CHANGED