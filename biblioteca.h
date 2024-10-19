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
  int vitoria4; // adicionar nas funcoes de binario
  int ficha;
} Cadastro;

typedef struct {
    char nome[20];
    char elemento[10];
    int nivel;
} Carta;

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
#endif

