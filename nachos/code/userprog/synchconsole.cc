#ifdef CHANGED
#include "copyright.h"
#include "synchconsole.h"
#include "synch.h"
#include "system.h"

//----------------------------------------------------------------------
// DEBUG_MODE
// 	Enable/Disable verbose mode for some functions. Helping mostly for debugging purposes.
//
//	1 -- Activate this mode
//	0 -- Deactivate this mode
//----------------------------------------------------------------------
#define DEBUG_MODE 0

// External functions used by this file
extern bool ReadMem(int addr, int size, int *value);

static Semaphore *readAvail;
static Semaphore *writeDone;

static void ReadAvailHandler(void *arg)
{
    (void)arg;
    readAvail->V();
}
static void WriteDoneHandler(void *arg)
{
    (void)arg;
    writeDone->V();
}

//----------------------------------------------------------------------
// SynchConsole::SynchConsole
// 	Initialize the simulation of a hardware console device using a synchronisation feature.
//
//	"readFile" -- UNIX file simulating the keyboard (NULL -> use stdin)
//	"writeFile" -- UNIX file simulating the display (NULL -> use stdout)
//----------------------------------------------------------------------
SynchConsole::SynchConsole(const char *readFile, const char *writeFile)
{
    readAvail = new Semaphore("read avail", 0);
    writeDone = new Semaphore("write done", 0);
    threadReadProtector = new Semaphore("thread read", 1);
    threadWriteProtector = new Semaphore("thread write", 1);

    ASSERT(readAvail);
    ASSERT(threadReadProtector);

    ASSERT(writeDone);
    ASSERT(threadWriteProtector);

    console = new Console(readFile, writeFile, ReadAvailHandler, WriteDoneHandler, 0);
    ASSERT(console);
}

//----------------------------------------------------------------------
// SynchConsole::~SynchConsole
// 	Clean up synchronisation console emulation
//----------------------------------------------------------------------
SynchConsole::~SynchConsole()
{
    delete console;

    delete readAvail;
    delete threadReadProtector;

    delete writeDone;
    delete threadWriteProtector;
}

//----------------------------------------------------------------------
// SynchConsole::SynchGetChar()
// 	Read a character from the input buffer, if there is any there.
//	Either return the character, or EOF if none buffered or the end of the
//	input file was reached.
//----------------------------------------------------------------------
int SynchConsole::SynchGetChar()
{
    int ch;

    threadReadProtector->V();
    readAvail->P(); // wait for character to arrive
    ch = console->GetChar();
    threadReadProtector->P();

    if (DEBUG_MODE)
    {
        if (ch == '\n')
            fprintf(stderr, "[DEBUG@SynchGetChar] GetChar:\\n\n");
        else if (ch == '\0')
            fprintf(stderr, "[DEBUG@SynchGetChar] GetChar:\\0\n");
        else
            fprintf(stderr, "[DEBUG@SynchGetChar] GetChar:%c\n", ch);
    }

    return ch;
}

//----------------------------------------------------------------------
// SynchConsole::SynchPutChar(int ch)
// 	Write a character to the simulated display, schedule an interrupt
//	to occurs in the future, and return.
//
//      "ch" the integer representation of the character to put into
//          the simulated display.
//----------------------------------------------------------------------
void SynchConsole::SynchPutChar(int ch)
{
    if (DEBUG_MODE)
    {
        if (ch == '\n')
            fprintf(stderr, "[DEBUG@SynchPutChar] PutChar:\\n\n");
        else if (ch == '\0')
            fprintf(stderr, "[DEBUG@SynchPutChar] PutChar:\\0\n");
        else
            fprintf(stderr, "[DEBUG@SynchPutChar] PutChar:%c\n", ch);
    }
    threadWriteProtector->P();
    console->PutChar(ch); // echo it!
    writeDone->P();       // wait for write to finish
    threadWriteProtector->V();
}

//----------------------------------------------------------------------
// SynchConsole::SynchPutString
//      Write an array of character to the simulated display. Using a synchronous
//      scheduling system. The maximum size of the string analysed is set
//      with the constant MAX_STRING_SIZE-1 (system.h).
//
//      We kept the last position for the print of the null character.
//      (for now, but this way of work is probably deprecated and pointless)
//
//      "s" is the const array containing the string to display
//      This array can NOT be NULL.
//----------------------------------------------------------------------
void SynchConsole::SynchPutString(const char s[])
{
    ASSERT(s != NULL);

    int i = 0;
    while (i < MAX_STRING_SIZE - 1)
    {
        SynchPutChar((int)s[i]);
        if (s[i] == '\0')
            break;

        i++;
    }

    // To think about this conditional instruction,
    // does not seems really interesting in case of great string size,
    // cutting the string with multiple \0
    if (s[i] != '\0')
    {
        //fprintf(stderr, "SynchPutString INFO - end of string not reached, last character is: %c at pos:%d", s[i],i);
        SynchPutChar((int)('\0'));
    }
}

//----------------------------------------------------------------------
// SynchConsole::copyStringFromMachine
//      Copy the string content located at the adress from into
//      a char* buffer. For a limited number of 'size' character
//
//      "from" the address of the beginning of the string that we want
//              to copy. This address can NOT be equals to the NULL address
//              (ie. 0x0)
//      "to" a char array that will store the string that has been read
//              from the machine
//      "size" the maximum numbers of character to store into the buffer (usually majored by
//              the constant MAX_STRING_SIZE located into system.h
//              The size can NOT be negative or greater than MAX_STRING_SIZE.
//----------------------------------------------------------------------
int SynchConsole::copyStringFromMachine(int from, char *to, unsigned size)
{
    ASSERT(size > 0);
    ASSERT(size <= MAX_STRING_SIZE);
    ASSERT(from != 0x0);

    unsigned int number_character_read = 0;
    int character = 1;

    while (number_character_read < size - 1)
    {

        machine->ReadMem(from + number_character_read, 1, &character); //ReadMem is already taking care of the Translation (virt <-> phys memory)
        to[number_character_read] = (char)character;
        if ((char)character == '\0')
        {
            break;
        }
        number_character_read += 1; /* On récupère, on test si /0 si /0 -> break, sinon putchar, à la fin p-e rajouter un /0 */
        to[number_character_read] = '\0';
    }

    return number_character_read;
}

//----------------------------------------------------------------------
// SynchConsole::SynchGetString
//      Write an array of character to the simulated display. Using a synchronous
//      scheduling system. The maximum size of the string analysed is set
//      with the constant MAX_STRING_SIZE-1 (system.h).
//
//      We kept the last position for the print of the null character.
//      (for now, but this way of work is probably deprecated and pointless)
//
//      "s" is the char array that will contains the result of the reading
//          from the simulated display
//      "n" is the maximum size of the array. For now, the length cannot be
//          greater than MAX_STRING_SIZE, to prevent some possible grief of the machine
//          until a better implementation will be set up.
//          The size can NOT be negative or greater than MAX_STRING_SIZE.
//----------------------------------------------------------------------
void SynchConsole::SynchGetString(char *s, int n)
{ //Fgets
    ASSERT(n > 0);
    //ASSERT(n <= MAX_STRING_SIZE);
    ASSERT(s != 0x0);

    int max_size = n;

    if (n <= MAX_STRING_SIZE)
        max_size = MAX_STRING_SIZE;

    int pos_in_buffer = 0;
    int char_readed = 1;
    char *buffer = (char *)malloc(sizeof(char) * max_size);
    ASSERT(buffer != 0x0);

    while (pos_in_buffer < max_size && char_readed != '\0' && char_readed != '\n')
    {
        char_readed = this->SynchGetChar();
        s[pos_in_buffer] = char_readed;
        pos_in_buffer += 1;
        s[pos_in_buffer] = '\0';
    }
}

//----------------------------------------------------------------------
// SynchConsole::copyStringToMachine
//      Copy the string content located in the buffer 'from' to the machine address 'to'.
//          For a limited number of 'size' character
//
//      "to" the address of the beginning of the machine address where we want
//              to copy the from char array.
//      "from" a char array that store the string that need to be paste
//              into the machine. This array can NOT be null
//      "size" the maximum numbers of character to copy into the machine (usually majored by
//              the constant MAX_STRING_SIZE located into system.h. This size, in fact
//              cannot be greater than this constant, to prevent malicious code
//              to write into forbidden memory slots.
//              Could probably fixed when a better implementation will be up.
//              The size can NOT be negative or greater than MAX_STRING_SIZE.
//----------------------------------------------------------------------
int SynchConsole::copyStringToMachine(int to, char *from, unsigned int size)
{
    ASSERT(from);
    ASSERT(size > 0);
    ASSERT(size <= MAX_STRING_SIZE);

    unsigned int number_character_read = 0;
    while (number_character_read < size)
    {
        if (DEBUG_MODE)
        {
            fprintf(stderr, "[DEBUG@copyStringToMachine] Write Char:%c. SlotID=%d\n", from[number_character_read], number_character_read);
        }

        machine->WriteMem(to + number_character_read, 1, from[number_character_read]); //ReadMem is already managing the Translation (virt <-> phys memory)

        if (from[number_character_read] == '\0' || from[number_character_read] == '\n')
        {

            if (DEBUG_MODE)
            {
                fprintf(stderr, "[DEBUG@copyStringToMachine] Read Char: \\0 or \\n at position:%d\n", number_character_read);
            }
            break;
        }
        number_character_read += 1;
    }

    return number_character_read;
}

//----------------------------------------------------------------------
// SynchConsole::PutInt
//      Put a String to the simulated console, convert a signed int to a char*
//          by using the snprintf function. Then it will be copied to the
//          console with the SynchPutString function.
//
//      "n" the signed integer value to be printed in the simulated console.
//----------------------------------------------------------------------
void SynchConsole::PutInt(int n)
{
    char *buffer = (char *)malloc(sizeof(char) * MAX_STRING_SIZE);
    ASSERT(buffer != 0x0);

    int size = snprintf(buffer, MAX_STRING_SIZE - 1, "%d", n);
    buffer[size] = '\0';

    this->SynchPutString(buffer);

    free(buffer);
}

//----------------------------------------------------------------------
// SynchConsole::GetInt
//      Get a String from the simulated console, convert it to a signed int using
//          the sscanf function and then copy it to the address of the integer
//          parameter.
//
//      "n" the address of that will store the conversion of the simulated console
//          string entry as an signed integer.
//----------------------------------------------------------------------
void SynchConsole::GetInt(int *n)
{
    ASSERT(n != 0x0);

    char *buffer = (char *)malloc(sizeof(char) * MAX_STRING_SIZE);
    ASSERT(buffer != 0x0);

    this->SynchGetString(buffer, MAX_STRING_SIZE);

    int ret = sscanf(buffer, "%d", n);
    if (ret == EOF)
    {
        fprintf(stderr, "[WARNING] GetInt invoked an error while performing sscanf call with argument : [%s] and saving to address %p\n", buffer, &n);
        fprintf(stderr, "[WARNING] Make sure you're not sending an invalid argument.\n");
    }

    free(buffer);
}

#endif //CHANGED
