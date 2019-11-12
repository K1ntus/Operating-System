#ifdef CHANGED
#include "copyright.h"
#include "system.h"
#include "userthread.h"




int UserThread::do_ThreadCreate(int f, int arg) {
    Thread* newThread = new Thread("user_thread");
    
    
    int * adress_pack = (int *) malloc(sizeof(int) * 4);
    adress_pack[0] = f;
    adress_pack[1] = arg;
    adress_pack[2] = machine->ReadRegister(7);  //ARG4
    adress_pack[3] = -1;
    currentThread->space->thread_id++;

    newThread->Start(UserThread::StartUserThread, (void*)adress_pack);

    return 1;
}

void UserThread::StartUserThread(void * schmurtz) {
    ASSERT(schmurtz);
	
    int * array = (int*) schmurtz;

    int function_adress = (int) array[0];
    int arg_adress = (int) array[1];
    int exit_address = (int) array[2];
    // free(schmurtz);

    DEBUG('x', "Function: %d\n", function_adress);
    

    // Init the registers
    int i;

    for (i = 0; i < NumTotalRegs; i++)
    	machine->WriteRegister (i, 0);

    // Initial program counter -- must be location of "Start"
    machine->WriteRegister (PCReg, function_adress);

    // Need to also tell MIPS where next instruction is, because
    // of branch delay possibility
    machine->WriteRegister (NextPCReg, machine->ReadRegister(PCReg) + 4);

    // ARGUMENT
    machine->WriteRegister (4, arg_adress);

    // Set the stack register to the end of the address space, where we
    // allocated the stack; but subtract off a bit, to make sure we don't
    // accidentally reference off the end and put it on a free space
    // of a range of 256 bytes
    int space = currentThread->space->AllocateUserStack();

    if(space == -1){
        DEBUG('t', "Not enought space to alloc the thread %d\n", currentThread->space->thread_id);
        currentThread->space->thread_id--;
        currentThread->Finish();
        return;
    }

    int offset = currentThread->space->NumPages() * PageSize - StackSizeToNotTouch;
    machine->WriteRegister (StackReg, offset - space); 
    
    DEBUG ('t', "Initializing stack register to 0x%x\n",
	   machine->ReadRegister(StackReg));
    
    machine->WriteRegister(RetAddrReg, exit_address);   //To allow auto-exit when the thread as reach the end 
	
    machine->Run();
}



int UserThread::do_ThreadExit() {
        DEBUG('t', "\nExiting thread %d.\n", currentThread->space->thread_id);
    int offset = currentThread->space->NumPages() * PageSize - StackSizeToNotTouch;
    
    currentThread->space->FreeUserStack(offset - machine->ReadRegister(StackReg));

    if(currentThread->space->GetFreeSpace() == UserStacksAreaSize && currentThread->space->thread_id  == 0) {
        interrupt->Halt();
        return 0;
    } else {
        currentThread->Finish();
        return 1;
    }
    
}


void UserThread::do_SemaphoreInit(sem_t sem_id, int initial_value){
                // ListElement* res = new ListElement(new Semaphore("martine decouvre les semaphores", initial_value), (long long) sem_id);
    semaphore_user_list->Prepend(new ListElement(new Semaphore("martine decouvre les semaphores", initial_value), (long long) sem_id));
    // ListElement * elem = new ListElement(new Semaphore("sem name", initial_value), sem_id);
    // printf("Added a semaphore. Name:%s. ID:%d. Init:%d.\n", ((Semaphore*) elem)->getName(),sem_id, initial_value);
    // semaphore_user_list->Prepend(elem);
}

void UserThread::UserSemaphore_V(int sem) {
    ListElement * semaphore = isElementPresent(sem);
    printf("V, ");
    getSemaphoreFromElement(semaphore)->V();
    // if(sem != 0x0)
    //     sem->V();
}


void UserThread::UserSemaphore_P(int sem) {
    ListElement * semaphore = isElementPresent(sem);
    printf("P, ");
    getSemaphoreFromElement(semaphore)->P();
    // if(sem != 0x0)
    //     sem->V();
}

#endif  //CHANGED