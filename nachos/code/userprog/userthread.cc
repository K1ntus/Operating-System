#ifdef CHANGED
#include "copyright.h"
#include "system.h"
#include "userthread.h"

int UserThread::do_ThreadCreate(int f, int arg) {
    Thread* newThread = new Thread("test_thread");

    int * adress_pack = (int *) malloc(sizeof(int) * 2);
    adress_pack[0] = f;
    adress_pack[1] = arg;
    newThread->Start(UserThread::StartUserThread, (void*)adress_pack);
    // space->RestoreState ();	// load page table register

    //machine->DumpMem ("memory.svg");
    // machine->Run ();	// jump to the user progam
    // ASSERT (FALSE);		// machine->Run never returns;
    


    return -1;
}

void UserThread::StartUserThread(void * schmurtz) {
    ASSERT(schmurtz);
	
    fprintf(stderr, "toto_init thread\n");
    int * array = (int*) schmurtz;

    int function_adress = (int) array[0];
    int arg_adress = (int) array[1];

    fprintf(stderr, "Created a thread with arguments: %d && %d\n", function_adress, arg_adress);

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
    machine->WriteRegister (StackReg, currentThread->space->NumPages() * PageSize - 16 - currentThread->space->AllocateUserStack());
    DEBUG ('a', "Initializing stack register to 0x%x\n",
	   currentThread->space->NumPages() * PageSize - 16);
    

	
    machine->Run();
    free(array);
}



int UserThread::do_ThreadExit() {
    machine->WriteRegister(StackReg, currentThread->space->NumPages() * PageSize -16 - 256);


    currentThread->Finish();
    return 1;
    // Thread* newThread = new Thread("test_thread");

    // int * adress_pack = (int *) malloc(sizeof(int) * 2);
    // adress_pack[0] = f;
    // adress_pack[1] = arg;
    // newThread->Start(UserThread::StartUserThread, (void*)adress_pack);
    // space->RestoreState ();	// load page table register

    //machine->DumpMem ("memory.svg");
    // machine->Run ();	// jump to the user progam
    // ASSERT (FALSE);		// machine->Run never returns;
    


    // return -1;
}
/*
void UserThread::Exit(void) {

}

int UserThread::Start(void f(void *arg), void *arg) {
    int res = -1;

    // res = do_ThreadCreate(*f, *arg);
    return res;
}*/


#endif