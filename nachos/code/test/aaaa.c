#ifdef CHANGED

//#include "syscall.h"
#include <stdarg.h>
//#include "vsprintf.c"



int main () {
   int i = 5;
   char str[50];
   strcpy(str, "Les ordinateurs, c'est vraiment génial\n\0");

   printf("%d %d %s\n", i+1, i);
   printf("%s", str);   //Should work (but currently not)
   printf(str);
   //PutString(buffer);
   
   return(0);
}


#endif //CHANGED