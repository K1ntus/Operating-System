// progtest.cc 
//      Test routines for demonstrating that Nachos can load
//      a user program and execute it.  
//
//      Also, routines for testing the Console hardware device.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "console.h"
#include "addrspace.h"
#include "synch.h"


// Data structures needed for the console test.  Threads making
// I/O requests wait on a Semaphore to delay until the I/O completes.

static Console *console;
static Semaphore *readAvail;
static Semaphore *writeDone;

//----------------------------------------------------------------------
// ConsoleInterruptHandlers
//      Wake up the thread that requested the I/O.
//----------------------------------------------------------------------

static void
ReadAvailHandler (void *arg)
{
    (void) arg;
    readAvail->V ();
}
static void
WriteDoneHandler (void *arg)
{
    (void) arg;
    writeDone->V ();
}

//----------------------------------------------------------------------
// StartProcess
//      Run a user program.  Open the executable, load it into
//      memory, and jump to it.
//----------------------------------------------------------------------

void StartProcess (char *filename) {

    OpenFile *executable = fileSystem->Open (filename);
    AddrSpace *space;

    if (executable == NULL)
    {
        SetColor (stdout, ColorRed);
        SetBold (stdout);
        printf ("Unable to open file %s\n", filename);
        ClearColor (stdout);
        return;
    }
    space = new AddrSpace (executable);
    currentThread->space = space;

    delete executable;		// close file

    space->InitRegisters ();	// set the initial register values
    space->RestoreState ();	// load page table register

    //machine->DumpMem ("memory.svg");
    machine->Run ();		// jump to the user progam
    ASSERT (FALSE);		// machine->Run never returns;
    

    interrupt->Halt();
    // the address space exits
    // by doing the syscall "exit"
}

//----------------------------------------------------------------------
// ConsoleTest
//      Test the console by echoing characters typed at the input onto
//      the output.  Stop when the user types a 'q'.
//----------------------------------------------------------------------

void ConsoleTest (const char *in, const char *out) {
    char ch;

    if(in == NULL && out == NULL)
        fprintf(stderr,"[INFO] ConsoleTest: Interactive test using '<'output'>'\n");
    else
        fprintf(stderr,"[INFO] ConsoleTest: Reading Test from file %s to %s\n", in, out);


    readAvail = new Semaphore ("read avail", 0);
    writeDone = new Semaphore ("write done", 0);
    console = new Console (in, out, ReadAvailHandler, WriteDoneHandler, 0);

    for (;;) {
      
	    readAvail->P ();	// wait for character to arrive
	    
        ch = console->GetChar ();
        if (ch!='\n'){
            console->PutChar ('<');	    // echo it!
            writeDone->P ();	        // wait for write to finish
            console->PutChar (ch);  	// echo it!
            writeDone->P ();	        // wait for write to finish
            console->PutChar ('>');	    // echo it!
            writeDone->P ();        	// wait for write to finish

        console->PutChar ('\n');	// echo it!
        writeDone->P ();	        // wait for write to finish
        }
        

      if (ch == 'q' || ch == -1) {
            fprintf (stderr, "[INFO] ConsoleTest: Exit\n\n");
	      break;		// if q, quit
	  }
    
    }
    
    delete console;
    delete readAvail;
    delete writeDone;
}


//----------------------------------------------------------------------
// SynchConsoleTest
//      Test the synchconsole by echoing characters typed at the input onto
//      the output.  Stop when the user types a 'q'.
//      Also test the synchconsole using a few methods predefined
//----------------------------------------------------------------------
void SynchConsoleTest (const char * in, const char * out) {
    SynchConsole * test_synch_console = new SynchConsole(in, out);

    if(in == NULL && out == NULL)
        fprintf(stderr,"[INFO] SynchConsoleTest: Interactive test using '<'output'>'\n");
    else
        fprintf(stderr,"[INFO] SynchConsoleTest: Reading Test from file %s to %s\n", in, out);

    char ch;
    for (;;) {
        ch = test_synch_console->SynchGetChar();
        if(ch == '\n'){
            test_synch_console->SynchPutChar(ch);
        } else {
            test_synch_console->SynchPutChar('<');
            test_synch_console->SynchPutChar(ch);
            test_synch_console->SynchPutChar('>');
            test_synch_console->SynchPutChar('\n');
        }
        
        if (ch == 'q' || ch == -1) {
            fprintf (stderr, "[INFO] SynchConsoleTest: Exit\n\n");
            break;		// if q, quit
        }
        
    }
    delete test_synch_console;
    delete readAvail;
    delete writeDone;

}

