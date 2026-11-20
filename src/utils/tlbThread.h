#ifndef TLBTHREAD_H
#define TLBTHREAD_H
#include "tlb.h"

typedef struct tlbThread{
    tlb *ptr;
    int acess;
    int indicador;
    int pagBusc;
    int achou;
}tlbThread;

#endif