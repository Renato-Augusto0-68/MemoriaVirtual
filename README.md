# Memória Virtual

Projeto da cadeira de Infraestrutura de Software (SO), do professor Marcelo Arcoverde

## Como rodar

### Para testar o código, é necessário definir os argumentos: 
 ### passar o arquivo.txt(nome a sua escolha) contendo os endereços de memória para serem buscados e o arquivo.bin representativo da memória virtual.
### Também é necessário os modos de execucao: fifo ou lru para substituição de páginas e fifo ou lru para sustituição de TLB.
### (São dois modos, paginas e TLB. AMBOS tem que ser passados, mas apenas fifo ou lru).
    ./vm arquivo.txt fifo lru

## Arquivos utilizados


#### alocar.c e alocar.h-> funções para alocação das 3 principais structs de dados utilizadas (RAM, TLB e paginas), e suas declarações de protótipos, respectivamente.

#### ram.h, tlb.h, tlbThread.h, dados.h e pagina.h-> Structs  de dados contendo as informações necessárias para o uso/funcionamento de RAM (simulada), de TLB, das threads para a estruturação inicial de TLB, dados brutos (como enderecos fisicos, total de endereços, página atual e offset) e conteúdo de cada página, respectivamente. 
#### (nos casos específicos de ram e tlb, dentro de suas structs também é posta o campo modo, para indicar se é utilizado FIFO ou Lru para cada um respectivamente)

#### abrirtexto.c e abrirtexto.h-> Funções responsáveis pela abertura das threads para iniciar TLB, a preparação de TLB e o processo de consulta a TLB-Tabela de Páginas-Memória física, e suas declarações de protótipos, respectivamente.