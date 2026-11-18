#include <stdio.h>
#include <stdlib.h>
#include "functions/dados.h"
#include "functions/pagina.h"
#include "functions/abrirTexto.h"

int main(){
    
    dados x;
    pagina **atual;
    atual=malloc(sizeof(pagina)*128);
    if(atual!=NULL){
        for(int i=0;i<128;i++){
            atual[i]=malloc(sizeof(pagina)*128);
            if(atual[i]==NULL){
                exit(1);
            }
        }
    }

    for(int i=0;i<128;i++){
        for(int g=0;g<128;g++){
            atual[i][g].informacao=-1;
        }
    }



    FILE *arq,*arq2;
    
    arq=fopen("addresses.txt","r");
    arq2 = fopen("BACKING_STORE.bin","rb");
    int i=0;
    int g=-1;
    if(arq2!=NULL && arq!=NULL){
        while(fscanf(arq,"%d",&x.enderecoBruto)!=EOF){
            x.enderecoBruto=x.enderecoBruto & 0xFFFF;
            x.pagina= (x.enderecoBruto>>8) & 0xFF;
            x.offset = x.enderecoBruto & 0xFF;
            printf("%d",atual[i][g++].informacao);       
            //localizarEnderecos(arq2,&x);
            i++;
        }
    }
    fclose(arq);
    fclose(arq2);



    return 0;
}