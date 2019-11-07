#ifdef CHANGED
#include "copyright.h"
#include "system.h"
#include "userthread.h"



int UserThread::do_ThreadCreate(int f, int arg) {
    Thread* newThread = new Thread("test_thread");

    // thread_id += 1;//Protéger accès
    fprintf(stderr, "\nCreating thread %d.\n", currentThread->space->thread_id);

    int * adress_pack = (int *) malloc(sizeof(int) * 2);
    adress_pack[0] = f;
    adress_pack[1] = arg;

    newThread->Start(UserThread::StartUserThread, (void*)adress_pack);

    return currentThread->space->thread_id;
}

void UserThread::StartUserThread(void * schmurtz) {
    ASSERT(schmurtz);
	
    // fprintf(stderr, "toto_init thread\n");
    int * array = (int*) schmurtz;

    int function_adress = (int) array[0];
    int arg_adress = (int) array[1];

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

    machine->WriteRegister (StackReg, currentThread->space->NumPages() * PageSize - space);
    DEBUG ('a', "Initializing stack register to 0x%x\n",
	   currentThread->space->NumPages() * PageSize - 16);
    

	
    machine->Run();
    free(array);
}



int UserThread::do_ThreadExit() {
    fprintf(stderr, "\nExiting thread %d.\n", currentThread->space->thread_id);
    
    currentThread->space->FreeUserStack(machine->ReadRegister(StackReg) - currentThread->space->NumPages() * PageSize);
    // thread_id -= 1;//Protéger accès

    if(currentThread->space->thread_id != 0){
        currentThread->Finish();
        return 1;
    } else {
        interrupt->Halt();
        return 0;
    }
    
}

#endif