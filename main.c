#include <stdio.h>
#include <stdlib.h>
#include "src/dados.h"
#include "src/pagina.h"
#include "src/abrirTexto.h"

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
            printf("%d",atual[i].informacao);       
            //localizarEnderecos(arq2,&x);
            i++;
        }
    }
    fclose(arq);
    fclose(arq2);



    return 0;
}