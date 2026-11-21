#include <stdio.h>
#include <stdlib.h>
#include "utils/dados.h"
#include "utils/pagina.h"
#include "utils/abrirTexto.h"
#include "utils/ram.h"
#include "utils/tlb.h"
#include "utils/alocar.h"
#include <string.h>

int main(int argc, char *argv[]){
    if(argc!=4){
        fprintf(stderr,"Erro, argumentos insuficientes para exceutar\n");
        exit(1);
    }
    if(strcmp(argv[1],"address.txt")!=0){
        fprintf(stderr,"Erro, arquivo address.txt passado incorretamente ou ausente\n");
        exit(1);
    }    
    if(strcmp(argv[2],"lru")!=0 && strcmp(argv[2],"fifo")!=0){
        fprintf(stderr,"Erro, modo de substituição da página inexistente\n");
        exit(1);
    } 
    if(strcmp(argv[3],"lru")!=0 && strcmp(argv[3],"fifo")!=0){
        fprintf(stderr,"Erro, modo de substituição do TLB inexistente\n");
        exit(1);
    } 
    int erro=0;
    int modo=0;
    int modoTLB=0;
    if(strcmp(argv[2],"lru")==0){
        modo=2;     //página, 1= fifo, 2 = lru
    }else{
        modo=1;
    } 
    if(strcmp(argv[3],"lru")==0){
        modoTLB=2; //TLB 1=fifo, 2= lru
    }else{
        modoTLB=1;
    }    
    
    dados x;
    x.totalEnderecos=0;
    pagina *atual=NULL;
    if(alocarPaginas(&atual, modo)==1)
        erro=1;
    tlb emUso;
    alocarTLB(&emUso, modoTLB);

    ram *usada=NULL;
    usada = malloc(sizeof(ram));
    if(alocarMemoria(&usada)==1){
        erro=1;
    }
    FILE *arq,*arq2;
    FILE *arqt;
    arqt=fopen("correct.txt","w");
    arq=fopen("addresses.txt","r");
    arq2=fopen("BACKING_STORE.bin","rb");
    if(arq==NULL){
        fprintf(stderr, "Não foi possível abrir adresses.txt\n");
        erro=1;
    }
    if(arq2==NULL){
        fprintf(stderr,"Não foi possível abrir BACKING_STORE.bin\n");
        erro=1;
    }
    if(arqt==NULL){
        fprintf(stderr,"Não foi possível abrir correct.txt\n");
        erro=1;
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
    if(usada!=NULL){
        if(usada->RAM!=NULL){
            for(int i=0;i<128;i++){
                if(usada->RAM!=NULL)
                    free(usada->RAM[i]);
            }   
            free(usada->RAM);
        }
        free(usada);
    }
    if(atual!=NULL)
        free(atual);
    return erro;
}