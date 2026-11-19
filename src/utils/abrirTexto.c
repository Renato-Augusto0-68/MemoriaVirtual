#include <stdio.h>
#include <stdlib.h>
#include "dados.h"
#include "pagina.h"
#include "ram.h"
#include "abrirTexto.h"

void localizarEnderecos(FILE *arquivo, dados *acessoAtual, pagina *tabela, ram *usada){
    int resultado = tabela[acessoAtual->pagina].informacao;
    printf("%d",resultado);
    if(resultado!=-1){
        printf("Deu diferente\n");
    }else{
        printf("registrando\n");
        printf("* fingir que registra *\n");
        resultado=(usada->proxFrame);
        printf("%d",resultado);
        fseek(arquivo,(acessoAtual->pagina)*256L,SEEK_SET);
        if (fread(usada->RAM[resultado],sizeof(signed char),256,arquivo)!=256){
            printf("deu falha de letiura");
        }
        tabela[acessoAtual->pagina].informacao=resultado;
        usada->proxFrame++;
        printf("A");
    }
    int sep=resultado*(256)+acessoAtual->offset;
    printf("%d %d",usada->RAM[resultado][acessoAtual->offset],sep);
}

