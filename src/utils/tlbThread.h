#ifndef TLBTHREAD_H
#define TLBTHREAD_H
#include "tlb.h"

typedef struct tlbThread{
    tlb *ptr;
    int indicador;
    int pagBusc;
    int achou;
}tlbThread;

#endif