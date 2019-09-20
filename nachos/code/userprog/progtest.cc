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

//----------------------------------------------------------------------
// StartProcess
//      Run a user program.  Open the executable, load it into
//      memory, and jump to it.
//----------------------------------------------------------------------

void
StartProcess (char *filename)
{
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

    // the address space exits
    // by doing the syscall "exit"
}

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
// ConsoleTest
//      Test the console by echoing characters typed at the input onto
//      the output.  Stop when the user types a 'q'.
//----------------------------------------------------------------------

void
ConsoleTest (const char *in, const char *out)
{
    char ch;

    readAvail = new Semaphore ("read avail", 0);
    writeDone = new Semaphore ("write done", 0);
    console = new Console (in, out, ReadAvailHandler, WriteDoneHandler, 0);

    for (;;)
      {
      
	  readAvail->P ();	// wait for character to arrive
	  ch = console->GetChar ();

//    printf("Code: %d", ch);
/*	  
	  if(ch != 10) {    //END-LINE CODE

*/
        console->PutChar ('<');	    // echo it!
        writeDone->P ();	        // wait for write to finish
        console->PutChar (ch);  	// echo it!
        writeDone->P ();	        // wait for write to finish
        console->PutChar ('>');	    // echo it!
        writeDone->P ();        	// wait for write to finish

        console->PutChar ('\n');	// echo it!
        writeDone->P ();	        // wait for write to finish

/*
      } else {  //It is the end-line char, no need to print the < and > char or echo it
    	  writeDone->P ();	        // wait for write to finish
      }*/
      
      if (ch == 'q' || ch == -1) {
	      printf ("\nAu revoir!\n");
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


    if(in != NULL && out != NULL){  //TO COMPLETE
        const int NUMBER_TEST = 3;
        int number_test_success = 0;
        fprintf(stderr, "\n[INFO] SynchConsole::SynchConsoleTest launching tests\n");

        /* Test 1 */
        fprintf(stderr, "[INFO] SynchConsole::SynchConsoleTestChar_01 test :\n");
        if(test_synch_console->SynchConsoleTestChar_01(in, out)) {
            fprintf(stderr, "\t * success\n");
            number_test_success += 1;
        } else {
            fprintf(stderr, "\t * FAILURE\n");
        }

        /* Test 2 */
        fprintf(stderr, "[INFO] SynchConsole::SynchConsoleTestString_01 test :\n");
        if(test_synch_console->SynchConsoleTestString_01(in,out)) {
            fprintf(stderr, "\t * success\n");
            number_test_success += 1;
        } else {
            fprintf(stderr, "\t * FAILURE\n");
        }

        /* Test 3 */
        /*
        fprintf(stderr, "[INFO] SynchConsole::SynchConsoleTestCopyString_01 test :\n");
        if(test_synch_console->SynchConsoleTestCopyString_01(in,out)) {
            fprintf(stderr, "\t * success\n");
            number_test_success += 1;
        } else {
            fprintf(stderr, "\t * FAILURE\n");
        }
        */

        fprintf(stderr,"[INFO] Test success: %d over %d\n", number_test_success, NUMBER_TEST);
    }

    fprintf(stderr,"[INFO] SynchConsole: Interactive test using '<'output'>'\n");


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
	        fprintf (stderr, "\nAu revoir!\n");
	        break;		// if q, quit
	    }
    
    }

    delete test_synch_console;
    delete readAvail;
    delete writeDone;

}

