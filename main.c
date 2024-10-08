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
  if (ler == NULL){
    puts("Arquivo 'usuarios.txt' não encontrado, favor criá-lo para continuar!");
  }
  else{
    while (fgets(linha, 2550, ler) !=NULL) { // LOOP QUE LE SEPARADAMENTE OS CADASRTOS SEPARADOS POR \n
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
      
      while (1){  //  CADASTRO DE USERNAME      
        printf("\nDigite seu username (máximo 16 carácteres): ");
        fgets(usuarios[NV].username, sizeof(usuarios[NV].username), stdin);
        usuarios[NV].username[strcspn(usuarios[NV].username, "\n")] = '\0';
        
        if (verifica_username(usuarios[NV].username, NV, usuarios) == 0) { // se for = 0 -> username valido
          puts("Username cadastrado!\n");
          break;
        }
      }

      while (1){ // CADASTRO DE SENHA
        printf("Digite sua senha (máximo 14 caractéres): ");
        fgets(usuarios[NV].senha, sizeof(usuarios[NV].senha), stdin);  
        
        if (verifica_senha(usuarios[NV].senha) == 0) { // se for = 0 -> senha valida
          puts("Senha cadastrada!\n");
          break;
        }
      }       

      while (1){ // VERIFICA INPUT DE CONFIRMAÇÃO DE CADASTRO
        printf("Deseja confirmar o cadastro? [S/N]: ");
        fgets(confirmar, sizeof(confirmar), stdin);
        
        if (confirma_cadastro(confirmar) == 0){ // só saira do loop se o input for s ou n
          break;
        }
      }
      if (confirmar[0] == 's' || confirmar[0] == 'S') {
        FILE *escreve = fopen("usuarios.txt", "a"); // Abre TXT para adicionar nova conta no final do arquivo
        if (escreve != NULL) {
          fprintf(escreve, "+;%s;%s;\n", usuarios[NV].username, usuarios[NV].senha); // Grava o username e a senha
          fclose(escreve);
          contador_cadastros++;  // Incrementa o contador de cadastros
          puts("Cadastro realizado com sucesso!\n");
        } 
        else{
          puts("Erro ao abrir o arquivo TXT!\n");
        }
      } 
      else{
        puts("Conta cancelada com sucesso!\n");
      }
    }

    // continuar o login aquiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii

  }  
}