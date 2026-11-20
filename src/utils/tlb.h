#ifndef TLB_H
#define TLB_H
#define TLBSIZE 16
#include "pagina.h"

typedef struct tlb{
    int pagina[TLBSIZE];
    int frame[TLBSIZE];
    int proxEnt;
    int tlbMiss;
    int lastUsed[TLBSIZE];
    int timeGoing;
    int modo;
    int tlbHit;
}tlb;

#endif