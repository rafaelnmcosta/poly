#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "poly.h"

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

void build_poly(int len, char* str_poly, POLY * new_poly){
	
	int i, j, k, max_pot, pot, coef_size, coef_start;
	char c_coef[MAX_NUM_STR_SIZE];
	char aux_poly[len];
	double f_coef;

	max_pot = get_max_pot(len, str_poly);
	
	new_poly->coef = (double*) calloc(max_pot+1, sizeof(double));
  
	i = len-1; //Começa na ultima potencia do polinomio e percorre ele de tras pra frente
	
	while(i>0){
		coef_size=0;
		pot=char_to_int(str_poly[i]);

		i-=2; // Vai para o ultimo caractere do coeficiente

		while(str_poly[i-1]!='+' && str_poly[i-1]!='-' && i>0){ // Percorre até o primeiro caractere do coef
			i--;
			coef_start = i;
			coef_size++;
		}

		k=0;
		for(j=coef_start; j<coef_start+coef_size; j++){ // Copia o coeficiente p/ uma string auxiliar
			c_coef[k]=str_poly[j];
			k++;
		}
		c_coef[k] = '\0';

		f_coef = atof(c_coef);

		if(i>0){
			i--; // Vai para o sinal

			if(str_poly[i]=='-') f_coef*=-1;

			new_poly->coef[pot] = f_coef;

			i--; //Vai para a proxima potencia
		}
		else{
			new_poly->coef[pot] = f_coef;
		}
	}

	strcpy(new_poly->code, "poly");
	new_poly->p = max_pot;

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

    fclose(poly_arq);
}

//--------------------------------------------------------------------------

void show_poly(POLY poly){
    int i;

    i=poly.p;
    if(is_float(poly.coef[i])){
        printf("\n%.2fx^%d", poly.coef[i], i);
    }
    else{
        printf("%dx^%d", (int)poly.coef[i], i);
    }
    for(i=poly.p-1; i>0; i--){ // Começa imprimindo pela maior potencia e segue até a menor
        if(poly.coef[i]!=0){
            if(poly.coef[i]>0){
                printf("+");
            }
            if(is_float(poly.coef[i])){ // Verifica se o numero tem casas decimais
                printf("%.2lfx^%d", poly.coef[i], i);
            }
            else{
                printf("%dx^%d", (int)poly.coef[i], i);
            }
        }
    }
    if(poly.coef[i]!=0){
        if(poly.coef[i]>0){
            printf("+");
        }
        if(is_float(poly.coef[i])){
            printf("%.2lf\n", poly.coef[i]);
        }
        else{
            printf("%d\n", (int)poly.coef[i]);
        }
    }
}

int is_float(double num){
    double res;

    res = num - (int)num;
    if(res>0) return 1;
    else return 0;
}