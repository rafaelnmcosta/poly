#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "poly.h"

int main(int argc, char const *argv[]){
	POLY new_poly;
	char * str_poly;
	char * arq_name;

	if(argc!=3){
		printf("\n*!* Uso incorreto *!*\nUse a sintaxe ./pbuild <polinomio> <arquivo a ser salvo>\n");
		return 0;
	}

	str_poly = (char*) calloc(strlen(argv[1]), sizeof(char));
	arq_name = (char*) calloc(strlen(argv[2]), sizeof(char));

	strcpy(str_poly, argv[1]);
	strcpy(arq_name, argv[2]);	

	build_poly(strlen(str_poly), str_poly, &new_poly);

	write_poly(new_poly, arq_name, new_poly.p+1);

	free(new_poly.coef);

	return 0;
}