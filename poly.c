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
		while(str_poly[i-1]!='^' && i>0){ // Se o ultimo caracter do polinomio não é uma potencia (x^n), percorre o polinomio de tras pra frente até achar uma
			i--;
		}
		if(i=0) return 1; // Se não encontra nenhuma potência no polinômio, então o grau é 1
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
	int i, j, max_pot, pot;
	char c_coef[MAX_NUM_STR_SIZE], str_aux[MAX_NUM_STR_SIZE];
	double f_coef;

	max_pot = get_max_pot(len, str_poly);

	new_poly->coef = (double*) calloc(max_pot+1, sizeof(double));

	i=0;
	while(i<len){
		j=1;
		str_aux[0] = str_poly[i];
		while(str_poly[i+1]!='x' && str_poly[i+1]!='+' && str_poly[i+1]!='-' && i<len-1){ // Percorre o polinomio até achar o primeiro x ou sinal
			i++;
			str_aux[j] = str_poly[i]; // Vai copiando o conteúdo atual para uma string auxiliar;
			j++;
		}
		str_aux[j] = '\0'; // Fecha a string auxiliar com um NULL

		if(str_poly[i+1]=='x') i++; // Caso tenha lido apenas um sinal ou numero, vai para o X

		if(str_poly[i]=='x'){ // Verifica se o que foi lido até então era um coeficiente de x
			
			if(!strcmp(str_aux, "-")){ // Verifica se o coeficiente é apenas um sinal que deixa x negativo
				strcpy(c_coef, "-1");
			}
			else if(!strcmp(str_aux, "+") || !strcmp(str_aux, "x")){
				strcpy(c_coef, "1");
			} // Se a string guarda apenas um + ou um x o coeficiente é 1
			else{
				strcpy(c_coef, str_aux); // Guarda o valor na string de coef
			}

			if(str_poly[i+1]=='^'){ // Verifica se é uma potência ou apenas um x sozinho
				i+=2; // Vai para o primeiro caracter da potencia
				j=1;
				str_aux[0] = str_poly[i]; 
				while(str_poly[i+1]!='+' && str_poly[i+1]!='-' && i<len-1){
					i++;
					str_aux[j] = str_poly[i]; // Guarda os caracteres da potencia na string auxiliar (Para o caso de potencias com varios digitos ex: x^1000)
					j++;
				}
				str_aux[j] = '\0';
				pot = atoi(str_aux); // Converte a potencia lida para int
				i++;
			}
			else{
				i++;
				pot=1;
			}
		}
		else{
			i++;
			pot=0; // Se não está acompanhado de x, então é uma potencia x^0;
			strcpy(c_coef, str_aux);
		}
		f_coef = atof(c_coef);
		new_poly->coef[pot] = f_coef;
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
    int i=0;

	if(poly.coef[i]!=0){ //Começa pela posição 0 para imprimir o numero sozinho (sem x)
		if(is_float(poly.coef[i])){ // Confere se o numero tem casas decimais para imprimir
			printf("%.2ls", poly.coef[i]);
		}
		else{
			printf("%d", (int)poly.coef[i], i);
		}
		if(poly.coef[i+1]>0){ // Vê se o próximo coeficiente é positivo para imprimir o sinal (negativos já carregam o sinal com eles)
			printf("+");
		}
	}
	
	for(i=1; i<=poly.p; i++){ // Percorre o restante do vetor imprimindo os coeficientes diferentes de 0
		if(poly.coef[i]!=0){
			if(is_float(poly.coef[i])){
				printf("%.2lsx^%d", poly.coef[i], i);
			}
			else{
				printf("%dx^%d", (int)poly.coef[i], i);
			}
		}
		if(poly.coef[i+1]>0 && i<poly.p){
			printf("+");
		}
	}
	printf("\n");
    
}

/* ------------------------------------------------------------------------------------
   | ESSA É UMA VERSÃO MAIS COMPLETA DA FUNÇÃO SHOW_POLY, QUE EXIBE O POLINÔMIO DE FORMA
   | MAIS AMIGÁVEL, COMO POR EXEMPLO IMPRIME OS COEFICIENTES EM ORDEM DECRESCENTE, SE O
   | COEFICIENTE É 1 IMPRIME APENAS O X (AO INVÉS DE 1x^n) E NÃO IMPRIME A POTÊNCIA CASO
   | ELA SEJA 1 OU ZERO (2x^0 == 2 e 4x^1 == 4x)
   | 
   | PORÉM APÓS CONVERSAR COM ALGUNS COLEGAS EU FIQUEI INSEGURO POR ELA IMPRIMIR DE UMA
   | FORMA DIFERENTE DO EXEMPLO DO PDF E PREFERI COMENTAR.
   | NO ENTANTO, ESTÁ RODANDO 100% CASO QUEIRA TESTAR
	-----------------------------------------------------------------------------------

void show_poly(POLY poly){
    int i, first;

    i=poly.p;
	if(poly.coef[i]!=0){
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
		first=0;
	}
	else{
		first=1; // Indica que nenhum numero foi imprimido ainda para não começar um polinomio com "+"
	}

    for(i=poly.p-1; i>1; i--){ // Segue imprimindo em ordem decrescente de potencias se o coeficiente não é nulo
        if(poly.coef[i]!=0){
            if(poly.coef[i]>0 && !first){ // Verifica se o coef é positivo (negativos já carregam o sinal consigo)
                printf("+");
            }
			else{
				first=0; // Indica que já não é mais o primeiro termo do polinômio
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

	if(poly.coef[i]!=0 && i>0){ // Imprime a potencia x^1 separado para seguir o formato x^1 == x
		if(poly.coef[i]>0){
            if(poly.coef[i]>0 && !first){
                printf("+");
            }
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
		i--;
	}

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
*/

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

void convert_poly(POLY * poly){
    int i;
    
    for(i=0; i<=poly->p; i++){
        if(poly->coef[i]!=0){
            poly->coef[i] *= -1;
        }
    }
}
