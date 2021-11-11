#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "poly.h"

void sum_poly(POLY poly1, POLY poly2, POLY * polyRes);

int main(int argc, char const *argv[]){
	
    FILE * poly1_arq;
    FILE * poly2_arq;
    FILE * polyRes_arq;
    POLY poly1;
    POLY poly2;
    POLY polyRes;
	char * arq1_name;
    char * arq2_name;
    char * res_name;

	if(argc!=4){
		printf("\n*!* Uso incorreto *!*\nUse a sintaxe ./pbuild <polinomio1> <polinomio2> <arquivo que contera o resultado>\n");
		return 0;
	}

    arq1_name = (char*) calloc(strlen(argv[1]), sizeof(char));
    strcpy(arq1_name, argv[1]);

    arq2_name = (char*) calloc(strlen(argv[2]), sizeof(char));
    strcpy(arq2_name, argv[2]);

    res_name = (char*) calloc(strlen(argv[3]), sizeof(char));
    strcpy(res_name, argv[2]);

    if(!read_poly(arq1_name, &poly1)) return 0;
    if(!read_poly(arq2_name, &poly2)) return 0;



	return 0;
}

void sum_poly(POLY poly1, POLY poly2, POLY * polyRes){
    int i;
}