#ifndef RAM_H
#define RAM_H
#define RAMSIZE 128
#define RAMLENGHT 256

typedef struct ram{
    signed char **RAM;
    signed char proxFrame;
    int pageFault;
    int reverse[RAMSIZE];
    int ocupados;
    int lastUsed[RAMSIZE];
    int timeGoing;
}ram;

#endif