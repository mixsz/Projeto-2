#ifndef biblioteca

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <string.h>
#include <ctype.h>


typedef struct cadastro {
  char username[30];
  char senha[25];
  int vitoria1;
  int vitoria2;
  int vitoria3;
  int vitoria4; 
  int vitoria5;
  int ficha;
} Cadastro;

typedef struct { // utilizado no jogo 4
    char nome[35];
    char elemento[10];
    int nivel;
} Carta;

typedef struct{
  char nome[30];
  int total_vitoria;
} Ranking;
/*                                       Prototipo das funcoes                             */

int verifica_username(char username[], int NV, Cadastro *usuarios);
int verifica_senha(char senha[]);
int confirma_cadastro(int NV, Cadastro *usuarios);
int login(int *bemvindo,int *id_usuario, int NV, Cadastro *usuarios);
void deseja_continuar(char username[], int *menu, int *sair);
int* gera_numeros(int quantidade, int numero_maximo);
int verifica_input(char adivinha[]); 
int adivinhe_numero(int *fichas, int *pontuacao);
void exibe_tutorial1();
int pedra_papel_tesoura(int *fichas, int *pontuacao);
void exibe_tutorial2();
int operacao_misteriosa(int *fichas, int *pontuacao);
void exibe_tutorial3();
void calculo (float *resultado,int *numero1, int *numero2, int *numero3, int *seleciona_operacao, int *numero4, int *rodada);
void numero_conforme_rodada(int *rodada, int **numero1, int **numero2, int **numero3, int **numero4);
void leitura_binaria(Cadastro *usuarios, int *counteudo_binario);
void escritura_binaria(Cadastro *usuarios);
void atualiza_binario(Cadastro *usuarios);
int duelo_cartas(int *fichas, int *pontuacao);
Carta criar_carta(int nivel);
int verifica_input2();
char *verbo_ataque(); 
char *verbo_defesa();
void verifica_pontuacao(int ponto_user[], int ponto_casa[], int *vitoria_user);
void exibe_tutorial4();
int termo(int *fichas, int *pontuacao);
void exibe_tutorial5();
void ver_ranking(Cadastro *usuarios, int NV);
void ordenar_ranking(Ranking rank[], int n);
void meu_perfil(char username[], int fichas, int vitoria1, int vitoria2, int vitoria3, int vitoria4, int vitoria5);
void guia_moeda(int *ficha);
int loja(int *ficha);
int comprar_novamente();
void curiosidade(); // As curiosidades foram retiradas do gpt
void desenho(); // Os desenhos foram retirados do site: https://ascii.co.uk/art
void piadoca();

#endif

