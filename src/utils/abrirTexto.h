#ifndef ABRIRTEXTO_h
#define ABRIRTEXTO_H

#include <stdio.h>
#include "dados.h"
#include "pagina.h"
#include "ram.h"
#include "tlb.h"

void guardar(FILE *arq, dados *acessoAtual,tlb *emUso, ram *usada);

void *buscaTLB(void *ptr);

int verificarTLB(tlb *emUso, dados *acessoAtual);

void localizarEnderecos(FILE *arquivo, dados *acessoAtual, pagina *tabela, ram *usada, FILE *arqt, tlb *emUso);

#endif