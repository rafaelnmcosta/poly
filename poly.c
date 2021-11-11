#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "poly.h"

int char_to_int(char c){
	int conv;
	conv = c-'0'; // Subtrair '0' transforma o char em int
	return conv;
}

int is_float(double num){
    double res;

	if(num<0) num*=-1; // Transforma em positivo para fazer a subtração

    res = num - (int)num;
    if(res>0) return 1;
    else return 0;
}

int get_max_pot(int len, char* str_poly){
	int i, max_pot, pot_cmp;
	
	i = len-1; 
	if(str_poly[i-1]!='^'){ 
		while(str_poly[i-1]!='^'){ // Se o ultimo caracter do polinomio não é uma potencia (x^n), percorre o polinomio de tras pra frente até achar uma
			i--;
		}
	}
	max_pot = char_to_int(str_poly[i]); // Assume que a potencia encontrada é a maior para poder comparar
	
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
	double f_coef;

	int is_pot, is_coef, is_x_alone; //Verificadores bool para indicar se o termo atual é uma potência, um coeficiente com x¹ ou se o x não tem coef (1*x)

	max_pot = get_max_pot(len, str_poly);

	printf("\nmax_pot: %d\n", max_pot);
	
	new_poly->coef = (double*) calloc(max_pot+1, sizeof(double));
  
	i = len-1; //Começa na ultima potencia do polinomio e percorre ele de tras pra frente
	
	while(i>0){
		coef_size=0;
		is_pot=1;
		is_coef=0;
		is_x_alone=0;

		if(str_poly[i-1]!='^'){ // Verifica se o caracter atual não é uma potencia
			if(str_poly[i]=='x'){ // Se não é uma pôtencia, vê se é um coeficiente com x¹ (x^1)
				if(str_poly[i-1]=='+' || str_poly[i-1]=='-'){ // Vê se o x está sozinho (com coeficiente 1)
					is_x_alone = 1;
				}
				is_coef = 1;
			}
			is_pot = 0;
		}

		printf("\nposicao: %d\nvalor: %c\n", i, str_poly[i]);
		printf("is_pot: %d\nis_coef: %d\nis_x_alone: %d\n", is_pot, is_coef, is_x_alone);

		if(is_pot){
			pot=char_to_int(str_poly[i]);
			is_coef = 1; // (Toda potência é coeficiente de x)
			i-=3; // Vai para ultimo caracter antes do x
			if(i<0 || str_poly[i]=='+' || str_poly[i]=='-'){ // Vê se o x está sozinho (+x^2 ou -x^2)
				is_x_alone = 1;
			}
		}
		else if(is_coef){
			if(!is_x_alone){
				i--; // Vai para o ultimo caractere antes do x caso não seja um sinal
			}
			pot = 1; // Se não é potencia mas é coeficiente, então é a mesma de x¹ (2x == 2x^1) 
		}
		else{
			pot = 0; // Se não é coeficiente, então é uma constante com x⁰ (2 == 2x^0)
		}

		if(is_x_alone){
			f_coef = 1;
		}
		else{
			while(str_poly[i]!='+' && str_poly[i]!='-' && i>=0){ // Percorre até o primeiro caractere do coeficiente
				coef_start = i;
				coef_size++;
				i--;
			}

			k=0;
			for(j=coef_start; j<coef_start+coef_size; j++){ // Copia o coeficiente p/ uma string auxiliar
				c_coef[k]=str_poly[j];
				k++;
			}
			c_coef[k] = '\0'; // Fecha a string com um NULL

			f_coef = atof(c_coef);
		}

		if(i>0 && str_poly[i]!='+' && str_poly[i]!='-'){
			i--; // Vai para o sinal
		}

		if(str_poly[i]=='-') f_coef*=-1;

		printf("\npot: %d\nfcoef: %.2lf\n", pot, f_coef);

		new_poly->coef[pot] = f_coef;
		if(i>0){
			i--; //Vai para a proxima potencia
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
		return 0;
	}

    fclose(poly_arq);
	return 1;
}

int read_poly(char * arq_name, POLY * poly){
    
    FILE * poly_arq;
    
    poly_arq = fopen(arq_name, "rb");

    if(poly_arq==NULL){
        printf("\n*!* Erro ao abrir arquivo *!*\n");
        return 0;
    }

    fread(poly->code, sizeof(poly->code), 1, poly_arq);
    if(strcmp(poly->code, "poly")){
        printf("\n*!* O arquivo %s nao eh um polinomio *!*\n", arq_name);
        return 0;
    }

    fread(&poly->p, sizeof(int), 1, poly_arq);
    
    poly->coef = (double*) calloc(poly->p+1, sizeof(double));
    fread(poly->coef, sizeof(double), poly->p+1, poly_arq);

	return 1;
}

void show_poly(POLY poly){
    int i;

    i=poly.p;
    if(is_float(poly.coef[i])){ // Verifica se o numero tem casas decimais para imprimir (1.00 == 1)
        printf("\n%.2f", poly.coef[i]); // Imprime primeiro pelo coeficiente de maior potencia pois ele sempre sera diferente de 0
		
		if(poly.p==1){ // Verifica se a potencia atual é 1, caso seja, imprime apenas x (x^1 == x)
			printf("x");
		}
		else{
			printf("x^%d", i);
		}
	}
    else{
		if(poly.coef[i]!=1){ // Verifica se o coef é 1 e caso seja imprime apenas x (1*x == x)
        	if(poly.coef[i]!=-1){
				printf("%d", (int)poly.coef[i]);
			}
			else printf("-"); //Se o coef é -1, imprime -x (-1*x == )
		}
		if(poly.p==1){
			printf("x");
		}
		else{
			printf("x^%d", i);
		}
    }

    for(i=poly.p-1; i>1; i--){ // Segue imprimindo em ordem decrescente de potencias se o coeficiente não é nulo
        if(poly.coef[i]!=0){
            if(poly.coef[i]>0){ // Verifica se o coef é positivo (negativos já carregam o sinal consigo)
                printf("+");
            }
            if(is_float(poly.coef[i])){
                printf("%.2lfx^%d", poly.coef[i], i);
            }
            else{
				if(poly.coef[i]!=1){
                	if(poly.coef[i]!=-1){
						printf("%dx^%d", (int)poly.coef[i], i);
					}
					else printf("-x^%d", i); // Imprime -x^n se o coef é -1
				}
				else{
					printf("x^%d", i); // Imprime apenas x^n se o coef é 1
				}
            }
        }
    }

	if(poly.coef[i]!=0){ // Imprime a potencia x^1 separado para seguir o formato x^1 == x
		if(poly.coef[i]>0){
            printf("+");
        }
        if(is_float(poly.coef[i])){
            printf("%.2lfx", poly.coef[i]);
        }
        else{
			if(poly.coef[i]!=1){
				if(poly.coef[i]!=-1){
            		printf("%dx", (int)poly.coef[i]);
				}
				else printf("-x");
			}
			else printf("x");
        }
	}
	i--;
    if(poly.coef[i]!=0){ // Imprime o ultimo numero sem x (5*x⁰ == 5*1 == 5)
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
	else{ // Se não tem potencia x^0, então apenas imprime a quebra de linha
		printf("\n");
	}
}

void sum_poly(POLY poly1, POLY poly2, POLY * polyRes){
    int i, max_pot, min_pot, big_poly;

    if(poly1.p>=poly2.p){ //Encontra o poly de maior grau p/ definir o grau do resultado
        max_pot = poly1.p;
        min_pot = poly2.p; //guarda o grau do menor polinomio
        big_poly = 1; // guarda qual dos polinomios é de maior grau
    }
    else{
        max_pot = poly2.p;
        min_pot = poly1.p;
        big_poly = 2;
    }

    polyRes->coef = (double*) calloc(max_pot+1, sizeof(double));

    for(i=0; i<=min_pot; i++){
        polyRes->coef[i] = poly1.coef[i] + poly2.coef[i];
    }

    while(i<=max_pot){ // Continua percorrendo o maior polinomio até o final
        if(big_poly==1){
            polyRes->coef[i] = poly1.coef[i]; 
        }
        else polyRes->coef[i] = poly2.coef[i];
        i++;
    }

    strcpy(polyRes->code, "poly");
    polyRes->p = max_pot;
}
