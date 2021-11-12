#Poly

Série de programas que realiza operações simples com polinômios através de arquivos binários.

##Compilação e instalação
Os arquivos podem ser compilados através do script build.sh; Serão criados os seguintes executáveis:
1. pbuild - Cria arquivos binários contendo o polinômio informado;
2. pview - Lê um polinômio de um arquivo binário;
3. psum - Soma dois polinômios através de seus arquivos e guarda o resultado em um novo;
4. psub - Funciona como o psum, mas realiza subtração;
Os códigos fontes serão então movidos para uma pasta src

##Estrutura do código
O código foi modularizado em arquivos responsáveis por cada executável, um header poly.h com protótipos de funções, defines e structs, e um poly.c que contém a implementação de todas as funções utilizadas;