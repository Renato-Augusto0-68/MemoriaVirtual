#include <stdio.h>
#include <stdlib.h>
#include "dados.h"
#include "pagina.h"
#include "ram.h"
#include "abrirTexto.h"

void localizarEnderecos(FILE *arquivo, dados *acessoAtual, pagina *tabela, ram *usada){
    int resultado = tabela[acessoAtual->pagina].informacao;
    if(resultado!=-1){
        printf("Deu diferente\n");
    }else{
        printf("registrando\n");
        printf("* fingir que registra *\n");
        resultado=(usada->proxFrame);
        fseek(arquivo,(acessoAtual->pagina)*256L,SEEK_SET);
        if (fread(usada->RAM[resultado],sizeof(signed char),256,arquivo)!=256){
            printf("deu falha de letiura\n");
        }
        tabela[acessoAtual->pagina].informacao=resultado;
        usada->proxFrame++;
    }
    int sep=resultado*(256)+acessoAtual->offset;
    
    printf("Virtual address: %d TLB: %d Physical address: %d\n",acessoAtual->enderecoBruto,usada->RAM[resultado][acessoAtual->offset],sep);
}

