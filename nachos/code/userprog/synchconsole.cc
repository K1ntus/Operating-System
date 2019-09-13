#ifdef CHANGED
#include "copyright.h"
#include "system.h"
#include "synchconsole.h"
#include "synch.h"



static Semaphore *readAvail;
static Semaphore *writeDone;
static int BUFFER_SIZE = 1024;


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
/*
//ASYNC
   int ch = incoming;

   incoming = EOF;
   return ch;
*/
// ...

    return 1;
}

void SynchConsole::SynchPutChar(int ch) {
/*
//ASYNC

    unsigned char c;
    ASSERT(putBusy == FALSE);
    if (ch < 0x80 || strcmp(nl_langinfo(CODESET),"UTF-8")) {
	// Not UTF-8 or ASCII, assume 8bit locale 
	c = ch;
        WriteFile(writeFileNo, &c, sizeof(c));
    } else if (ch < 0x100) {
	// Non-ASCII UTF-8, thus two bytes 
	c = ((ch & 0xc0) >> 6) | 0xc0;
        WriteFile(writeFileNo, &c, sizeof(c));
	c = (ch & 0x3f) | 0x80;
        WriteFile(writeFileNo, &c, sizeof(c));
    } // Else not latin1, drop 
    putBusy = TRUE;
    interrupt->Schedule(ConsoleWriteDone, this, ConsoleTime,
					ConsoleWriteInt);
*/


// ...

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




//----------------------------------------------------------------------
// ConsoleTest
//      Test the console by echoing characters typed at the input onto
//      the output.  Stop when the user types a 'q'.
//----------------------------------------------------------------------


#endif // CHANGED