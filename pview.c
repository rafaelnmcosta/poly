#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "poly.h"

int main(int argc, char const *argv[]){
    
    FILE * poly_arq;
	char * arq_name;
    POLY poly;

    if(argc!=2){
		printf("\n*!* Uso incorreto *!*\nUse a sintaxe ./pview <arquivo a ser lido>\n");
		return 0;
	}

	arq_name = (char*) calloc(strlen(argv[1]), sizeof(char));
    strcpy(arq_name, argv[1]);

    poly_arq = fopen(arq_name, "rb");

    if(poly_arq==NULL){
        printf("\n*!* Erro ao abrir arquivo *!*\n");
        return 0;
    }

    fread(poly.code, sizeof(poly.code), 1, poly_arq);
    if(strcmp(poly.code, "poly")){
        printf("\n*!* O arquivo nao eh um polinomio *!*\n");
        return 0;
    }

    fread(&poly.p, sizeof(int), 1, poly_arq);
    
    poly.coef = (double*) calloc(poly.p+1, sizeof(double));
    fread(poly.coef, sizeof(double), poly.p+1, poly_arq);
    
    show_poly(poly);

    return 0;
}