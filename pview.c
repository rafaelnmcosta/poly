#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "poly.h"

int main(int argc, char const *argv[]){
    
	char * arq_name;
    POLY poly;

    if(argc!=2){
		printf("\n*!* Uso incorreto *!*\nUse a sintaxe ./pview <arquivo a ser lido>\n");
		return 0;
	}

	arq_name = (char*) calloc(strlen(argv[1]), sizeof(char));
    strcpy(arq_name, argv[1]);

    if(!read_poly(arq_name, &poly)) return 0;
    
    show_poly(poly);

    return 0;
}