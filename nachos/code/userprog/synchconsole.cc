#ifdef CHANGED
#include "copyright.h"
#include "system.h"
#include "synchconsole.h"
#include "synch.h"


#define DEBUG_MODE 0   //1:true, 0:false    //Enable/Disable generation of < ... > surrounding each chars that has been read
#define TEST_STRING_BUFFER_SIZE 1023

// External functions used by this file
extern bool ReadMem(int addr, int size, int* value);

static Semaphore *readAvail;
static Semaphore *writeDone;

static void ReadAvailHandler(void *arg) { (void) arg; readAvail->V(); }
static void WriteDoneHandler(void *arg) { (void) arg; writeDone->V(); }

SynchConsole::SynchConsole(const char *readFile, const char *writeFile) {
    readAvail = new Semaphore ("read avail", 0);
    writeDone = new Semaphore ("write done", 0);
    console = new Console (readFile, writeFile, ReadAvailHandler, WriteDoneHandler, 0);
}



SynchConsole::~SynchConsole() {
    delete console;
    delete writeDone;
    delete readAvail;
}


int SynchConsole::SynchGetChar() {
    int ch;

	readAvail->P ();	// wait for character to arrive
	ch = console->GetChar ();

    if(ch == EOF) {
        return EOF;
    }

    return ch;
}

void SynchConsole::SynchPutChar(int ch) {
    console->PutChar (ch);	    // echo it!
    writeDone->P ();	        // wait for write to finish
}


void SynchConsole::SynchPutString(const char s[]) {
    size_t size_string = strlen(s);

    for(size_t i = 0; i < size_string; i++){
        SynchPutChar(s[i]);
    }
}

void SynchConsole::SynchGetString(char *s, int n) { //Fgets
    if(n <= 0){
        //ERROR
        return;
    }

    s[0] = '\0';
    int pos_in_buffer = 0;

    while(--n > 0) {        
        int char_readed = SynchConsole::SynchGetChar();
        if(char_readed == EOF || char_readed == '\n') {
            if(DEBUG_MODE)
                fprintf(stderr, "[DEBUG@SynchGetString] EOF/NewLine\n");
            break;
        } else {
            s[pos_in_buffer] = char_readed;
            s[pos_in_buffer+1] = '\0';
            if(DEBUG_MODE)
                fprintf(stderr, "[DEBUG@SynchGetString] Char:%c\n", s[pos_in_buffer]);
            pos_in_buffer+=1;
        }
    }    
}



int SynchConsole::copyStringFromMachine(int from, char *to, unsigned size) {
    
    unsigned int number_character_read = 0;
    int character = 1;
    //int * phys_adress = NULL;


    //fprintf(stderr, " * from&0x3: %d\n * from: %d\n * val_from:%c\n", from & 0x3, from, (char) from);
    //fprintf(stderr, " * from: %p\n * phys_adress: %p\n * val:%c\n", &from, phys_adress, (char) from);
    //ExceptionType Machine::Translate(int virtAddr, int* physAddr, int size, bool writing)
   
   /*
    ExceptionType exception = machine->Translate(from, phys_adress, sizeof(int), false);    //Syscall exception
    if (exception != NoException) {
        fprintf(stderr, "DEBUG@Exception raised in SynchConsole::copyStringFromMachine\n");
        fprintf(stderr, "from: %d\n phys_adress: %p\n\n", from, phys_adress);
        machine->RaiseException(exception, from);
        return -1;
    }*/


    //bool ReadMem(int addr, int size, int* value); //machine.h
    while(number_character_read < size){/* while avec la taille du buffer */
        //fprintf(stderr, "Iteration@%d\n", number_character_read);

    fprintf(stderr, "READMEM: %d, %p\n", from + number_character_read, &character);


        machine->ReadMem(from + number_character_read, 1, &character);   //ReadMem is already taking care of the Translation
        //console->GetChar ();
        to[number_character_read] = (char) character;
        number_character_read += 1; /* On récupère, on test si /0 si /0 -> break, sinon putchar, à la fin p-e rajouter un /0 */
    }
    
    to[number_character_read] ='\0';
    number_character_read+=1;

    return number_character_read;

}


bool SynchConsoleCopyString_01(const char * in, const char * out) {
    char * char_buffer = (char *) malloc(sizeof(char) * TEST_STRING_BUFFER_SIZE);
    SynchConsole * test_synchconsole = new SynchConsole(in, out);

    test_synchconsole->SynchGetString(char_buffer, TEST_STRING_BUFFER_SIZE);


    //TODO

    free(char_buffer);
    delete(test_synchconsole);
    test_synchconsole = NULL;

    return true;
}












/*  TESTS   */

bool SynchConsoleTestChar_01(const char * in, const char * out){
    char ch;
    SynchConsole * test_synchconsole = new SynchConsole(in, out);
    while ((ch = test_synchconsole->SynchGetChar()) != EOF){
        if(DEBUG_MODE){
            test_synchconsole->SynchPutChar('<');
            test_synchconsole->SynchPutChar(ch);
            test_synchconsole->SynchPutChar('>');
            test_synchconsole->SynchPutChar('\n');
        } else {
            test_synchconsole->SynchPutChar(ch);

        }
    }
    
    if(DEBUG_MODE){
        fprintf(stderr, "[DEBUG@SynchConsoleTestChar_01] EOF detected in SynchConsoleTestChar!\n");
    }


    delete test_synchconsole;
    
    test_synchconsole = NULL;
    return true;
}

bool SynchConsoleTestString_01(const char * in, const char * out) {
    char * char_buffer = (char *) malloc(sizeof(char) * TEST_STRING_BUFFER_SIZE);
    SynchConsole * test_synchconsole = new SynchConsole(in, out);

    //Test if first line is already EOF
    test_synchconsole->SynchGetString(char_buffer, TEST_STRING_BUFFER_SIZE);
    if(DEBUG_MODE)
        fprintf(stderr, "[DEBUG@TestString_01] char: %s\n", char_buffer);


    while(char_buffer[0] != '\0') {
        char_buffer[0] = '\0';
        test_synchconsole->SynchGetString(char_buffer, TEST_STRING_BUFFER_SIZE);
        if(DEBUG_MODE)
            fprintf(stderr, "[DEBUG@TestString_01] char: %s\n", char_buffer);
    }


    free(char_buffer);
    delete(test_synchconsole);
    test_synchconsole = NULL;

    return true;
}

bool SynchConsoleTestCopyString_01(const char * in, const char * out) {
    char * char_buffer = (char *) malloc(sizeof(char) * TEST_STRING_BUFFER_SIZE);
    SynchConsole * test_synchconsole = new SynchConsole(in, out);

    /*
    char name[13] = "StudyTonight";       // valid character array initialization
    int  int_name[13];
    for(int i = 0; i < 13; i++){
        int_name[i] = name[i];
    }*/

    int int_name2[13] = {83, 116, 117, 100, 121, 84, 111, 110, 105, 103, 104, 116};
    int res = test_synchconsole->copyStringFromMachine(int_name2[0], char_buffer, 120);
    
    if (res != 14){
        free(char_buffer);
        delete(test_synchconsole);
        test_synchconsole = NULL;

        return false;
    }




    free(char_buffer);
    delete(test_synchconsole);
    test_synchconsole = NULL;

    return true;
}


/* Main Test Handler*/
void SynchConsoleTest (const char * in, const char * out) {
    const int NUMBER_TEST = 3;
    int number_test_success = 0;
    fprintf(stderr, "\n[INFO] SynchConsole::SynchConsoleTest launching tests\n");

    /* Test 1 */
        fprintf(stderr, "[INFO] SynchConsole::SynchConsoleTestChar_01 test :\n");
    if(SynchConsoleTestChar_01(in, out)) {
        fprintf(stderr, "\t * success\n");
        number_test_success += 1;
    } else {
        fprintf(stderr, "\t * FAILURE\n");
    }

    /* Test 2 */
        fprintf(stderr, "[INFO] SynchConsole::SynchConsoleTestString_01 test :\n");
    if(SynchConsoleTestString_01(in,out)) {
        fprintf(stderr, "\t * success\n");
        number_test_success += 1;
    } else {
        fprintf(stderr, "\t * FAILURE\n");
    }

    /* Test 2 */
        fprintf(stderr, "[INFO] SynchConsole::SynchConsoleTestCopyString_01 test :\n");
    if(SynchConsoleTestCopyString_01(in,out)) {
        fprintf(stderr, "\t * success\n");
        number_test_success += 1;
    } else {
        fprintf(stderr, "\t * FAILURE\n");
    }

    fprintf(stderr,"[INFO] Test success: %d over %d\n", number_test_success, NUMBER_TEST);
}

#endif // CHANGED

