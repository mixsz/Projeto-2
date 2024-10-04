#include "biblioteca.h"

typedef struct cadastro {
  char username[17];
  char senha[15];
  int pontuacao1;
} Cadastro;

int main() {
  setlocale(LC_ALL, "portuguese");
  int bemvindo = 0, sair = 0, verificar = 0;
  int PT = 0; // contador de ponto e vírgula
  int i, j;
  int contador_username, contador_senha, contador_cadastros;
  Cadastro usuarios[10];
  char resposta[10];
  char confirma_senha[15];
  int comparador_senha = 1, username_existente = 0, username_finder;

  
  FILE *ler = fopen("usuarios.txt", "r"); // LER ARQUIVO TXT
    char linha[2550]; // VARIAVEL QUE ARMAZENA TEMPORARIAMENTE OS CADASTROS DO TXT
    while (fgets(linha, 2550, ler) !=
           NULL) { // LOOP QUE LE SEPARADAMENTE OS CADASRTOS SEPARADOS POR \n
      contador_username = 0;
      contador_senha = 0;
      PT = 0; // CONTADOR DE PONTO E VÍRGULA
      fscanf(ler, "%s", linha);
      for (i = 0; i < strlen(linha); i++) {
        if (linha[i] == '*') {
          contador_cadastros++;
        }
      }
  
      for (i = 0; i < strlen(linha); i++) {
        if (linha[i] == ';') {
          PT++;
        } else if (linha[i] == '*') {
          continue;
        } else {
          switch (PT) {
          case 1:
            usuarios[contador_cadastros - 1].username[contador_username] = linha[i]; // COLOCA O USERNAME NO VETOR
            usuarios[contador_cadastros - 1].username[contador_username + 1] = '\0'; // TIRA LIXOS QUE FICAM NO FINAL DO VETOR
            contador_username++;
            break;
          case 2:
            usuarios[contador_cadastros - 1].senha[contador_senha] = linha[i];
            usuarios[contador_cadastros - 1].senha[contador_senha + 1] = '\0';
            contador_senha++;
            break;
            
          default:
            break;
          }
        }
      }   
    }
    printf( "%s", usuarios[0].username);
    printf( "%s", usuarios[0].senha);
  
    fclose(ler);

      FILE *escreve1 = fopen("usuarios.txt", "a"); // APLICA UM \N INICIAL CASO NÃO TENHA NADA NO ARQUIVO
      if (contador_cadastros == 0){
      fprintf(escreve1, "\n");}
      fclose(escreve1);  

  
  while (sair != 1){
    
    int NV = contador_cadastros; // Novo Cadastro
    printf("1 - Criar conta \n");
    printf("2 - Acessar conta\n");
    printf("3 - Sair\n");

    if (bemvindo == 0){
      printf("\nBem-vindo! Digite a opção desejada: ");
    }
    else{
      printf("\nDigite a opção desejada: ");
    }
    fgets(resposta, sizeof(resposta), stdin);
    
    if (resposta[0] != '1' && resposta[0] != '2' && resposta[0] != '3' || strlen(resposta) > 2){
      puts("Resposta inválida!\n");
      bemvindo = 1;
    }
    if (resposta[0] == '1'){ // Criar conta
      bemvindo = 1;
      while (verificar == 0){
        printf("\nDigite seu username (máximo 16 caractéres): ");
        fgets(usuarios[NV].username, sizeof(usuarios[NV].username), stdin);
        
        if (strlen(usuarios[NV].username) == 1 || strlen(usuarios[NV].username) > 50) { // username maior que 0 e menor que 16
          puts("Username inválido!");
          continue;
        } 
        else {
          for (i = 0; i < strlen(usuarios[NV].username); i++) {
            if (usuarios[NV].username[i] == ' ') {
              puts("O username não deve conter espaços !");
              break;
            }
            else if (usuarios[NV].username[i] == '*') {
              puts("O username não deve conter asterísco (*) !");
              break;
            }
            else if (usuarios[NV].username[i] == ';') {
              puts("O username não deve conter ponto e vírgula (;) !");
              break;
            }
            else if (usuarios[NV].username[i] == '\n') {
              usuarios[NV].username[i] = '\0';
              
              puts("Username cadastrado!\n");
              verificar = 1;
            }
          } 
          /*
          username_existente = 0;
          if (contador_cadastros != 0){
            for (i = 0; i < 10; i++) {

              for (j = 0; j < 16; j++) {
                if (usuarios[i].username[j] == usuarios[NV].username[j]) {
                    username_finder = 0;
                } // Comparador
                else {
                  username_finder = 1;
                  break;
                }
                if (j == 13 && username_finder == 0) {
                  username_existente++;
                  break;
                }
              }
            }
          }
          if (username_existente == 2){
            puts("Esse username já existe!\n"); 
            continue;
          }
          */
        }
      }
      verificar = 0;
      while (verificar == 0){
        comparador_senha = 1;
        printf("Digite sua senha (máximo 14 caractéres): ");
        fgets(usuarios[NV].senha, sizeof(usuarios[NV].senha), stdin);
        if (strlen(usuarios[NV].senha) == 1 || strlen(usuarios[NV].senha) > 14) { // senha maior que 0 e menor que 16
          puts("Senha inválida!\n");
          continue;
        }
        else {
  
          for (i = 0; i < strlen(usuarios[NV].senha); i++) {
            if (usuarios[NV].senha[i] == ' ') {
              puts("A senha não deve conter espaços!\n");
              break;
            } 
            else if(usuarios[NV].senha[i] == ';'){
              puts("A senha não deve conter ponto e vírgula! (;)\n");
              break;
            }
            else if(usuarios[NV].senha[i] == '*'){
              puts("A senha não deve conter asterísco! (*)\n");
              break;
            }
            else if (usuarios[NV].senha[i] == '\n') {
              while (comparador_senha == 1){
                usuarios[NV].senha[i] = '\0';
                printf("Confirme sua senha: ");
                fgets(confirma_senha, sizeof(confirma_senha), stdin);
                confirma_senha[strcspn(confirma_senha, "\n")] = '\0'; // TIRANDO O \n PRA PODER COMPARAR AS SENHAS
                
                if (strcmp(confirma_senha, usuarios[NV].senha) == 0){
                  puts("Senha cadastrada!\n");
                  verificar = 1;
                  comparador_senha = 0;
                }    
                else{
                  puts("As senhas não são iguais!\n");
                }
              }
            }              
          }          
        }
      }       
      verificar = 0;
   
      FILE *escreve = fopen("usuarios.txt", "a"); // SALVA O CADASTRO NO TXT

      fprintf(
        escreve, "*;%s;%s;\n", usuarios[NV].username, usuarios[NV].senha); // ADICIONA O %X E ESCREVE O USUARIO[NV].XXXX

      fclose(escreve);

      contador_cadastros++;     
    }
  }  
}