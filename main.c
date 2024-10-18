#include "biblioteca.h"

int main() {
  setlocale(LC_ALL, "portuguese");
  srand(time(NULL)); // inicializa o gerador de numeros aleatorios aqui para evitar repeticoes na funcao gera_numeros
  int bemvindo = 0, sair = 0, permissao_acesso = 0, tentar_novamente = 0, verif_username = 0; // variaveis de controle
  int PT = 0; // contador de ponto e vírgula
  int i, j;
  int contador_username, contador_senha, contador_cadastros;
  Cadastro usuarios[15];
  char resposta[10], opcao[10];
  char confirma_senha[15];
  int id_usuario, menu = 1, oi = 1;
  int *NV; // ponteiro para o indice numero de usuarios (da variavel contador_cadastros)
  int *numero_usuario, *numero_casa; // ponteiros (int) usados para atribuir valores da funcao gera_numeros
  int conteudo_binario = 1; // numeros utilizados no binario

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
      fprintf(escreve1, "\n");
    }
    fclose(escreve1);

  leitura_binaria(usuarios, &conteudo_binario); // leitura de fichas e vitorias do struct usuarios
  int numbers0[15], numbers1[15], numbers2[15], numbers3[15];
  if (conteudo_binario == 0){
    escritura_binaria(usuarios); // escreve fichas e vitorias do struct usuarios no arquivo binario
  }
    NV = &contador_cadastros; // Novo Cadastro
    while (sair != 1){
      printf("contador %d\n",contador_cadastros);
      printf("ponteiro %d\n",*NV);


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

        if (*NV >= 15){
          puts("Número máximo de contas atingido!\n");
        }
        else{
          while (1){//  CADASTRO DE USERNAME      
              printf("\nDigite seu username (máximo 16 carácteres): ");
              fgets(usuarios[*NV].username, sizeof(usuarios[*NV].username), stdin);
              usuarios[*NV].username[strcspn(usuarios[*NV].username, "\n")] = '\0';

              if (verifica_username(usuarios[*NV].username, *NV, usuarios) == 0) { // se for = 0 -> username valido
                puts("Username cadastrado!\n");
                break;
              }
          }
          while (1){ // CADASTRO DE SENHA
            printf("Digite sua senha (máximo 14 caractéres): ");
            fgets(usuarios[*NV].senha, sizeof(usuarios[*NV].senha), stdin);  

            if (verifica_senha(usuarios[*NV].senha) == 0) { // se for = 0 -> senha valida
              puts("Senha cadastrada!\n");
              usuarios[*NV].ficha = 10; // inicia a conta com 10 fichas
              break;
            }
          }       
          if(confirma_cadastro(*NV, usuarios) == 1){ // confirma o cadastro e escreve no txt
            contador_cadastros++;       
          }
        }
      }

      if (resposta[0] == '2'){
        id_usuario = -1; // o id sera iniciado como -1 pois n existira o indice -1 no vetor
        permissao_acesso = login(&bemvindo, &id_usuario, *NV, usuarios); // se for 1 significa que o user logou!
        if (permissao_acesso == 1){
          while (menu == 1){
            atualiza_binario(usuarios); // atualiza as vitorias e fichas sempre que voltar ao menu principal
            puts("\n1. Adivinhe o número!");
            puts("2. Pedra, papel, tesoura");
            puts("3. Operaçao misteriosa");
            puts("4. Slweferg");
            puts("X. Guia de fichas");
            puts("X. Consultar fichas");
            puts("X. Sair");
            puts("");
            while (1){
              if (oi == 1) { // dar oi na primeira vez da mensagem
              printf("Olá %s! Digite a opção desejada: ",usuarios[id_usuario].username);
              oi = 0;
            } 
            else{
              printf("Digite a opção desejada: ");
            }
            fgets(opcao,sizeof(opcao),stdin);
            if (opcao[0] != '1' && opcao[0] != '2' && opcao[0] != '3' && opcao[0] != '4' || strlen(opcao) > 2){
               puts("Resposta inválida!\n");
            }
            else{
              break;
            }
          }
          if (opcao[0] == '1'){
            if(adivinhe_numero(&usuarios[id_usuario].ficha,&usuarios[id_usuario].vitoria1) == 0){
              deseja_continuar(usuarios[id_usuario].username, &menu, &sair);  
            }
          }
          if (opcao[0] == '2'){

            if(pedra_papel_tesoura(&usuarios[id_usuario].ficha,&usuarios[id_usuario].vitoria2) == 0){
                deseja_continuar(usuarios[id_usuario].username, &menu, &sair);  
            }

          }
          if (opcao[0] == '3'){

            if(operacao_misteriosa(&usuarios[id_usuario].ficha,&usuarios[id_usuario].vitoria3) == 0){
                deseja_continuar(usuarios[id_usuario].username, &menu, &sair);  
            }

          }
          if (opcao[0] == '4'){
            if(duelo_cartas(&usuarios[id_usuario].ficha,&usuarios[id_usuario].vitoria4) == 0){ // mudar vitoria2
                deseja_continuar(usuarios[id_usuario].username, &menu, &sair);  
            } 
          }
        } // fim do loop menu
      } // fim do permissao = 1
    } // fim resposta = 2    

    if (resposta[0] == '3'){ // sai do programa
      puts("\nTenha um ótimo dia!\n");
      sair = 1;
    }
  }
}