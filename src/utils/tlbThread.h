#ifndef TLBTHREAD_H
#define TLBTHREAD_H

typedef struct tlbThread{
    int pagina;
    int frame;
    int proxEnt;
    int tlbMiss;
    int lastUsed;
    int timeGoing;
    int modo;
    int tlbHit;
}tlbThread;

#endif