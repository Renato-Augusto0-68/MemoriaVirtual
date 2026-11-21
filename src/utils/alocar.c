#include <stdio.h>
#include <stdlib.h>
#include "ram.h"
#include "pagina.h"
#include "tlb.h"

int alocarMemoria(ram **usada){
    
    (*usada)->RAM=malloc(sizeof(signed char*)*128);
    if((*usada)->RAM==NULL){
        fprintf(stderr,"Não foi possível alocar memória para RAM ");
        return 1;
    }
    for(int i=0;i<128;i++){
        (*usada)->RAM[i]=malloc(sizeof(signed char)*256);
        if((*usada)->RAM[i]==NULL){
            fprintf(stderr,"Não foi possível alocar memória para os subnós de RAM ");
            return 1;
        }
        (*usada)->reverse[i]=-1;
        (*usada)->lastUsed[i]=0;
    }
    (*usada)->proxFrame=0;
    (*usada)->pageFault=0;
    (*usada)->ocupados=0;
    (*usada)->timeGoing=0;    
    return 0;
}

int alocarPaginas(pagina **atual, int modo){
    (*atual)=malloc(sizeof(pagina)*256);
    if(*atual==NULL){
       fprintf(stderr,"Não foi possível alocar memória para a tabela de paginas\n");
        return 1;
    }
    (*atual)->modo=modo;
    
    for(int i=0;i<256;i++){   
            (*atual)[i].informacao=-1;
    }
    return 0;
}

void alocarTLB(tlb *emUso, int modo){
    for(int i=0;i<16;i++){
        emUso->pagina[i]=-1;
        emUso->frame[i]=-1;
        emUso->lastUsed[i]=0;
    }
    emUso->modo=modo;
    emUso->proxEnt=0;
    emUso->timeGoing=0;
    emUso->tlbMiss=0;
}