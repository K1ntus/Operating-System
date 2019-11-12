#ifdef CHANGED
#ifndef USERTHREAD_H
#define USERTHREAD_H

#include "copyright.h"
#include "utility.h"
#include "machine.h"
#include "translate.h"
#include "thread.h"
#include "list.h"
#include "synch.h"

static List *semaphore_user_list = new List();
typedef int sem_t;
class UserThread : dontcopythis
{
public:
    static int Start(void f(void *arg), void *arg);

    static void Exit(void);

    static int do_ThreadCreate(int f, int arg);

    static void StartUserThread(void *schmurtz);

    static int do_ThreadExit();

    static void UserSemaphore_V(int id);
    static void UserSemaphore_P(int id);
    static void do_SemaphoreInit(sem_t sem_id, int initial_value);

private:
    static Semaphore *getSemaphoreFromElement(ListElement *elem)
    {
        Semaphore *res = ((Semaphore *)elem->item);

        return res;
    }

    static ListElement *isElementPresent(int id)
    {
        if (semaphore_user_list->IsEmpty())
        {
            ListElement *res = new ListElement(new Semaphore("martine decouvre les semaphores", 5), (int)id);
            semaphore_user_list->Append(res);
            return res;
        }

        ListElement *itemList = semaphore_user_list->FirstElement();
        for (int i = 0; i < semaphore_user_list->Length(); i++)
        {
            if (itemList != 0x0)
            {

                if (itemList->key == id)
                {
                    return itemList;
                }
            }
            itemList = itemList->next;
        }

        ListElement *res = new ListElement(new Semaphore("martine decouvre la galere", 5), (int)id);
        semaphore_user_list->Append(res);
        return res;
        // return NULL;
    }
};

#endif // USERTHREAD_H
#endif // CHANGED