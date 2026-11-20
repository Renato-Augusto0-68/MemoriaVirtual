#include <stdio.h>
#include <stdlib.h>
#include "dados.h"
#include "pagina.h"
#include "ram.h"
#include "tlb.h"
#include "abrirTexto.h"

void verificarTLB(){

}

void localizarEnderecos(FILE *arquivo, dados *acessoAtual, pagina *tabela, ram *usada, FILE *arqt){
    int resultado = tabela[acessoAtual->pagina].informacao;
    usada->timeGoing++;
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
        }
        usada->reverse[resultado] = acessoAtual->pagina;      
        fseek(arquivo,(acessoAtual->pagina)*256L,SEEK_SET);
        if (fread(usada->RAM[resultado],sizeof(signed char),256,arquivo)!=256){
        } 
        
        tabela[acessoAtual->pagina].informacao=resultado;
        
        usada->pageFault++;
    }
    usada->lastUsed[resultado]=usada->timeGoing;
    int sep=resultado*(256)+acessoAtual->offset;
    fprintf(arqt,"Virtual address: %d TLB: %d Physical address: %d\n",acessoAtual->enderecoBruto,sep,usada->RAM[resultado][acessoAtual->offset]);
}

