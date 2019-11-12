#ifdef CHANGED
/* thread.c
 *	Simple program to test whether the GetChar works. 
 *  Also supposed that the PutString and PutChar syscalls 
 *  are working.
 *	
 *	It is looping, trying to Getchar, then Put it in the simulated console
 *  To exit the looping, you had to send the character '$'.
 */
#include "syscall.h"


// sem_t s_consommateur = (sem_t) {.id = 0, .begin_value = 0};
// sem_t s_producteur = (sem_t) {.id = 1, .begin_value = 100};

int s_consommateur = 0;
int s_producteur = 1;

void printChar(char c)
{
    int n = 150;
    int i;
    for (i = 0; i < n; i++)
    {
        PutChar(c);
    }
}
void printString(char c)
{
    int n = 2;
    int i;
    for (i = 0; i < n; i++)
    {
        PutString("Je Suis Une Chaine de Caracteres");
    }
}

// char* getChar(){
//     char res[10];
//     int i;
//     PutString("Insert 10 char, one by one.\n");
//     for(i = 0; i < 10; i++)
//         res[i] = GetChar();

//     return res;

// }

void print_principal(char c)
{
    int n = 12;
    int i;
    for (i = 0; i < n; i++)
    {
        PutChar(c);
    }
}

void consommateur(){

        P(s_consommateur);  //Consommateur
        PutString("consommateur\n");
        V(s_producteur);    //Producteur



}

void producteur(){

        P(s_producteur);   //Producteur
        PutString("producteur\n");
        V(s_consommateur);   //Consommateur

}

void unlock_producteur(){
    int i;
    for(i = 0; i < 15; i++)
        V(s_producteur);
}
int main(void)
{

    // void (*fun_ptr_consommateur) (int) = &consommateur;
    // void (*fun_ptr_producteur) (int) = &producteur;
    // void (*fun_ptr_producteur_unlock) (int) = &unlock_producteur;
    // SemaphoreInit(s_consommateur, 0);
    // SemaphoreInit(s_producteur, 10);
    // ThreadCreate(*fun_ptr_producteur, 0x0);
    // ThreadCreate(*fun_ptr_consommateur, 0x0);
    // ThreadCreate(*fun_ptr_producteur_unlock, 0x0);
    // while(1){
    //     V(s_producteur);
    //     producteur();
    //     consommateur();
    // }
    

    // void (*fun_ptr)(int) = &fun;
    void (*fun_ptr)(int) = &printChar;
    void (*fun_ptr_string)(int) = &printString;
    print_principal('$');
    // int j;

    
    ThreadCreate(*fun_ptr, '2');
    ThreadCreate(*fun_ptr, '3');
    ThreadCreate(*fun_ptr, '4');
    ThreadCreate(*fun_ptr, '5');
    ThreadCreate(*fun_ptr, '6');
    ThreadCreate(*fun_ptr, '7');

    while(ThreadCreate(*fun_ptr_string, 0x0) == -1){ }
    
    // ThreadExit(); //ThreadPrincipal*/
    // return 0; 
}
#endif