#ifndef TLB_H
#define TLB_H
#define TLBSIZE 16
#include "pagina.h"

typedef struct tlb{
    int informacao[TLBSIZE];
    int frame[TLBSIZE];
    int proxEnt;
    int tlbMiss;
    int lastUsed[TLBSIZE];
    int timeGoing;
    int modo;
}tlb;

#endif