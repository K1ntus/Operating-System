
// PageProvider.h
//      Data structures to keep track of executing user programs
//      (address spaces).
//
//      For now, we don't keep any information about address spaces.
//      The user level CPU state is saved and restored in the thread
//      executing the user program (see thread.h).
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#ifndef PAGEPROVIDER_H
#define PAGEPROVIDER_H

#include "bitmap.h"
#include "translate.h"


class PageProvider : dontcopythis
{
    public:
        PageProvider(unsigned long size);
        ~PageProvider();
        int getEmptyPage();
        void ReleasePage(int page_pos);
        size_t NumAvailPage();
    
    private:
        BitMap * pageMap;
        
};
#endif  //PAGEPROVIDER_H