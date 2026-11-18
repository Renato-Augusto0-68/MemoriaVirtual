#include <stdio.h>
#include <stdlib.h>
#include "functions/dados.h"
#include "functions/abrirTexto.h"

int main(){
    
    dados x;
    

    FILE *arq,*arq2;
    
    arq=fopen("addresses.txt","r");
    arq2 = fopen("BACKING_STORE.bin","r");
    if(arq!=NULL){
        while(fscanf(arq,"%d",&x.enderecoBruto)!=EOF){
            x.pagina= x.enderecoBruto/256;
            x.offset = x.enderecoBruto%256;
            
        
        }
        fclose(arq);
    }



    return 0;
}