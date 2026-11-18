#include <stdio.h>
#include <stdlib.h>
#include "abrirTexto.h"
#include "dados.h"
#include "pagina.h"

void localizarEnderecos(FILE *arquivo, dados *acessoAtual, pagina **tabela){
    int resultado = tabela[acessoAtual->pagina];
    if(resultado==-1){
        printf("Deu -1\n");
    }else{
       printf("registrando\n");
       fscanf(arquivo," %c", acessoAtual->pagina);
    }

}

