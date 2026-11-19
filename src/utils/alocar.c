#include <stdio.h>
#include <stdlib.h>
#include "ram.h"
#include "pagina.h"

void alocarMemoria(ram **usada){
    
    (*usada)->RAM=malloc(sizeof(signed char*)*256);
    if((*usada)->RAM==NULL){
        printf("RAM é nulo");
    }
    for(int i=0;i<256;i++){
        (*usada)->RAM[i]=malloc(sizeof(signed char)*256);
    }
    (*usada)->proxFrame=0;
    
}

void alocarPaginas(pagina **atual){
    (*atual)=malloc(sizeof(pagina)*256);
    if(*atual==NULL){
        printf("aqui");
        exit(1);
    }
    for(int i=0;i<256;i++){   
            (*atual)[i].informacao=-1;
    }
}