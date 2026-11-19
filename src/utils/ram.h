#ifndef RAM_H
#define RAM_H
#define RAMSIZE 128
#define RAMLENGHT 256

typedef struct ram{
    signed char **RAM;
    signed char proxFrame;
    int pageFault;
    signed char reverse[RAMSIZE][RAMLENGHT];

}ram;

#endif