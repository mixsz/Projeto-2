#include "biblioteca.h"

int main() {
  setlocale(LC_ALL, "portuguese");
  int bemvindo = 0, sair = 0, verificar = 0, tentar_novamente = 0; // variaveis de controle
  int PT = 0; // contador de ponto e vírgula
  int i, j;
  int contador_username, contador_senha, contador_cadastros;
  Cadastro usuarios[10];
  char resposta[10], confirmar[10];
  char confirma_senha[15];
  int comparador_senha = 1, username_existente = 0;


  FILE *ler = fopen("usuarios.txt", "r"); // LER ARQUIVO TXT
    char linha[2550]; // VARIAVEL QUE ARMAZENA TEMPORARIAMENTE OS CADASTROS DO TXT
    while (fgets(linha, 2550, ler) !=
           NULL) { // LOOP QUE LE SEPARADAMENTE OS CADASRTOS SEPARADOS POR \n
      contador_username = 0;
      contador_senha = 0;
      PT = 0; // CONTADOR DE PONTO E VÍRGULA
      fscanf(ler, "%s", linha);
      for (i = 0; i < strlen(linha); i++) {
        if (linha[i] == '+') {
          contador_cadastros++;
        }
      }

      for (i = 0; i < strlen(linha); i++) {
        if (linha[i] == ';') {
          PT++;
        } else if (linha[i] == '+') {
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
    printf( "%s\n", usuarios[0].username);
    printf( "%s\n", usuarios[0].senha);  
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
      verificar = 0;
      
      while (1){  //  CADASTRO DE USERNAME      
        printf("\nDigite seu username (máximo 16 carácteres): ");
        fgets(usuarios[NV].username, sizeof(usuarios[NV].username), stdin);
        usuarios[NV].username[strcspn(usuarios[NV].username, "\n")] = '\0';

        if (verifica_username(usuarios[NV].username, NV, usuarios) == 0) { // = 0 -> usuario valido
          puts("Username cadastrado!\n");
          break;
        }
      }
      
      while (verificar == 0){
        tentar_novamente = 0;
        comparador_senha = 1;
        printf("Digite sua senha (máximo 14 caractéres): ");
        fgets(usuarios[NV].senha, sizeof(usuarios[NV].senha), stdin);
        if (strlen(usuarios[NV].senha) > 15) { // senha maior que 14 + \n invalida!
          puts("A senha atingiu o máximo de carácteres!\n");
        }
        else if(strlen(usuarios[NV].senha) < 7){
          puts("A senha precisa ter no mínimo 6 carácteres!\n");
        }
        else { 
          for (i = 0; i < strlen(usuarios[NV].senha); i++) {
            if (usuarios[NV].senha[i] == ' ') {
              puts("A senha não deve conter espaços!\n");
              break;
            }
            else if (usuarios[NV].senha[i] == '\n') {
              while (comparador_senha == 1){
                usuarios[NV].senha[i] = '\0';
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
                else if (strcmp(confirma_senha, usuarios[NV].senha) == 0){
                  puts("Senha cadastrada!\n");
                  verificar = 1;
                  comparador_senha = 0;
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
      verificar = 0;
      while (verificar == 0){
        printf("Deseja confirmar o cadastro? [S/N]: ");
        fgets(confirmar, sizeof(confirmar), stdin);
        if (strlen(confirmar) > 2 ||confirmar[0] != 'S' && confirmar[0] != 's' && confirmar[0] != 'N' && confirmar[0] != 'n'){
          puts("Resposta inválida!\n");
        }
        else{
          verificar = 1;
        }
      }
      if (confirmar[0] == 's' || confirmar[0] == 'S') {
        FILE *escreve = fopen("usuarios.txt", "a"); // Abre para adicionar ao final do arquivo
        if (escreve != NULL) {
          fprintf(escreve, "+;%s;%s;\n", usuarios[NV].username, usuarios[NV].senha); // Grava o username e a senha
          fclose(escreve);
          contador_cadastros++;  // Incrementa o contador de cadastros
          puts("Cadastro realizado com sucesso!\n");
        } 
        else{
          puts("Erro ao abrir o arquivo para gravação.\n");
        }
      } 
      else{
        puts("Conta cancelada com sucesso!\n");
      }
    }

    // continuar o login aquiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii

  }  
}