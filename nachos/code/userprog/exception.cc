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
#include "userthread.h"


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
#define DEFAULT_RETURN_VALUE 0

void ExceptionHandler (ExceptionType which) {
    int type = machine->ReadRegister (CALL_CODE);


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
						interrupt->Halt();	//Already making Exit(0)
						break;
					}

					#ifdef CHANGED
					case SC_Exit:
					{
						DEBUG ('s', "Shutdown, initiated by user program.\n");
						int value = machine->ReadRegister(CALL_ARG1);
						Exit(value);
						break;
					}


					case SC_PutChar:
					{
						DEBUG ('s', "Putchar, initiated by user program.\n");
						synchconsole->SynchPutChar(machine->ReadRegister(CALL_ARG1));
						machine->WriteRegister(CALL_CODE, DEFAULT_RETURN_VALUE);
						break;
					}


					case SC_GetChar:
					{
						DEBUG ('s', "GetChar, initiated by user program.\n");
						machine->WriteRegister(CALL_CODE, (int) synchconsole->SynchGetChar());
						break;
					}


					case SC_PutInt:
					{
						DEBUG ('s', "PutInt, initiated by user program.\n");
						int value = machine->ReadRegister(CALL_ARG1);
						synchconsole->PutInt(value);
						machine->WriteRegister(CALL_CODE, DEFAULT_RETURN_VALUE);
						break;
					}


					case SC_GetInt:
					{
						DEBUG ('s', "GetInt, initiated by user program.\n");
						int value = -1;
						int address = machine->ReadRegister(CALL_ARG1);
						synchconsole->GetInt(&value);
						machine->WriteMem(address, sizeof(int), (int) value);
						machine->WriteRegister(CALL_CODE, value);
						break;
					}


					case SC_PutString:
					{
						DEBUG ('s', "PutString, initiated by user program.\n");
						int address = machine->ReadRegister(CALL_ARG1);
						int nb_char_copied = -1;
						int offset = 0;

						char* buffer = (char *) malloc(sizeof(char) * MAX_STRING_SIZE);
    					ASSERT(buffer != 0x0);  

						while(nb_char_copied != 0) {
							nb_char_copied = synchconsole->copyStringFromMachine(address + offset, buffer, MAX_STRING_SIZE);
							synchconsole->SynchPutString(buffer);


							//FIX THE OFFSET
							if(MAX_STRING_SIZE == nb_char_copied){
								nb_char_copied -=1;	
							}

							//EOSTRING or EOF
							if(buffer[nb_char_copied] == '\0' && nb_char_copied < MAX_STRING_SIZE-1){
								break;	
							} else if(buffer[nb_char_copied] == EOF){
								break;	
							}

							offset += nb_char_copied;
						}

						free(buffer);
						machine->WriteRegister(CALL_CODE, DEFAULT_RETURN_VALUE);						
						break;
					}


					case SC_GetString:
					{
						DEBUG ('s', "GetString, initiated by user program.\n");

						int address = machine->ReadRegister(CALL_ARG1);
						int size = machine->ReadRegister(CALL_ARG2);
<<<<<<< HEAD
						ASSERT(size > 0);
						int offset = 0;
						
						char * buffer = (char *) malloc(size * sizeof(char));
						ASSERT(buffer != 0x0);
						
						while(offset < size) {
							synchconsole->SynchGetString(buffer, size);
							offset += synchconsole->copyStringToMachine(address, buffer, MAX_STRING_SIZE);
=======
						int init_size = size;
						ASSERT(size > 0);
						int offset = 0;

						int nb_char_written = 0;

						while(size > 0 && size <= init_size) {
						char * buffer = (char *) malloc(size * sizeof(char));
    					ASSERT(buffer != 0x0);  

							synchconsole->SynchGetString(buffer, size);
					
							size = synchconsole->copyStringToMachine(address+offset, buffer, MAX_STRING_SIZE);
							offset += size;
							if(buffer[size] == '\n' || buffer[size] == '\0') {
								break;
							}

							free(buffer);
>>>>>>> get_string
						}

						free(buffer);

						machine->WriteRegister(CALL_CODE, offset);
						break;
					}


					case SC_ThreadCreate:
					{
						DEBUG ('s', "ThreadCreate, initiated by user program.\n");
						int return_value = -1;

						int function_adress = machine->ReadRegister(CALL_ARG1);
						int args_adress = machine->ReadRegister(CALL_ARG2);

						return_value = UserThread::do_ThreadCreate(function_adress, args_adress);
						break;
					}
					case SC_ThreadExit:
					{
						DEBUG ('s', "ThreadExit, initiated by user program.\n");
						int return_value = -1;
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
