// exception.cc 
//      Entry point into the Nachos kernel from user programs.
//      There are two kinds of things that can cause control to
//      transfer back to here from user code:
//
//      syscall -- The user code explicitly requests to call a procedure
//      in the Nachos kernel.  Right now, the only function we support is
//      "Halt".
//
//      exceptions -- The user code does something that the CPU can't handle.
//      For instance, accessing memory that doesn't exist, arithmetic errors,
//      etc.  
//
//      Interrupts (which can also cause control to transfer from user
//      code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h"

// #if 1
// #include <unistd.h>
// #endif
//----------------------------------------------------------------------
// UpdatePC : Increments the Program Counter register in order to resume
// the user program immediately after the "syscall" instruction.
//----------------------------------------------------------------------
static void UpdatePC () {
    int pc = machine->ReadRegister (PCReg);
    machine->WriteRegister (PrevPCReg, pc);
    pc = machine->ReadRegister (NextPCReg);
    machine->WriteRegister (PCReg, pc);
    pc += 4;
    machine->WriteRegister (NextPCReg, pc);
}


//----------------------------------------------------------------------
// ExceptionHandler
//      Entry point into the Nachos kernel.  Called when a user program
//      is executing, and either does a syscall, or generates an addressing
//      or arithmetic exception.
//
//      For system calls, the following is the calling convention:
//
//      system call code -- r2
//              arg1 -- r4
//              arg2 -- r5
//              arg3 -- r6
//              arg4 -- r7
//
//      The result of the system call, if any, must be put back into r2. 
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//      "which" is the kind of exception.  The list of possible exceptions 
//      are in machine.h.
//----------------------------------------------------------------------
#define CALL_CODE 2
#define CALL_ARG1 4
#define CALL_ARG2 5
#define CALL_ARG3 6
#define CALL_ARG4 7

void ExceptionHandler (ExceptionType which) {
    int type = machine->ReadRegister (2);


//	FLAGS:
//      '+' -- turn on all debug messages
//      't' -- thread system
//      's' -- semaphores, locks, and conditions
//      'i' -- interrupt emulation
//      'm' -- machine emulation (USER_PROGRAM)
//      'd' -- disk emulation (FILESYS)
//      'f' -- file system (FILESYS)
//      'a' -- address spaces (USER_PROGRAM)
//      'n' -- network emulation (NETWORK)
//

    switch (which) {
		case SyscallException:
			{
				switch (type) {
					case SC_Halt:
					{
						DEBUG ('s', "Shutdown, initiated by user program.\n");
						interrupt->Halt();
						break;
					}


					#ifdef CHANGED
					case SC_PutChar:
					{
						DEBUG ('s', "Putchar, initiated by user program.\n");
						synchconsole->SynchPutChar(machine->ReadRegister(CALL_ARG1));
						break;
					}
					case SC_GetChar:
					{
						DEBUG ('s', "GetChar, initiated by user program.\n");
						machine->WriteRegister(CALL_CODE, (int) synchconsole->SynchGetChar());

						//If char == EOF, alors interrupt-<Halt() ?
						break;
					}


					case SC_PutInt:
					{
						DEBUG ('s', "PutInt, initiated by user program.\n");
						synchconsole->PutInt(machine->ReadRegister(CALL_ARG1));
						break;
					}
					case SC_GetInt:
					{
						DEBUG ('s', "GetInt, initiated by user program.\n");

						int address = machine->ReadRegister(CALL_ARG1);

						synchconsole->GetInt(&address);

						//machine->WriteRegister(CALL_CODE, address);

        				//machine->WriteMem(to + number_character_read, 1, from[number_character_read]);   //ReadMem is already taking care of the Translation (virt <-> phys memory)


						break;
					}


					case SC_PutString:
					{
						DEBUG ('s', "PutString, initiated by user program.\n");
						char buffer[MAX_STRING_SIZE];
						int address = machine->ReadRegister(CALL_ARG1);


						int nb_char_copied = -1;
						int offset = 0;
						//int SynchConsole::copyStringFromMachine(int from, char *to, unsigned size);

						while(nb_char_copied != 0) {
							nb_char_copied = synchconsole->copyStringFromMachine(address + offset*MAX_STRING_SIZE, buffer, MAX_STRING_SIZE);

							//fprintf(stderr, "\n\nSYSCALL@SC_PUTSTRING: Number Character Copied = %d\n\n", nb_char_copied);
							// fprintf(stderr, "SYSCALL@SC_PUTSTRING: String=%s\n\n", buffer);
							// usleep(500);
							synchconsole->SynchPutString(buffer);

							if(buffer[nb_char_copied] == '\0'){
								break;
							}

							offset += 1;
						}
						break;
					}
					case SC_GetString:
					{
						DEBUG ('s', "GetString, initiated by user program.\n");
						char buffer[MAX_STRING_SIZE];

						int address = machine->ReadRegister(CALL_ARG1);	// Get the first argument (ie. the address) 
						int size = machine->ReadRegister(CALL_ARG2);	// Get the second argument (ie. the size) 

						//TO TEST

						//int copyStringToMachine(int to, char *from, unsigned size);
						synchconsole->SynchGetString(buffer, size);


						fprintf(stderr, "GETSTRING SYSCALL = %s\n", buffer);
						synchconsole->copyStringToMachine(address, buffer, size);

						break;
					}
					#endif	//CHANGED

					default:
					{
						printf("Unimplemented system call %d\n", type);
						ASSERT(FALSE);
					}
				}

				// Do not forget to increment the pc before returning!
				UpdatePC ();
				break;
		}

		case PageFaultException:
			if (!type) {
				printf("NULL dereference at PC %x!\n", machine->registers[PCReg]);
				ASSERT (FALSE);
			} else {
				printf ("Page Fault at address %x at PC %x\n", type, machine->registers[PCReg]);
				ASSERT (FALSE);	// For now
			}
			break;

		default:
			printf ("Unexpected user mode exception %d %d at PC %x\n", which, type, machine->registers[PCReg]);
			ASSERT (FALSE);
    }
}
