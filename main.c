#include <stdio.h>
#include <stdlib.h>
#include "functions/dados.h"
#include "functions/abrirTexto.h"

int main(){
    printf("Hello world");
    dados x;
    

    FILE *arq;
    
    arq=fopen("addresses.txt","r");
    if(arq!=NULL){
        while(scanf("%d",&x.byteBruto)!=EOF){
            x.pagina= x.byteBruto/256;
            x.offset = x.byteBruto%256;

        }
    }



    return 0;
}