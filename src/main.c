#include <stdio.h>
#include <stdlib.h>
#include "utils/dados.h"
#include "utils/pagina.h"
#include "utils/abrirTexto.h"
#include "utils/ram.h"
#include "utils/alocar.h"


int main(){
    
    dados x;
    pagina *atual;
    atual=malloc(sizeof(pagina)*256);
    if(atual==NULL){
        exit(1);
    }
    for(int i=0;i<256;i++){   
            atual[i].informacao=-1;
    }
    ram *usada;
    usada->RAM=malloc(sizeof(signed char*)*256);
    for(int i=0;i<256;i++){
        usada->RAM[i]=malloc(sizeof(signed char)*256);
    }
    usada->proxFrame=0;

    FILE *arq,*arq2;
    
    arq=fopen("addresses.txt","r");
    arq2 = fopen("BACKING_STORE.bin","rb");
    if(arq2!=NULL && arq!=NULL){
        while(fscanf(arq,"%d",&x.enderecoBruto)!=EOF){
            x.enderecoBruto=x.enderecoBruto & 0xFFFF;
            x.pagina= (x.enderecoBruto>>8) & 0xFF;
            x.offset = x.enderecoBruto & 0xFF;     
            localizarEnderecos(arq2,&x,atual,usada);
        }
    }
    fclose(arq);
    fclose(arq2);



    return 0;
}