/**
 * Header para os códigos poly.c, pbuild.c, pview.c, psum.c e psub.c
 **/

#define ID_SIZE 4 // Tamanho da string que define o código 
#define MAX_NUM_STR_SIZE 10 //Tamanho máximo de caracteres que um numero pode ter ao ser lido numa string 

/**
 * Struct que define o formato de um polinômio
 * code: string "poly" que define o cabeçalho dos arquivos que armazenam polinômios
 * p: potência máxima do polinomio
 * coef: vetor que contem p doubles, representando os coficientes com potencia de acordo com a posição
 * 	ex: 2x²+4x+8 == coef=[8, 4, 2] == 8*x⁰ + 4*x¹ + 2*x²
 **/
typedef struct {
	char code[ID_SIZE];
	int p;
	double* coef;
} POLY;

/**
 * @brief Função que recebe um numeral em char e retorna seu valor em int;
 * 
 * @param c o char a ser convertido;
 * @return Valor de c em inteiro;
 */
int char_to_int(char c);

/**
 * @brief Função que verifica se determinado número tem casas decimais válidas e diferentes de .00;
 * 
 * @param num Número que terá as casas decimais verificadas;
 * @return 1 caso tenha casas decimais válidas, 0 caso não tenha;
 */
int is_float(double num);

/**
 * @brief Função que recebe um polinômio em formato de string e retorna o valor de sua potência mais alta;
 * 
 * @param len Tamanho da string;
 * @param str_poly String que contém o polinômio;
 * @return O valor da potência mais alta encontrada;
 */
int get_max_pot(int len, char* str_poly);

/**
 * @brief Função que monta uma struct POLY a partir de uma string que contém um polinômio;
 * 
 * @param len Tamanho da string;
 * @param str_poly String que contém o polinômio;
 * @param new_poly Ponteiro para a struct que será montada com os dados da string;
 */
void build_poly(int len, char* str_poly, POLY * new_poly);

/**
 * @brief Função que cria e escreve uma sruct POLY em um arquivo binario;
 * 
 * @param poly Struct que será gravada;
 * @param name String do nome do arquivo que será criado;
 * @return 1 para sucesso ou 0 para erro;
 */
int write_poly(POLY poly, char* name);

/**
 * @brief Função que abre um arquivo binário, verifica se é um polinômio pelo cabeçalho e caso seja o guarda em uma struct;
 * 
 * @param arq_name String contendo o nome do arquivo a ser aberto;
 * @param poly Ponteiro para a struct que receberá os dados do arquivo;
 * @return 1 para sucesso ou 0 para erro;
 */
int read_poly(char * arq_name, POLY * poly);

/**
 * @brief Função que imprime um polinômio (Para versão alternativa, confira poly.c);
 * 
 * @param poly Struct que contém os dados desse polinômio;
 */
void show_poly(POLY poly);

/**
 * @brief Função que soma o polinômio 1 ao polinômio 2 e guarda seu resultado em uma outra struct;
 * 
 * @param poly1 Primeiro fator da soma;
 * @param poly2 Segundo fator da soma;
 * @param polyRes Ponteiro para a struct que armazenará o resultado;
 */
void sum_poly(POLY poly1, POLY poly2, POLY * polyRes);

/**
 * @brief Função que multiplica um polinômio por -1; É usada junto com a sum_poly para fazer subtração de polinômios;
 * 
 * @param poly Ponteiro para o polinômio que será multiplicado por -1;
 */
void convert_poly(POLY * poly);
