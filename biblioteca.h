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
  int pontuacao1;
  int ficha;
} Cadastro;

/*                                       Prototipo das funcoes                             */

int verifica_username(char username[], int NV, Cadastro *usuarios);
int verifica_senha(char senha[]);
int confirma_cadastro(int NV, Cadastro *usuarios);
int login(int *bemvindo,int *id_usuario, int NV, Cadastro *usuarios);
void deseja_continuar(char username[], int *menu, int *sair);
int* gera_numeros(int quantidade, int numero_maximo);
int verifica_input(char adivinha[]); 
int adivinhe_numero(int *fichas);

#endif