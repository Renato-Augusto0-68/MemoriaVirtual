#ifndef ALOCAR_H
#define ALOCAR_H

#include "ram.h"
#include "pagina.h"
#include "tlb.h"

int alocarMemoria(ram **usada);

int alocarPaginas(pagina **atual, int modo);

void alocarTLB(tlb *emUso, int modo);

#endif