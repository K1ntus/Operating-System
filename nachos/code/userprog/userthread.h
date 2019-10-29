#ifdef CHANGED
#ifndef USERTHREAD_H
#define USERTHREAD_H

#include "copyright.h"
#include "utility.h"
#include "machine.h"
#include "translate.h"
#include "thread.h"

class UserThread : dontcopythis
{
public:
    static int Start(void f(void *arg), void *arg);

    static void Exit(void);

    static int do_ThreadCreate(int f, int arg);

    static void StartUserThread(void *schmurtz);

    static int do_ThreadExit();
    
private:
};

#endif // USERTHREAD_H
#endif // CHANGED