#include "biblioteca.h"

int verifica_username(char username[30], int NV, Cadastro *usuarios){ 
  int i, username_existente = 0; 

  if (strlen(username) > 16) { // username maior 16 + \n invalido!
    puts("Este username atingiu o máximo de carácteres!");
    return 1;
  } 
  else if(strlen(username) < 3){ 
    puts("O username precisa ter no mínimo 3 carácteres!");
    return 1;
  }
  else {
    for (i = 0; i < strlen(username); i++) {
      if (username[i] == ' ') {
        puts("O username não deve conter espaços!");
        return 1;
      }
    }
    username_existente = 0;
    for (i = 0; i < NV; i++){
      if (strcmp(usuarios[i].username, username) == 0){ // verifica se o username ja existe
        username_existente += 1;
      }
    }

    if (username_existente > 0){
      puts("Esse username já está sendo utilizado!");
      return 1;
    }
    else{
      return 0;
    }
  }      
}

int verifica_senha(char senha[]){
  int tentar_novamente = 0;
  int comparador_senha = 1;
  int i;
  char confirma_senha[25];

  if (strlen(senha) > 15) { // senha maior que 14 + \n invalida!
    puts("A senha atingiu o máximo de carácteres!\n");
    return 1;
  }
  else if(strlen(senha) < 7){
    puts("A senha precisa ter no mínimo 6 carácteres!\n");
    return 1;
  }
  else { 
    for (i = 0; i < strlen(senha); i++) {
      if (senha[i] == ' ') {
        puts("A senha não deve conter espaços!\n");
        return 1;
      }
      else if (senha[i] == '\n') {
        while (comparador_senha == 1){
          senha[i] = '\0';
          if (tentar_novamente == 0){
            printf("Confirme sua senha: ");
          }
          else{
            printf("Tente novamente ou digite 'CANCELAR' para voltar: ");
          }
          fgets(confirma_senha, sizeof(confirma_senha), stdin);
          confirma_senha[strcspn(confirma_senha, "\n")] = '\0'; // TIRANDO O \n PRA PODER COMPARAR AS SENHAS

          if (strcmp(confirma_senha, "CANCELAR") == 0 || strcmp(confirma_senha, "cancelar") == 0){
            comparador_senha = 0;
            puts("");
          }
          else if (strcmp(confirma_senha, senha) == 0){
            return 0;
          }    
          else{
            puts("As senhas não são iguais!\n");
            tentar_novamente = 1;
          }
        }
      }              
    }          
  }
}

int confirma_cadastro(int NV, Cadastro *usuarios){
  char confirmar[10];
  while (1){
    printf("Deseja confirmar o cadastro? [S/N]: ");
    fgets(confirmar, sizeof(confirmar), stdin);
    
    if (strlen(confirmar) > 2 ||confirmar[0] != 'S' && confirmar[0] != 's' && confirmar[0] != 'N' && confirmar[0] != 'n'){
      puts("Resposta inválida!\n");
    }
    else{
      break;
    }
  }
  if (confirmar[0] == 's' || confirmar[0] == 'S') {
    FILE *escreve = fopen("usuarios.txt", "a"); // Abre TXT para adicionar nova conta no final do arquivo
    if (escreve != NULL) {
      fprintf(escreve, "+;%s;%s;\n", usuarios[NV].username, usuarios[NV].senha); // Grava o username e a senha
      fclose(escreve);
      puts("Cadastro realizado com sucesso!\n");
      return 1;
    } 
    else{
      puts("Erro ao abrir o arquivo TXT!\n");
      return 0;
    }
  } 
  else{
    puts("Conta cancelada com sucesso!\n");
    return 0;
  }
}


int login(int *bemvindo,int *id_usuario, int NV, Cadastro *usuarios){
  char usernamelogin[30], senhalogin[20];
  int i, verif_username;
  while (1){
    verif_username = 0;
    printf("\nDigite seu username: ");
    fgets(usernamelogin, sizeof(usernamelogin), stdin);
    usernamelogin[strcspn(usernamelogin, "\n")] = '\0';

    if (strcmp(usernamelogin, "CANCELAR") == 0 || strcmp(usernamelogin, "cancelar") == 0){
      puts("");
      *bemvindo = 1;
      return 0;              // ele volta ao menu principal 
    }
    for (i = 0; i < NV; i++){
      printf("%s\n", usuarios[i].username);
      if (strcmp(usernamelogin, usuarios[i].username) == 0) { 
        *id_usuario = i;          // pega o i e passa para o id pra facilitar no rastreamento de senha
        verif_username = 1;
        break;
      }
    }       
    printf("Digite sua senha: ");
    fgets(senhalogin, sizeof(senhalogin), stdin);
    senhalogin[strcspn(senhalogin, "\n")] = '\0';
    if (strcmp(senhalogin, usuarios[*id_usuario].senha) == 0 && verif_username == 1){ // senha e nome compativeis
      return 1; // o usuario pode prosseguir      
    }
    else{
      puts("\nNome do usuário ou senha incorreto!"); //volta ao inicio do loop
      puts("Tente novamente ou digite 'CANCELAR' para voltar!");
    }
  }
}

void deseja_continuar(char username[], int *menu, int *sair){
  char continuar[10];
  while (1){
    printf("\nQuer continuar? [S/N]: ");
    fgets(continuar, sizeof(continuar), stdin);
    if (continuar[0] == 's' && strlen(continuar) == 2 || continuar[0] == 'S' && strlen(continuar) == 2){
      break;
    }
    else if (continuar[0] == 'n' && strlen(continuar) == 2|| continuar[0] == 'N'&& strlen(continuar) == 2){
      printf("\nAté mais %s!\n", username);
      *menu = 0;
      *sair = 1;
      break;
    }
    else{
      puts("Resposta inválida!\n");
    }
  }
}
