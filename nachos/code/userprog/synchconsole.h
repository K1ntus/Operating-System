#ifdef CHANGED
#ifndef SYNCHCONSOLE_H
#define SYNCHCONSOLE_H

#include "copyright.h"
#include "utility.h"
#include "console.h"
#include "machine.h"
#include "translate.h"
#include "synch.h"

class SynchConsole:dontcopythis {
    public:
        SynchConsole(const char *readFile, const char *writeFile);
        // initialize the hardware console device
        ~SynchConsole();                        // clean up console emulation

        void SynchPutChar(int ch);              // Unix putchar(3S)
        int SynchGetChar();                     // Unix getchar(3S)
        void SynchPutString(const char *s);      // Unix fputs(3S)
        void SynchGetString(char *s, int n);     // Unix fgets(3S)

        int copyStringFromMachine(int from, char *to, unsigned size);
        int copyStringToMachine(int to, char *from, unsigned size);


        void PutInt (int n);
        void GetInt (int * n);
        /*
        bool SynchConsoleTestChar_01 ();
        bool SynchConsoleTestString_01 ();
        bool SynchConsoleTestCopyString_01 ();
        */
    
    private:
        Console *console;
        Semaphore * threadReadProtector;
        Semaphore * threadWriteProtector;

};


#endif // SYNCHCONSOLE_H
#endif // CHANGED