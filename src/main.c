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
    (atual)=malloc(sizeof(pagina)*256);
    alocarPaginas(&atual);
    
    ram *usada;
    usada = malloc(sizeof(ram));
    alocarMemoria(&usada);
    FILE *arq,*arq2;
    
    arq=fopen("addresses.txt","r");
    arq2 = fopen("BACKING_STORE.bin","rb");
    if(arq==NULL){
        printf("arq é nulo");
        exit(1);
    }
    if(arq2==NULL){
        printf("arq2 é nulo");
        exit(1);
    }

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