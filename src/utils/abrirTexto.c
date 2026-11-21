#include <stdio.h>
#include <stdlib.h>
#include "dados.h"
#include "pagina.h"
#include "ram.h"
#include "tlb.h"
#include <pthread.h>
#include "abrirTexto.h"
#include "tlbThread.h"

void guardar(FILE *arq,  dados *acessoAtual,tlb *emUso, ram *usada){
    fprintf(arq, "Number of Translated Addresses = %d\n",acessoAtual->totalEnderecos);
    fprintf(arq,"Page Faults = %d\n",usada->pageFault);
    fprintf(arq,"Page Fault Rate = %.3f\n", (double) usada->pageFault/acessoAtual->totalEnderecos);
    fprintf(arq,"TLB Hits = %d\n",emUso->tlbHit);
    fprintf(arq,"TLB Hit Rate = %.3f",(double)emUso->tlbHit/acessoAtual->totalEnderecos);
}

void *buscaTLB(void *ptr){
    tlbThread * recebido = (tlbThread*)ptr;
    if(((*recebido).acess) == ((*recebido).ptr->pagina[recebido->indicador]))    
        (*recebido).achou=1;
    return NULL;
}

int verificarTLB(tlb *emUso, dados *acessoAtual){
    tlbThread divisao[16];
    for(int i=0;i<16;i++){
        divisao[i].acess=acessoAtual->pagina;
        divisao[i].ptr=emUso;
        divisao[i].indicador=i;
        divisao[i].achou=0;
    }
    pthread_t valor[16];
    for(int i=0;i<16;i++){
        if(pthread_create(&valor[i],NULL,buscaTLB,&divisao[i])!=0){
            fprintf(stderr,"Falha de preparação das threads");
            exit(EXIT_FAILURE);
        }
    }
    for(int i=0;i<16;i++){
        pthread_join(valor[i],NULL);
    }
    int indiceTLB=-1;
    int resultado=0;
    for (int i=0;i<16;i++){
        if(divisao[i].achou==1){
            indiceTLB=divisao[i].indicador;
            
            emUso->tlbHit++;
            break;
        }    
    }    
    if(indiceTLB!=-1){
        if(emUso->modo==2){
            emUso->timeGoing++;
            emUso->lastUsed[indiceTLB]=emUso->timeGoing;
        }
        
    }
    
    return indiceTLB;
}

void localizarEnderecos(FILE *arquivo, dados *acessoAtual, pagina *tabela, ram *usada, FILE *arqt, tlb *emUso){
    int resultTLB = verificarTLB(emUso,acessoAtual);
    int resultado;
    if(resultTLB!=-1){
        resultado=emUso->frame[resultTLB];
    }else{
        
    resultado = tabela[acessoAtual->pagina].informacao;
    
    if(resultado==-1){
        if(tabela->modo==1){
            resultado=(usada->proxFrame);
            usada->proxFrame=((usada->proxFrame+1)%128);
        }
        if(tabela->modo==2){
            int menor=usada->lastUsed[0];
            resultado=0;
            for(int i=1;i<128;i++){
                usada->lastUsed[i];
                if (usada->lastUsed[i]<menor){
                    menor=usada->lastUsed[i];
                    resultado=i;
                }
            }
        }   

        if(usada->reverse[resultado]!=-1){
            tabela[usada->reverse[resultado]].informacao=-1;
            for(int i=0;i<16;i++){
               (emUso->pagina[i]==usada->reverse[resultado]) ? emUso->lastUsed[i] = 0 : 0; 
               (emUso->pagina[i]==usada->reverse[resultado]) ? emUso->pagina[i] = -1 : 0;
            }
        }
        usada->reverse[resultado] = acessoAtual->pagina;

        fseek(arquivo,(acessoAtual->pagina)*256L,SEEK_SET);
        if (fread(usada->RAM[resultado],sizeof(signed char),256,arquivo)!=256){
        } 
        
        tabela[acessoAtual->pagina].informacao=resultado;
        
        usada->pageFault++;
    }
    for(int i=0;i<16;i++){
        if(emUso->pagina[i]==-1){
            resultTLB=i;
            if(emUso->modo==1 && i==emUso->proxEnt){
                emUso->proxEnt=( (emUso->proxEnt+1)%16);
            }
            if(emUso->modo==2){
                emUso->timeGoing++;
                emUso->lastUsed[i]=emUso->timeGoing;
            }
            break;
        }
        
    }
    if(resultTLB==-1){
        resultTLB=0;
        if(emUso->modo==1){
            resultTLB=emUso->proxEnt;
            emUso->proxEnt=((emUso->proxEnt+1)%16);
        }
        if(emUso->modo==2){
            int menor= emUso->lastUsed[0];
            for(int i=1;i<16;i++){
                if(menor>emUso->lastUsed[i]){
                    menor=emUso->lastUsed[i];
                    resultTLB=i;
                }
            }
            emUso->timeGoing++;
            emUso->lastUsed[resultTLB]=emUso->timeGoing;
        }
    }
    emUso->pagina[resultTLB]=acessoAtual->pagina;
    emUso->frame[resultTLB]=resultado;
    }
    usada->timeGoing++;
    usada->lastUsed[resultado]=usada->timeGoing;
    int sep=resultado*(256)+acessoAtual->offset;
    fprintf(arqt,"Virtual address: %d TLB: %d Physical address: %d Value: %d\n",acessoAtual->enderecoBruto,resultTLB,sep,usada->RAM[resultado][acessoAtual->offset]);
}

