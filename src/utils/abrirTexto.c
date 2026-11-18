#include <stdio.h>
#include <stdlib.h>
#include "abrirTexto.h"
#include "dados.h"
#include "pagina.h"

void localizarEnderecos(FILE *arquivo, dados *acessoAtual, pagina *tabela){
    int resultado = tabela[acessoAtual->pagina].informacao;
    if(resultado!=-1){
        printf("Deu diferente\n");
    }else{
       printf("registrando\n");
       printf("* fingir que registra *\n");

       fseek(arquivo,(acessoAtual->offset)*256L,SEEK_SET);
       
    }

}

