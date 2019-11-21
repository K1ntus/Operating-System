
#include "pageprovider.h"
#include "system.h"


PageProvider::~PageProvider() {
    delete pageMap;
    
}

//Singleton
PageProvider::PageProvider(unsigned long size) {
    pageMap = new BitMap(size);
    ASSERT(pageMap);
    
}


int PageProvider::getEmptyPage() {
    //Semaphore
    int page_pos = pageMap->Find();
    ASSERT(page_pos != -1);

    void* address = memset(machine->mainMemory + (page_pos*PageSize), 0, PageSize);
    ASSERT(address != 0x0);

    pageMap->Mark(page_pos);

    return page_pos;
}


void PageProvider::ReleasePage(int page_pos) {
    if(!pageMap->Test(page_pos)) {
        return;
    }

    memset(machine->mainMemory + (page_pos*PageSize), 0, PageSize);

    pageMap->Clear(page_pos);
}


size_t PageProvider::NumAvailPage() {
    return pageMap->NumClear();
}