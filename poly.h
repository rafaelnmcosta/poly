/**
 * Header para os códigos poly.c, pbuild.c, pview.c, psum.c e psub.c
 **/

#define ID_SIZE 4
#define MAX_NUM_STR_SIZE 10 //Tamanho máximo de caracteres que um numero pode ter ao ser lido numa string 

/**
 * Struct que define o formato de um polinomio e define que ser arquivo tem um cabeçalho identificador
 * code: string que armazena "poly" para indicar que o arquivo é um polinomio
 * p: potência máxima do polinomio
 * coef: vetor que contem p doubles, representando os coficientes com potencia de acordo com a posição
 * 	ex: 2x²+4x+8 == coef=[8, 4, 2]
 * 					 8*x⁰ + 4*x¹ + 2*x²
 **/
typedef struct {
	char code[ID_SIZE];
	int p;
	double* coef;
} POLY;

int char_to_int(char c);
int get_max_pot(int len, char* str_poly);
void build_poly(int len, char* str_poly, POLY * new_poly);
int write_poly(POLY poly, char* name, int size);

void show_poly(POLY poly);
int is_float(double num);
