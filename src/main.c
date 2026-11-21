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
    if((strcmp(argv[2],"lru")!=0 && strcmp(argv[2],"fifo")!=0) || strlen(argv[2])==0){
        fprintf(stderr,"Erro, modo de substituição da página inexistente\n");
        exit(1);
    } 
    if((strcmp(argv[3],"lru")!=0 && strcmp(argv[3],"fifo")!=0) || strlen(argv[3])==0){
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

    ram *usada = malloc(sizeof(ram));
    if(alocarMemoria(&usada)==1){
        erro=1;
    }
    FILE *arqEnt,*arqMV, *arqResp;
    arqEnt=fopen(argv[1],"r");
    arqMV=fopen("BACKING_STORE.bin","rb");
    if(arqEnt==NULL){
        fprintf(stderr, "Não foi possível abrir %s\n",argv[1]);
        erro=1;
    }
    if(arqMV==NULL){
        fprintf(stderr,"Não foi possível abrir BACKING_STORE.bin\n");
        erro=1;
    }
    arqResp=fopen("correct.txt","w");
    if(arqResp==NULL){
        fprintf(stderr,"Não foi possível abrir correct.txt\n");
        erro=1;
    }
    char verif;
    int lidos;
    if(arqMV!=NULL && arqEnt!=NULL && arqResp!=NULL && erro==0){
        while((lidos=fscanf(arqEnt,"%d%*[ \t]%c",&x.enderecoBruto,&verif))>=1){
            if(lidos==2 && verif!='\n' && verif!='\r'){
                fprintf(stderr,"Erro: formatação inválida!\n");
                break;
            }       
            if(x.enderecoBruto<0){
                fprintf(stderr,"Endereço inválido!\n");
                break;
            }
            x.enderecoBruto=x.enderecoBruto & 0xFFFF;
            x.pagina= (x.enderecoBruto>>8) & 0xFF;
            x.offset = x.enderecoBruto & 0xFF;   
            x.totalEnderecos++;  
            localizarEnderecos(arqMV,&x,atual,usada, arqResp, &emUso);
            
        }
        if(feof(arqEnt))
            guardar(arqResp,&x,&emUso,usada);  
    }
   
    if(arqEnt!=NULL)
        fclose(arqEnt);
    if(arqMV!=NULL)
        fclose(arqMV);
    if(arqResp!=NULL)
        fclose(arqResp);
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