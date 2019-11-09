#ifdef CHANGED
#include "copyright.h"
#include "system.h"
#include "userthread.h"



int UserThread::do_ThreadCreate(int f, int arg) {
    Thread* newThread = new Thread("test_thread");
    
    // int *address_exit = &(f) + sizeof(int);
    
    int * adress_pack = (int *) malloc(sizeof(int) * 3);
    adress_pack[0] = f;
    adress_pack[1] = arg;
    adress_pack[2] = machine->ReadRegister(7);  //ARG4

    newThread->Start(UserThread::StartUserThread, (void*)adress_pack);

    return currentThread->space->thread_id;
}

void UserThread::StartUserThread(void * schmurtz) {
    ASSERT(schmurtz);
	
    // fprintf(stderr, "toto_init thread\n");
    int * array = (int*) schmurtz;

    int function_adress = (int) array[0];
    int arg_adress = (int) array[1];
    int exit_address = (int) array[2];

    // fprintf(stderr, "Created a thread with arguments: %d && %d\n", function_adress, arg_adress);

    DEBUG('x', "Function: %d\n", function_adress);
    

    // AddrSpace::InitRegisters ();	// set the initial register values
    int i;

    for (i = 0; i < NumTotalRegs; i++)
    	machine->WriteRegister (i, 0);

    // Initial program counter -- must be location of "Start"
    machine->WriteRegister (PCReg, function_adress);

    // Need to also tell MIPS where next instruction is, because
    // of branch delay possibility
    machine->WriteRegister (NextPCReg, machine->ReadRegister(PCReg) + 4);

    // ARGUMENT
    // machine->WriteRegister (2, function_adress);
    machine->WriteRegister (4, arg_adress);

    // Set the stack register to the end of the address space, where we
    // allocated the stack; but subtract off a bit, to make sure we don't
    // accidentally reference off the end!
    int space = currentThread->space->AllocateUserStack();

    if(space == -1){
        fprintf(stderr, "Not enought space to alloc the thread %d\n", currentThread->space->thread_id);
        return;
    }

    int offset = currentThread->space->NumPages() * PageSize - StackSizeToNotTouch;
    machine->WriteRegister (StackReg, offset - space);
    // printf("StackReg = %d\n", machine->ReadRegister(StackReg));
    DEBUG ('a', "Initializing stack register to 0x%x\n",
	   machine->ReadRegister(StackReg));
    
    machine->WriteRegister(RetAddrReg, exit_address);
	
    machine->Run();
    free(array);
}



int UserThread::do_ThreadExit() {
    fprintf(stderr, "\nExiting thread %d.\n", currentThread->space->thread_id);
    int offset = currentThread->space->NumPages() * PageSize - StackSizeToNotTouch;
    // printf("Offset=%d\n",offset);
    currentThread->space->FreeUserStack(offset - machine->ReadRegister(StackReg));

    if(currentThread->space->thread_id != 0){
        currentThread->Finish();
        return 1;
    } else {
        interrupt->Halt();
        return 0;
    }
    
}

#endif