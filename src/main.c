#include <stdio.h>
#include <stdlib.h>
#include "utils/dados.h"
#include "utils/pagina.h"
#include "utils/abrirTexto.h"
#include "utils/ram.h"
#include "utils/tlb.h"
#include "utils/alocar.h"


int main(){
    FILE *arqt;
    arqt=fopen("correct.txt","w");
    int modo=2; //página, 1= fifo, 2 = lru
    int modoTLB=1; //TLB 1=fifo, 2= lru
    dados x;
    x.totalEnderecos=0;
    pagina *atual=NULL;
    alocarPaginas(&atual, modo);
    
    tlb emUso;
    alocarTLB(&emUso, modoTLB);

    ram *usada;
    usada = malloc(sizeof(ram));
    alocarMemoria(&usada);

    FILE *arq,*arq2;
    
    arq=fopen("addresses.txt","r");
    arq2 = fopen("BACKING_STORE.bin","rb");
    
    if(arq==NULL){
        fprintf(stderr, "Não foi possível abrir adresses.txt\n");
    }
    if(arq2==NULL){
        fprintf(stderr,"Não foi possível abrir BACKING_STORE.bin\n");
    }
    if(arqt==NULL){
        fprintf(stderr,"Não foi possível abrir correct.txt\n");
    }

    if(arq2!=NULL && arq!=NULL && arqt!=NULL){
        while(fscanf(arq,"%d",&x.enderecoBruto)!=EOF){
            x.enderecoBruto=x.enderecoBruto & 0xFFFF;
            x.pagina= (x.enderecoBruto>>8) & 0xFF;
            x.offset = x.enderecoBruto & 0xFF;   
            x.totalEnderecos++;  
            localizarEnderecos(arq2,&x,atual,usada, arqt, &emUso);
        }
        guardar(arqt,&x,&emUso,usada);
    }
    if(arq!=NULL)
        fclose(arq);
    if(arq2!=NULL)
        fclose(arq2);
    if(arqt!=NULL)
        fclose(arqt);

    for(int i=0;i<128;i++){
        free(usada->RAM[i]);
    }
    free(usada->RAM);
    free(usada);
    free(atual);


    return 0;
}