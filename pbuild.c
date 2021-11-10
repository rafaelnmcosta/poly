#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "poly.h"

int char_to_int(char c);
int get_max_pot(int len, char* str_poly);
POLY build_poly(int len, char* str_poly);
int write_poly(POLY poly, char* name, int size);

int main(int argc, char const *argv[]){
	POLY new_poly;
	char * str_poly;
	char * arq_name;

	if(argc!=3){
		printf("\n*!* Uso incorreto *!*\nUse a sintaxe ./pbuild <polinomio> <arquivo a ser salvo>\n");
		return 0;
	}

	strcpy(str_poly, argv[1]);
	printf("\n%s\n", str_poly);
	strcpy(arq_name, argv[2]);
	printf("\n%s\n", arq_name);

	new_poly = build_poly(strlen(str_poly), str_poly);

	write_poly(new_poly, arq_name, new_poly.p);

	return 0;
}

int char_to_int(char c){
	int conv;
	conv = c-'0'; // Subtrair '0' transforma o char em int
	return conv;
}

int get_max_pot(int len, char* str_poly){
	int i, max_pot, pot_cmp;

	max_pot = char_to_int(str_poly[len-1]); 
	
	for(i=0; i<len; i++){
		if(str_poly[i]=='^'){
			i++;
			pot_cmp = char_to_int(str_poly[i]);
			if(pot_cmp>max_pot){
				max_pot=pot_cmp;
			}
			i++;
		}
	}

	return max_pot;
}

POLY build_poly(int len, char* str_poly){
	
	POLY new_poly;
	int i, j, k, max_pot, pot, coef_size, coef_start;
	char c_coef[MAX_NUM_STR_SIZE];
	char aux_poly[len];
	double f_coef;
	double * aux_coef;

	max_pot = get_max_pot(len, str_poly);
	aux_coef = (double*) calloc(max_pot+1, sizeof(double));

	strcpy(aux_poly, str_poly);
  
	i = len-1; //Começa na ultima potencia do polinomio e percorre ele de tras pra frente
	
	while(i>=0){
		coef_size=0;
		pot=char_to_int(aux_poly[i]);

		i-=2; // Vai para o ultimo caractere do coeficiente

		while(aux_poly[i-1]!='+' && aux_poly[i-1]!='-'){ // Percorre até o primeiro caractere do coef
			i--;
			coef_start = i;
			coef_size++;
		}

		k=0;
		for(j=coef_start; j<coef_size; j++){ // Copia o coeficiente p/ uma string auxiliar
			c_coef[k]=aux_poly[j];
		}

		f_coef = atof(c_coef);

		i--; // Vai para o sinal

		if(aux_poly[i-1]=='-') f_coef*=-1;

		aux_coef[pot] = f_coef;

		i--; //Vai para a proxima potencia
	}

	strcpy(new_poly.code, "poly");
	new_poly.p = max_pot;
	new_poly.coef = aux_coef;

	free(aux_coef);
	return new_poly;
}

int write_poly(POLY poly, char* name, int size){
	FILE* poly_arq;

	poly_arq = fopen(name, "wb");

	if(poly_arq!=NULL){
		fwrite(poly.code, sizeof(char), 4, poly_arq);
		fwrite(&poly.p, sizeof(int), 1, poly_arq);
		fwrite(poly.coef, sizeof(double), size, poly_arq);
	}
	else{
		printf("\n*!* Erro ao salvar arquivo *!*\n");
	}
}