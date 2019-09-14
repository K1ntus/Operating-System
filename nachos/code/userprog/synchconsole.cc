#ifdef CHANGED
#include "copyright.h"
#include "system.h"
#include "synchconsole.h"
#include "synch.h"


#define DEBUG_MODE 1   //1:true, 0:false    //Enable/Disable generation of < ... > surrounding each chars that has been read

// External functions used by this file
extern bool ReadMem(int addr, int size, int* value);


static Semaphore *readAvail;
static Semaphore *writeDone;

static void ReadAvailHandler(void *arg) { (void) arg; readAvail->V(); }
static void WriteDoneHandler(void *arg) { (void) arg; writeDone->V(); }


SynchConsole::SynchConsole(const char *readFile, const char *writeFile)

{
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
/*
//ASYNC
   int ch = incoming;

   incoming = EOF;
   return ch;
*/
// ...
}

void SynchConsole::SynchPutChar(int ch) {
    console->PutChar (ch);	    // echo it!
    writeDone->P ();	        // wait for write to finish
}

void SynchConsole::SynchPutString(const char s[]) {
    size_t size_string = strlen(s);

    for(size_t i = 0; i < size_string; i++){
        SynchConsole::SynchPutChar(s[i]);
    }
}

void SynchConsole::SynchGetString(char *s, int n) {
    if(n <= 0){
        //ERROR
        return;
    }

    s[0] = '\0';
    int pos_in_buffer = 0;

    while(--n > 0) {        
        int char_readed = SynchConsole::SynchGetChar();
        if(char_readed == EOF || char_readed == '\n') {
            break;
        } else {
            s[pos_in_buffer] = char_readed;
            s[pos_in_buffer+1] = '\0';
        }
    }    
}

void SynchConsoleTest (const char * in, const char * out) {
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
    fprintf(stderr, "EOF detected in SynchConsole!\n");
}


int copyStringFromMachine(int from, char *to, unsigned size) {
    
    unsigned int number_character_written = 0;

    int* character = (int *) malloc(sizeof(int) * size);

    //bool ReadMem(int addr, int size, int* value); //machine.h
   /* while(ReadMem(from, sizeof(char), (character+number_character_written)) && number_character_written < size){
        if(character[number_character_written] == '\0'){
            to[number_character_written+1] = '\0';
            break;
        }
        to[number_character_written] = character[number_character_written];
        number_character_written += 1;
    }*/
    
    free(character);
    return number_character_written;
    
}

#endif // CHANGED