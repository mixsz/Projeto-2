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
} Cadastro;

/*                                       Prototipo das funcoes                             */

int verifica_username(char username[], int NV, Cadastro *usuarios);
int verifica_senha(char senha[]);

#endif