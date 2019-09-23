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




//----------------------------------------------------------------------
// SynchConsole::SynchConsole
// 	Initialize the simulation of a hardware console device using a synchronisation feature.
//
//	"readFile" -- UNIX file simulating the keyboard (NULL -> use stdin)
//	"writeFile" -- UNIX file simulating the display (NULL -> use stdout)
// 	"readAvailHandler" is the interrupt handler called when a character arrives
//		from the keyboard
// 	"writeDoneHandler" is the interrupt handler called when a character has
//		been output, so that it is ok to request the next char be
//		output
//----------------------------------------------------------------------
SynchConsole::SynchConsole(const char *readFile, const char *writeFile) {
    readAvail = new Semaphore ("read avail", 0);
    writeDone = new Semaphore ("write done", 0);
    console = new Console (readFile, writeFile, ReadAvailHandler, WriteDoneHandler, 0);
}



//----------------------------------------------------------------------
// SynchConsole::~SynchConsole
// 	Clean up synchronisation console emulation
//----------------------------------------------------------------------
SynchConsole::~SynchConsole() {
    delete console;
    delete writeDone;
    delete readAvail;
}


//----------------------------------------------------------------------
// SynchConsole::SynchGetChar()
// 	Read a character from the input buffer, if there is any there.
//	Either return the character, or EOF if none buffered or the end of the
//	input file was reached.
//----------------------------------------------------------------------
int SynchConsole::SynchGetChar() {
    int ch;

	readAvail->P ();	// wait for character to arrive
	ch = console->GetChar ();

    /* //Useless statement
    if(ch == EOF) { //Mb not that much, make it halt the prog if EOF ?
        return EOF;
    }
    */

    return ch;
}


//----------------------------------------------------------------------
// SynchConsole::SynchPutChar(int ch)
// 	Write a character to the simulated display, schedule an interrupt 
//	to occur in the future, and return.
//----------------------------------------------------------------------
void SynchConsole::SynchPutChar(int ch) {
    console->PutChar (ch);	    // echo it!
    writeDone->P ();	        // wait for write to finish
}


//----------------------------------------------------------------------
// Initialize
//      Initialize Nachos global data structures.  Interpret command
//      line arguments in order to determine flags for the initialization.  
// 
//      "argc" is the number of command line arguments (including the name
//              of the command) -- ex: "nachos -d +" -> argc = 3 
//      "argv" is an array of strings, one for each command line argument
//              ex: "nachos -d +" -> argv = {"nachos", "-d", "+"}


// TODO



//----------------------------------------------------------------------
void SynchConsole::SynchPutString(const char s[]) {
    if(s == NULL){
        //ERROR CASE
        return;        
    }

    int i = 0;
    while(i < MAX_STRING_SIZE){
        if(s[i] == '\0')
            break;

        this->SynchPutChar((int) s[i]);
        i++;
    }
}



//----------------------------------------------------------------------
// Initialize
//      Initialize Nachos global data structures.  Interpret command
//      line arguments in order to determine flags for the initialization.  
// 
//      "argc" is the number of command line arguments (including the name
//              of the command) -- ex: "nachos -d +" -> argc = 3 
//      "argv" is an array of strings, one for each command line argument
//              ex: "nachos -d +" -> argv = {"nachos", "-d", "+"}


// TODO



//----------------------------------------------------------------------
int SynchConsole::copyStringFromMachine(int from, char *to, unsigned size) {
    
    unsigned int number_character_read = 0;
    int character = 1;
    while(number_character_read < size){/* while avec la taille du buffer */

        machine->ReadMem(from + number_character_read*sizeof(int), sizeof(int), &character);   //ReadMem is already taking care of the Translation (virt <-> phys memory)
        //console->GetChar ();
        if((char) character == '\0') {
            to[number_character_read] ='\0';
            number_character_read+=1;
            break;
        }
        to[number_character_read] = (char) character;
        number_character_read += 1; /* On récupère, on test si /0 si /0 -> break, sinon putchar, à la fin p-e rajouter un /0 */
    }
    

    return number_character_read;

}


//----------------------------------------------------------------------
// Initialize
//      Initialize Nachos global data structures.  Interpret command
//      line arguments in order to determine flags for the initialization.  
// 
//      "argc" is the number of command line arguments (including the name
//              of the command) -- ex: "nachos -d +" -> argc = 3 
//      "argv" is an array of strings, one for each command line argument
//              ex: "nachos -d +" -> argv = {"nachos", "-d", "+"}


// TODO



//----------------------------------------------------------------------
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


//----------------------------------------------------------------------
// Initialize
//      Initialize Nachos global data structures.  Interpret command
//      line arguments in order to determine flags for the initialization.  
// 
//      "argc" is the number of command line arguments (including the name
//              of the command) -- ex: "nachos -d +" -> argc = 3 
//      "argv" is an array of strings, one for each command line argument
//              ex: "nachos -d +" -> argv = {"nachos", "-d", "+"}


// TODO



//----------------------------------------------------------------------
int SynchConsole::copyStringToMachine(int to, char *from, unsigned int size) {

    fprintf(stderr,"Entry String:%s\n", from);
    
    unsigned int number_character_read = 0;


    while(number_character_read < size){/* while avec la taille du buffer */
        if(DEBUG_MODE) {
            fprintf(stderr, "[DEBUG@copyStringToMachine] Write Char:%c. SlotID=%d\n", from[number_character_read], number_character_read);
        }

        machine->WriteMem(to + number_character_read*sizeof(int), sizeof(int), from[number_character_read]);   //ReadMem is already taking care of the Translation (virt <-> phys memory)


        //console->GetChar ();
        if((char) from[number_character_read] == '\0' || (char) from[number_character_read] == '\n') {
            break;
        }
        number_character_read += 1; /* On récupère, on test si /0 si /0 -> break, sinon putchar, à la fin p-e rajouter un /0 */

    }
    

    return number_character_read;

}







/*  TESTS   */
#if 0
bool SynchConsole::SynchConsoleTestChar_01(){
    char ch;
    while ((ch = SynchGetChar()) != EOF){
        if(DEBUG_MODE){
            SynchPutChar('<');
            SynchPutChar(ch);
            SynchPutChar('>');
            SynchPutChar('\n');
        } else {
            SynchPutChar(ch);

        }
    }
    
    if(DEBUG_MODE){
        fprintf(stderr, "[DEBUG@SynchConsoleTestChar_01] EOF detected in SynchConsoleTestChar!\n");
    }


    return true;
}

bool SynchConsole::SynchConsoleTestString_01() {
    char * char_buffer = (char *) malloc(sizeof(char) * TEST_STRING_BUFFER_SIZE);

    //Test if first line is already EOF
    SynchGetString(char_buffer, TEST_STRING_BUFFER_SIZE);
    if(DEBUG_MODE)
        fprintf(stderr, "[DEBUG@TestString_01] char: %s\n", char_buffer);


    while(char_buffer[0] != '\0') {
        char_buffer[0] = '\0';
        SynchGetString(char_buffer, TEST_STRING_BUFFER_SIZE);
        if(DEBUG_MODE)
            fprintf(stderr, "[DEBUG@TestString_01] char: %s\n", char_buffer);
    }


    free(char_buffer);

    return true;
}

bool SynchConsole::SynchConsoleTestCopyString_01() {
    char * char_buffer = (char *) malloc(sizeof(char) * TEST_STRING_BUFFER_SIZE);


    
    // char name[13] = "StudyTonight";       // valid character array initialization
    // int  int_name[13];
    // for(int i = 0; i < 13; i++){
    //     int_name[i] = name[i];
    // }

    int int_name2[13] = {83, 116, 117, 100, 121, 84, 111, 110, 105, 103, 104, 116};
    int res = copyStringFromMachine(int_name2[0], char_buffer, 120);
    
    if (res != 14){
        free(char_buffer);

        return false;
    }




    free(char_buffer);

    return true;
}
#endif  // Test (deprecated)

#endif // CHANGED

