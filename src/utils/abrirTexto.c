#include <stdio.h>
#include <stdlib.h>
#include "abrirTexto.h"
#include "dados.h"
#include "pagina.h"
#include "ram.h"

void localizarEnderecos(FILE *arquivo, dados *acessoAtual, pagina *tabela, ram *usada){
    int resultado = tabela[acessoAtual->pagina].informacao;
    if(resultado!=-1){
        printf("Deu diferente\n");
    }else{
        printf("registrando\n");
        printf("* fingir que registra *\n");

        fseek(arquivo,(acessoAtual->pagina)*256L,SEEK_SET);
        int result=fread(usada->RAM[acessoAtual->pagina][acessoAtual->offset],sizeof(signed char),(acessoAtual->pagina*256+acessoAtual->offset),arquivo);
        if (result!=256){
            printf("deu falha de letiura");
        }
        
    }
}

