#ifndef ALOCAR_H
#define ALOCAR_H

#include "ram.h"
#include "pagina.h"
#include "tlb.h"

void alocarMemoria(ram **usada);

void alocarPaginas(pagina **atual, int modo);

void alocarTLB(tlb *emUso, int modo);

#endif