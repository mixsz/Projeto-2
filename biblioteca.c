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