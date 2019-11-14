
#include "pageprovider.h"

TranslationEntry PageProvider::getEmptyPage() {


    return 0x0;
}


void PageProvider::ReleasePage(TranslationEntry * page) {

}


size_t PageProvider::NumAvailPage() {

    return 0;
}