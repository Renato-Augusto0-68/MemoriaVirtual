#include <stdio.h>
#include <stdlib.h>
#include "dados.h"
#include "pagina.h"
#include "ram.h"
#include "abrirTexto.h"

void localizarEnderecos(FILE *arquivo, dados *acessoAtual, pagina *tabela, ram *usada, FILE *arqt){
    int resultado = tabela[acessoAtual->pagina].informacao;
    if(resultado!=-1){
        printf("Deu diferente\n");
    }else{
        printf("registrando\n");
        printf("* fingir que registra *\n");
        resultado=(usada->proxFrame);
        
        if(usada->reverse[resultado]!=-1){
            tabela[usada->reverse[resultado]].informacao=-1;
        }
        fseek(arquivo,(acessoAtual->pagina)*256L,SEEK_SET);
        

        if (fread(usada->RAM[resultado],sizeof(signed char),256,arquivo)!=256){
            
        }
        tabela[acessoAtual->pagina].informacao=resultado;
        usada->reverse[resultado] = acessoAtual->pagina;
        usada->proxFrame=((usada->proxFrame+1)%128);
        usada->pageFault++;
    }
    int sep=resultado*(256)+acessoAtual->offset;
    fprintf(arqt,"Virtual address: %d TLB: %d Physical address: %d\n",acessoAtual->enderecoBruto,sep,usada->RAM[resultado][acessoAtual->offset]);
}

