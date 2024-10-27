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
    printf("\nDeseja retornar ao menu? [S/N]: ");
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
      puts("Resposta inválida!");
    }
  }
}

int* gera_numeros(int quantidade, int numero_maximo){
  int i;
  int *random; // um ponteiro de inteiros ja que n tem como retornar array de int
  random = malloc(quantidade * sizeof(int));  // aloca memoria de acordo com a quantidade

  if (random == NULL) { // caso de um erro na alocacao de memoria!!
      printf("Erro ao alocar memória.\n");
      return NULL;
  }
  
  for (i = 0; i < quantidade; i++){
    random[i] = rand() % numero_maximo + 1; // inclui o numero maximo
  }
  return random;
}

void exibe_tutorial1(){ // apenas visual
  puts("\nO objetivo do jogo é adivinhar o número gerado aleatório dentro de uma faixa específica, dependendo do nível de dificuldade escolhido pelo jogador.\n");
  puts("Existem 3 níveis de dificuldade:");
  puts("-O normal gera um número aleatório entre 1 e 50.");
  puts("-O dificil gera um número aleatório entre 1 e 100.");
  puts("-O impossível gera um número aleatório entre 1 e 1000.");
  puts("\nVocê possui 4 tentativas para acertar o número gerado no modo Normal e 5 no Difícil.");
  puts("No modo Impossível, você possui 8 tentativas.");
  
}
int verifica_input(char palavra[]) { // verifica se o input e um numero
  for (int i = 0; i < strlen(palavra); i++) {
    if (!isdigit(palavra[i])) {
        return 1;
    }
  }
  return 0;
}

int adivinhe_numero(int *fichas, int *pontuacao){
  char selecionar[10], tutorial[10], adivinha[10];
  int catalogo = 1, vidas, i, erro = 0, numero = 0, vitoria = 0;
  int *random; // ponteiro que armazenara o numero gerado aleatoriamente
  while (1){
    if (catalogo == 1){
      puts("\n1 - Normal 🪙 ");
      puts("2 - Dificíl 🪙  (2x)");
      puts("3 - IMPOSSÍVEL 🪙  (3x)");
      puts("4 - Como jogar?");
      puts("5 - Voltar");    
    }
    printf("\nSelecione a dificuldade: ");
    fgets(selecionar,sizeof(selecionar),stdin);
    
    if (strlen(selecionar) == 2 && selecionar[0] == '1'){ // modo normal
      vidas = 4;
      puts("\nVocê selecionou a dificuldade normal.");
      random = gera_numeros(1, 50);
      puts("O número foi gerado entre 1 a 50!\n");
      while (vidas > 0){
        numero = 0;
        if (vidas != 4){
          if (vidas == 1){
            puts("(1 vida restante)\n");
          }
          else{
            printf("(%d vidas restantes)\n\n", vidas);
          }
        }
        printf("QUE NÚMERO EU SOU? ");
        fgets(adivinha,sizeof(adivinha),stdin);
        adivinha[strcspn(adivinha, "\n")] = '\0';       
        if(verifica_input(adivinha) == 1){
          if (erro == 0){
            puts("A PRÓXIMA GRAÇA VOCÊ PERDERÁ UMA VIDA!\n"); // se o user colocar letras ou caracteres especiais
            erro += 1; // na proxima vez que ele colocar algo invalido ele perde uma vida
          }
          else{
            if (erro == 1){
              puts("EU AVISEI! VOCÊ PERDEU UMA VIDA!");
              vidas -= 1;
            }
            else{
              puts("EU AVISEI! VOCÊ PERDEU OUTRA VIDA!"); // e aqui mais uma vida...
            }
          }
        }        
        else if (verifica_input(adivinha) == 0){
          if (atof(adivinha) != random[0]){
            if (atof(adivinha) > 50){
              puts("\nO NÚMERO MAXIMO É 50!");
              vidas -= 1;
            }
            else if (atof(adivinha) < 1){
              puts("\nO NÚMERO MÍNIMO É 1!");
              vidas -= 1;
            }
            else if (atof(adivinha) > random[0]){
              vidas -= 1;
              puts("\nO NÚMERO É MENOOOOOOOOR!");
            }
            else if (atof(adivinha) < random[0]){
              puts("\nO NÚMERO É MAIOOOOOOOR!");
              vidas -= 1;
            }
          }
          else{
            puts("\nPARABÉNS! VOCÊ CONSEGUIU ADIVINHAR O NÚMERO! :D");
            printf("Total de chutes: %d\n", 4 - vidas); 
            vitoria = 1;
            *pontuacao += 1;
            break;
          }
        }
      }
      if (vitoria == 0){
        printf("\nQUE PENA! VOCÊ PERDEU!\nO NÚMERO ERA %d :(\n", random[0]);
        *fichas -= 1;
      puts("-1 🪙");
      }
      else{
        *fichas += 1;
        puts("+1 🪙");
      }
      free(random); // libera memoria
      return 0;
    }
    else if (strlen(selecionar) == 2 && selecionar[0] == '2'){
      vidas = 5;
      puts("\nVocê selecionou a dificuldade dificíl.");
      random = gera_numeros(1, 100);
      puts("O número foi gerado entre 1 a 100!\n");
      while (vidas > 0){
        numero = 0;
        if (vidas != 5){
          if (vidas == 1){
            puts("(1 vida restante)\n");
          }
          else{
            printf("(%d vidas restantes)\n\n", vidas);
          }
        }
        printf("QUE NÚMERO EU SOU? ");
        fgets(adivinha,sizeof(adivinha),stdin);
        adivinha[strcspn(adivinha, "\n")] = '\0';       
        if(verifica_input(adivinha) == 1){
          if (erro == 0){
            puts("A PRÓXIMA GRAÇA VOCÊ PERDERÁ UMA VIDA!\n");
            erro += 1;
          }
          else{
            if (erro == 1){
              puts("EU AVISEI! VOCÊ PERDEU UMA VIDA!");
              vidas -= 1;
            }
            else{
              puts("EU AVISEI! VOCÊ PERDEU OUTRA VIDA!");
            }
          }
        }        
        else if (verifica_input(adivinha) == 0){
          if (atof(adivinha) != random[0]){
            if (atof(adivinha) > 100){
              puts("\nO NÚMERO MAXIMO É 100!");
              vidas -= 1;
            }
            else if (atof(adivinha) < 1){
              puts("\nO NÚMERO MÍNIMO É 1!");
              vidas -= 1;
            }
            else if (atof(adivinha) > random[0]){
              vidas -= 1;
              puts("\nO NÚMERO É MENOOOOOOOOR!");
            }
            else if (atof(adivinha) < random[0]){
              puts("\nO NÚMERO É MAIOOOOOOOR!");
              vidas -= 1;
            }
          }
          else{
            puts("\nPARABÉNS! VOCÊ CONSEGUIU ADIVINHAR O NÚMERO! :D");
            printf("Total de chutes: %d\n", 5 - vidas);            
            vitoria = 1;
            *pontuacao += 1;
            break;
          }
        }
      }
      if (vitoria == 0){
        printf("\nQUE PENA! VOCÊ PERDEU!\nO NÚMERO ERA %d :(\n", random[0]);
        *fichas -= 1;
        puts("-1 🪙");
      }
      else{
        puts("+2 🪙");
        *fichas += 2;
      }
      free(random); // libera memoria
      return 0;
    }
    else if (strlen(selecionar) == 2 && selecionar[0] == '3'){
      vidas = 8;
      puts("\nVocê selecionou a dificuldade IMPOSSÍVEL.");
      random = gera_numeros(1, 1000);
      puts("O número foi gerado entre 1 a 1000!\n");
      while (vidas > 0){
        numero = 0;
        if (vidas != 8){
          if (vidas == 1){
            puts("(1 vida restante)\n");
          }
          else{
            printf("(%d vidas restantes)\n\n", vidas);
          }
        }
        printf("QUE NÚMERO EU SOU? ");
        fgets(adivinha,sizeof(adivinha),stdin);
        adivinha[strcspn(adivinha, "\n")] = '\0';       
        if(verifica_input(adivinha) == 1){
          if (erro == 0){
            puts("A PRÓXIMA GRAÇA VOCÊ PERDERÁ UMA VIDA!\n");
            erro += 1;
          }
          else{
            if (erro == 1){
              puts("EU AVISEI! VOCÊ PERDEU UMA VIDA!");
              vidas -= 1;
            }
            else{
              puts("EU AVISEI! VOCÊ PERDEU OUTRA VIDA!");
            }
          }
        }        
        else if (verifica_input(adivinha) == 0){
          if (atof(adivinha) != random[0]){
            if (atof(adivinha) > 1000){
              puts("\nO NÚMERO MAXIMO É 1000!");
              vidas -= 1;
            }
            else if (atof(adivinha) < 1){
              puts("\nO NÚMERO MÍNIMO É 1!");
              vidas -= 1;
            }
            else if (atof(adivinha) > random[0]){
              vidas -= 1;
              puts("\nO NÚMERO É MENOOOOOOOOR!");
            }
            else if (atof(adivinha) < random[0]){
              puts("\nO NÚMERO É MAIOOOOOOOR!");
              vidas -= 1;
            }
          }
          else{
            puts("\nPARABÉNS! VOCÊ CONSEGUIU ADIVINHAR O NÚMERO! :D");
            printf("Total de chutes: %d\n", 8 - vidas);   
            vitoria = 1;
            *pontuacao += 1;
            break;
          }
        }
      }
      if (vitoria == 0){
        printf("\nQUE PENA! VOCÊ PERDEU!\nO NÚMERO ERA %d :(\n", random[0]);
        *fichas -= 1;
        puts("-1 🪙");
      }
      else{
        *fichas += 3;
        puts("+3 🪙");
      }
      free(random); // libera memoria
      return 0;
    }
    else if (strlen(selecionar) == 2 && selecionar[0] == '4'){
      exibe_tutorial1();
      while(1){
        printf("\nDeseja jogar? [S/N]: ");
        fgets(tutorial,sizeof(tutorial),stdin);
        if (strlen(tutorial) == 2 && tutorial[0] == 'n' || tutorial[0] == 'N'){
          return 1;
        }
        else if (strlen(tutorial) == 2 && tutorial[0] == 's' || tutorial[0] == 'S'){
          catalogo = 1;
          break;
        }
        else{
          puts("Resposta inválida!");
        }
      }
    }
    else if (strlen(selecionar) == 2 && selecionar[0] == '5'){
      return 1;
    }
    else{
      puts("Resposta inválida!");
      catalogo = 0;
    }
  }
}

int pedra_papel_tesoura(int *fichas, int *pontuacao){
  char selecionar[10],tutorial[10], objeto_user[10], qualquer_coisa[10];
  int catalogo = 1, comeco = 1, pt_casa = 0, pt_user = 0;
  int *objeto_casa;
  while(1){
    if (catalogo == 1){
      puts("\n1. Jogar");
      puts("2. Como jogar?");
      puts("3. Voltar\n");
    }
    printf("Digite a opção desejada: ");
    fgets(selecionar,sizeof(selecionar),stdin);           
    if (selecionar[0] != '1' && selecionar[0] != '2' && selecionar[0] != '3' || strlen(selecionar) > 2){
      puts("Resposta inválida!\n");
      catalogo = 0;
    }
    else if(selecionar[0] == '3'){
      return 1;
    }
    else if(selecionar[0] == '2'){
      exibe_tutorial2();
      while(1){
        printf("\nDeseja jogar? [S/N]: ");
        fgets(tutorial,sizeof(tutorial),stdin);
        if (strlen(tutorial) == 2 && tutorial[0] == 'n' || tutorial[0] == 'N'){
          return 1;
        }
        else if (strlen(tutorial) == 2 && tutorial[0] == 's' || tutorial[0] == 'S'){
          catalogo = 1;
          break;
        }
        else{
          puts("Resposta inválida!");
        }
      }
    }
    else if(selecionar[0] == '1'){
      puts("\nINICIANDO O DUELO MELHOR DE 3!\n");
      while (pt_casa < 2 && pt_user < 2){
        if(comeco == 1){
          printf("VOCÊ %d VS CASA %d\n\n", pt_user, pt_casa);        
          puts("1 - Pedra");
          puts("2 - Papel");
          puts("3 - Tesoura\n");
          printf("FAÇA SUA ESCOLHA: ");
        }
        else{
          printf("FAÇA SUA ESCOLHA CORRETAMENTE: ");
        }
        comeco = 1;
        fgets(objeto_user,sizeof(objeto_user),stdin);
        objeto_user[strcspn(objeto_user, "\n")] = 0;
        if(verifica_input(objeto_user) == 1){
          puts("Esse objeto não existe!\n");
          comeco = 0;
        }
        else{
          if (objeto_user[0] != '1' && objeto_user[0] != '2' && objeto_user[0] != '3'){
            puts("Esse objeto não existe!\n");
            comeco = 0;
          }
          else{
            if (objeto_user[0] == '1'){
              puts("\nVocê escolheu PEDRA.");
            }
            else if(objeto_user[0] == '2'){
              puts("\nVocê escolheu PAPEL.");
            }
            else{
              puts("\nVocê escolheu TESOURA.");
            }  
            objeto_casa = gera_numeros(1,3);
            if (objeto_casa[0] == 1){
              puts("A casa escolheu PEDRA.\n");
            }
            else if(objeto_casa[0] == 2){
              puts("A casa escolheu PAPEL.\n");
            }
            else{
              puts("A casa escolheu TESOURA.\n");
            }  
            if (atoi(objeto_user) == objeto_casa[0]){
              puts("EMPATE NA RODADA!\n");
            }
            else if (atoi(objeto_user) == 1 && objeto_casa[0] == 3 || atoi(objeto_user) == 3 && objeto_casa[0] == 2 || atoi(objeto_user) == 2 && objeto_casa[0] == 1){
              if (pt_user == 0){
                puts("VOCÊ GANHOU A RODADA!\n");
              }
              pt_user += 1;
            }
            else{
              if (pt_casa == 0){
                puts("VOCÊ PERDEU A RODADA!\n");
              }
              pt_casa += 1;
            }
            if (pt_casa != 2 && pt_user != 2){
              while (1) {
                  puts("Pressione ENTER para continuar...");
                  fgets(qualquer_coisa, sizeof(qualquer_coisa), stdin);
                  if (qualquer_coisa[0] == '\n') {
                      break; 
                  }
              }
            }
            else{
              if (pt_casa == 2){
                puts("OH NÃO! VOCÊ PERDEU O DUELO!");
                *fichas -= 1;
              puts("-1 🪙");
              }
              else{
                puts("MUITO BEM! VOCÊ GANHOU O DUELO!");
                *fichas += 1;
                *pontuacao += 1;
                puts("+1 🪙");
              }
            }
          }
        }
      }
      return 0;
    }
  }
}

void exibe_tutorial2(){
  puts("\nO objetivo do jogo é ganhar 2 rodadas contra a casa escolhendo um dos três objeto: pedra, papel ou tesoura.\n\nCada objeto vence o outro:\n");
  puts("-Pedra vence tesoura");
  puts("-Tesoura vence papel");
  puts("-Papel vence pedra");
  puts("\nObs: Caso o obeto escolhido seja o mesmo que o da casa, o jogo continua e ninguem pontuará na rodada.");
}
void exibe_tutorial3(){
  puts("\nNeste jogo, seu objetivo é descobrir qual operador utilizar:\nSoma (+)\nSubtração (-)\nMultiplicação (*)\nDivisão (/)\n");
  puts("Os números serão exibidos na tela, e você deverá completar o sinal para operação.");
  puts("Adivinhe o máximo de sinais que conseguir!\nCada acerto vale 1 ponto e a média para passar é 6.");
  puts("Obs: O jogo fica mais dificíl conforme as rodadas passam.");
}

char verifica_resposta(){ // verifica input do usuario no jogo 3 (operacao misteriosa)
  char resposta_usuario[10];
  while (1){
     printf("Qual operação foi utilizada? ");
     fgets(resposta_usuario,sizeof(resposta_usuario),stdin);
     if (strlen(resposta_usuario) != 2 || resposta_usuario[0] != '+' && resposta_usuario[0] != '-' && resposta_usuario[0] != '*' && resposta_usuario[0] != '/'){
       puts("Digite apenas a operação! Ex: +, -, *, /\n");
     }
    else{
      return resposta_usuario[0];
    }
   }
}

void numero_conforme_rodada(int *rodada, int **numero1, int **numero2, int **numero3, int **numero4){
  // gera numeros aleatorios conforme a rodada, no terceiro jogo (operacao misteriosa)
  // utilizado ponteiro do ponteiro para poder alterar o valor da variavel diretamente dentro da funcao
  if (*rodada < 3){ 
     *numero1 = gera_numeros(1,50);
     *numero2 = gera_numeros(1,50);
   }
   else if(*rodada > 3 && *rodada > 7){
     *numero1 = gera_numeros(1,75);
     *numero2 = gera_numeros(1,50);
     *numero3 = gera_numeros(1,60);
   }
   else{
     *numero1 = gera_numeros(1,100);
     *numero2 = gera_numeros(1,100);
     *numero3 = gera_numeros(1,80);
     *numero4 = gera_numeros(1,60);
   }
}

void calculo (float *resultado,int *numero1, int *numero2, int *numero3, int *seleciona_operacao, int *numero4, int *rodada){ // o calculo e gerado aleatorio e depende de duas variaveis: seleciona_operacao, operacao_secundaria
  int *operacao_secundaria;
  int *n1_ajuda, *n2_ajuda; // numeros que dificultam determinadas contas, principalmente divisoes
  operacao_secundaria = gera_numeros(1,4);
  n1_ajuda = gera_numeros(1,100);
  n2_ajuda = gera_numeros(1,100);
  if (seleciona_operacao[0] == 1){
    if (*rodada < 7){
      if (operacao_secundaria[0] == 1){
        *resultado = numero1[0] + numero2[0] + numero3[0];
         printf("%d(?)%d + %d = %.1f\n\n", numero1[0], numero2[0], numero3[0], *resultado);
      }
      else if (operacao_secundaria[0] == 2){
         *resultado = numero1[0] + numero2[0] - numero3[0];
         printf("%d(?)%d - %d = %.1f\n\n", numero1[0], numero2[0], numero3[0], *resultado);
  
      }
      else if (operacao_secundaria[0] == 3){
         *resultado = numero1[0] * numero2[0] + numero3[0];
         printf("%d * %d(?)%d = %.1f\n\n", numero1[0], numero2[0], numero3[0], *resultado);
      }
      else{
         *resultado = ((float)numero1[0] + (float)numero2[0] / (float)numero3[0]) * n1_ajuda[0] - n2_ajuda[0];
         printf("(%d(?)%d / %d) * %d - %d = %.1f\n\n", numero1[0], numero2[0], numero3[0], n1_ajuda[0],n2_ajuda[0], *resultado);
      }
    }
    else{
      if (operacao_secundaria[0] == 1){
        *resultado = numero1[0] + numero2[0] + numero3[0] - numero4[0];
         printf("%d(?)%d + %d - %d = %.1f\n\n", numero1[0], numero2[0], numero3[0], numero4[0],*resultado);
      }
      else if (operacao_secundaria[0] == 2){
         *resultado = numero1[0] + numero2[0] - numero3[0] + numero4[0];
         printf("%d(?)%d - %d + %d = %.1f\n\n", numero1[0], numero2[0], numero3[0], numero4[0],*resultado);

      }
      else if (operacao_secundaria[0] == 3){
         *resultado = numero1[0] * numero2[0] + numero3[0] - numero4[0];
         printf("%d * %d(?)%d - %d = %.1f\n\n", numero1[0], numero2[0], numero3[0], numero4[0],*resultado);
      }
      else{
         *resultado = ((float)numero1[0] + (float)numero2[0] / (float)numero3[0] + (float)numero4[0]) * (float)n1_ajuda[0] * (float)n2_ajuda[0];;
         printf("(%d(?)%d / %d + %d * 10) * %d * %d = %.1f\n\n", numero1[0], numero2[0], numero3[0], numero4[0],n1_ajuda[0],n2_ajuda[0],*resultado);
      }
    }
  }
  if (seleciona_operacao[0] == 2){
    if (*rodada < 7){
      if (operacao_secundaria[0] == 1){
        *resultado = numero1[0] - numero2[0] + numero3[0];
         printf("%d(?)%d + %d = %.1f\n\n", numero1[0], numero2[0], numero3[0], *resultado);
      }
      else if (operacao_secundaria[0] == 2){
         *resultado = numero1[0] - numero2[0] - numero3[0];
         printf("%d(?)%d - %d = %.1f\n\n", numero1[0], numero2[0], numero3[0], *resultado);
      }
      else if (operacao_secundaria[0] == 3){
         *resultado = numero1[0] - numero2[0] * numero3[0];
         printf("%d(?)%d * %d = %.1f\n\n", numero1[0], numero2[0], numero3[0], *resultado);
      }
      else{
         *resultado = ((float)numero1[0] - (float)numero2[0] / (float)numero3[0]) * n1_ajuda[0] - n2_ajuda[0];
         printf("(%d(?)%d / %d) * %d - %d = %.1f\n\n", numero1[0], numero2[0], numero3[0], n1_ajuda[0],n2_ajuda[0],*resultado);
      }
    }
    else{
      if (operacao_secundaria[0] == 1){
        *resultado = numero1[0] - numero2[0] + numero3[0] * numero4[0];
         printf("%d(?)%d + %d * %d = %.1f\n\n", numero1[0], numero2[0], numero3[0], numero4[0],*resultado);
      }
      else if (operacao_secundaria[0] == 2){
         *resultado = numero1[0] - numero2[0] - numero3[0] + numero4[0];;
         printf("%d(?)%d - %d + %d = %.1f\n\n", numero1[0], numero2[0], numero3[0],numero4[0],*resultado);
      }
      else if (operacao_secundaria[0] == 3){
         *resultado = - numero1[0] - numero2[0] * numero3[0] + numero4[0];
         printf("-%d(?)%d * %d + %d = %.1f\n\n", numero1[0], numero2[0], numero3[0], numero4[0], *resultado);
      }
      else{
         *resultado = ((-(float)numero1[0] - (float)numero2[0]) * (float)n1_ajuda[0] / (float)numero3[0] * -(float)numero4[0]) * (float)n2_ajuda[0];
         printf("((-%d(?)%d) * %d / %d * (-%d)) * %d = %.1f\n\n", numero1[0], numero2[0], n1_ajuda[0], numero3[0], numero4[0], n2_ajuda[0], *resultado);
      }
    }
  }
  if (seleciona_operacao[0] == 3){
    if (*rodada < 7){
      if (operacao_secundaria[0] == 1){
        *resultado = numero1[0] * numero2[0] + numero3[0];
         printf("%d(?)%d + %d = %.1f\n\n", numero1[0], numero2[0], numero3[0], *resultado);
      }
      else if (operacao_secundaria[0] == 2){
         *resultado = numero1[0] * numero2[0] - numero3[0];
         printf("%d(?)%d - %d = %.1f\n\n", numero1[0], numero2[0], numero3[0], *resultado);
      }
      else if (operacao_secundaria[0] == 3){
         *resultado = numero1[0] * numero2[0] * numero3[0];
         printf("%d(?)%d * %d = %.1f\n\n", numero1[0], numero2[0], numero3[0], *resultado);
      }
      else{
         *resultado = (float)numero1[0] * (float)numero2[0] / (float)numero3[0] - (float)n1_ajuda[0];
         printf("%d(?)%d / %d - %d = %.1f\n\n", numero1[0], numero2[0], numero3[0], n1_ajuda[0],*resultado);
      }
    }
    else{
      if (operacao_secundaria[0] == 1){
        *resultado = numero1[0] * numero2[0] + numero3[0] - numero4[0];
         printf("%d(?)%d + %d - %d = %.1f\n\n", numero1[0], numero2[0], numero3[0], numero4[0], *resultado);
      }
      else if (operacao_secundaria[0] == 2){
         *resultado = numero1[0] * numero2[0] - numero3[0] - numero4[0];
         printf("%d(?)%d - %d - %d = %.1f\n\n", numero1[0], numero2[0], numero3[0], numero4[0], *resultado);
      }
      else if (operacao_secundaria[0] == 3){
         *resultado = ((float)numero1[0] * (float)numero2[0] *(float)numero3[0] - (float)numero4[0]) / (float)n1_ajuda[0] + (float)n2_ajuda[0];
         printf("(%d(?)%d * %d - %d) / %d + %d = %.1f\n\n", numero1[0], numero2[0], numero3[0], numero4[0], n1_ajuda[0], n2_ajuda[0], *resultado);
      }
      else{
         *resultado = ((float)numero1[0] * (float)numero2[0] / (float)numero3[0] - (float)numero4[0]) * (float)n1_ajuda[0] - (float)n2_ajuda[0];
         printf("(%d(?)%d / %d - %d) * %d - %d = %.1f\n\n", numero1[0], numero2[0], numero3[0], numero4[0], n1_ajuda[0],n2_ajuda[0],*resultado);
      }
    }
  }
  if (seleciona_operacao[0] == 4){
    if (*rodada < 7){
      if (operacao_secundaria[0] == 1){
        *resultado = (float)n1_ajuda[0] + ((float)numero1[0] / (float)numero2[0] + (float)numero3[0]) * (float)n2_ajuda[0];
         printf("%d + (%d(?)%d + %d) * %d = %.1f\n\n", n1_ajuda[0],numero1[0], numero2[0], numero3[0], n2_ajuda[0],*resultado);
      }
      else if (operacao_secundaria[0] == 2){
         *resultado = (float)numero1[0] * (float)n1_ajuda[0] / (float)numero2[0] - (float)numero3[0];
         printf("%d * %d(?)%d - %d = %.1f\n\n", numero1[0], n1_ajuda[0],numero2[0], numero3[0], *resultado);
      }
      else if (operacao_secundaria[0] == 3){
         *resultado = (float)n1_ajuda[0]+(float)numero1[0] / (float)numero2[0] * (float)numero3[0];
         printf("%d + %d(?)%d * %d = %.1f\n\n", n1_ajuda[0],numero1[0], numero2[0], numero3[0], *resultado);
      }
      else{
         *resultado = ((float)numero1[0] / (float)numero2[0] / (float)numero3[0]) * (float)n1_ajuda[0];
         printf("(%d(?)%d / %d) * %d = %.1f\n\n", numero1[0], numero2[0], numero3[0], n1_ajuda[0],*resultado);
      }
    }
    else{
      if (operacao_secundaria[0] == 1){
        *resultado = ((float)n1_ajuda[0] - (float)(n2_ajuda[0])) * (float)numero1[0] / (float)numero2[0] + (float)numero3[0] + (float)numero4[0];
         printf("(%d - %d) * %d(?)%d + %d + %d = %.1f\n\n", n1_ajuda[0],n2_ajuda[0],numero1[0], numero2[0], numero3[0], numero4[0],*resultado);
      }
      else if (operacao_secundaria[0] == 2){
         *resultado = ((float)numero1[0] / (float)numero2[0] - (float)numero3[0] + (float)numero4[0] * (float)n1_ajuda[0]) * (float)n2_ajuda[0];
         printf("(%d(?)%d - %d + %d * %d) * %d = %.1f\n\n", numero1[0], numero2[0], numero3[0], numero4[0], n1_ajuda[0],n2_ajuda[0],*resultado);
      }
      else if (operacao_secundaria[0] == 3){
         *resultado = (float)numero1[0] / (float)numero2[0] * (float)numero3[0] * (float)numero4[0];
         printf("%d(?)%d * %d * %d = %.1f\n\n", numero1[0], numero2[0], numero3[0],numero4[0], *resultado);
      }
      else{
         *resultado = (float)numero1[0] * (float)n1_ajuda[0] / (float)numero2[0] / ((float)n2_ajuda[0] - ((float)numero3[0] + (float)numero4[0]));
         printf("%d * %d(?)%d / (%d-(%d + %d)) = %.1f\n\n", numero1[0], n1_ajuda[0], numero2[0], n2_ajuda[0],numero3[0], numero4[0],*resultado);
      }
    }
  }
}

int operacao_misteriosa(int *fichas, int *pontuacao){
  int catalogo = 1, i, rodada = 1, quantidade_numeros_rodada, resultado_conta, acerto, erro;
  float resultado;
  char selecionar[10], tutorial[10],resposta_usuario[10], continuar[5];
  int *seleciona_operacao, *numero1, *numero2, *numero3, *numero4;
   while(1){
    if (catalogo == 1){
      puts("\n1. Jogar");
      puts("2. Como jogar?");
      puts("3. Voltar\n");
    }
    printf("Digite a opção desejada: ");
    fgets(selecionar,sizeof(selecionar),stdin);           
    if (selecionar[0] != '1' && selecionar[0] != '2' && selecionar[0] != '3' || strlen(selecionar) > 2){
      puts("Resposta inválida!\n");
      catalogo = 0;
    }
    else if (selecionar[0] == '3'){
      return 1;
    }
    else if(selecionar[0] == '2'){
      exibe_tutorial3();
       while(1){
         printf("\nDeseja jogar? [S/N]: ");
         fgets(tutorial,sizeof(tutorial),stdin);
         if (strlen(tutorial) == 2 && tutorial[0] == 'n' || tutorial[0] == 'N'){
           return 1;
         }
         else if (strlen(tutorial) == 2 && tutorial[0] == 's' || tutorial[0] == 'S'){
           catalogo = 1;
           break;
         }
         else{
           puts("Resposta inválida!");
         }
       }
     }
     else if (selecionar[0] == '1'){ // inicio do jogo
       quantidade_numeros_rodada = 2;
       rodada = 1;
       acerto = 0;
       erro = 0;
       puts("\nComeçando o jogo...\nAdivinhe a operação matemática!\n");
       while (rodada < 11){
         printf("RODADA %d\n\n", rodada);
         seleciona_operacao = gera_numeros(1,4);
         if (seleciona_operacao[0] == 1){     
           numero_conforme_rodada(&rodada,&numero1,&numero2,&numero3,&numero4);
           if (rodada <= 3){
             resultado = numero1[0] + numero2[0];
             printf("%d(?)%d = %.0f\n\n", numero1[0], numero2[0], resultado);
           }
           else{
             calculo(&resultado, numero1, numero2, numero3, seleciona_operacao, numero4, &rodada);
           }          
           resposta_usuario[0] = verifica_resposta();
           if (resposta_usuario[0] == '+'){
             puts("Resposta correta!\n");
             acerto++;
           }
           else{
             puts("Você errou! A resposta correta era +\n");
             erro++;
           }
         }   
         if (seleciona_operacao[0] == 2){
            numero_conforme_rodada(&rodada,&numero1,&numero2,&numero3,&numero4);
           if (rodada <= 3){
              resultado = numero1[0] - numero2[0];
              printf("%d(?)%d = %.0f\n\n", numero1[0], numero2[0], resultado);
            }
            else{
              calculo(&resultado, numero1, numero2, numero3, seleciona_operacao, numero4, &rodada);
            }       
            resposta_usuario[0] = verifica_resposta();
            if (resposta_usuario[0] == '-'){
              puts("Resposta correta!\n");
              acerto++;
            }
            else{
              puts("Você errou! A resposta correta era -\n");
              erro++;
            }
          }
         if (seleciona_operacao[0] == 3){
            numero_conforme_rodada(&rodada,&numero1,&numero2,&numero3,&numero4);
           if (rodada <= 3){
             resultado = numero1[0] * numero2[0];
             printf("%d(?)%d = %.0f\n\n", numero1[0], numero2[0], resultado);
           }
           else{
             calculo(&resultado, numero1, numero2, numero3, seleciona_operacao, numero4, &rodada);
           }             
           resposta_usuario[0] = verifica_resposta();
           if (resposta_usuario[0] == '*'){
             puts("Resposta correta!\n");
             acerto++;
           }
           else{
             puts("Você errou! A resposta correta era *\n");
             erro++;
           }
         }
         if (seleciona_operacao[0] == 4){
            numero_conforme_rodada(&rodada,&numero1,&numero2,&numero3,&numero4);
           if (rodada <= 3){
              resultado = (float)numero1[0] / (float)numero2[0];
              printf("%d(?)%d = %.1f\n\n", numero1[0], numero2[0], resultado);
            }
            else{
              calculo(&resultado, numero1, numero2, numero3, seleciona_operacao, numero4, &rodada);
            }           
           resposta_usuario[0] = verifica_resposta();
           if (resposta_usuario[0] == '/'){
             puts("Resposta correta!\n");
             acerto++;
           }
           else{
             puts("Você errou! A resposta correta era /\n");
             erro++;
           }
         }
         rodada++;
         printf("Acertos: %d\nErros: %d\n",acerto, erro);
         strcpy(continuar, "0"); // reseta a variavel
         if (rodada <= 10){
           while (1) {
               puts("\nPressione ENTER para continuar...");
               fgets(continuar, sizeof(continuar), stdin);
               if (continuar[0] == '\n') {
                   break;
               }
           }
         }
       }
        printf("\nNota: %d", acerto);
       if (acerto == 10){ // se acertar tudo ganha 3 fichas
          puts("\nPARABÉNS GÊNIO DA MATEMÁTICA! VOCÊ TIROU A MAIOR NOTA!");
          *fichas += 3;
          *pontuacao += 1;
         puts("+3 🪙");
          return 0;
        }
       else if (acerto > 5 && acerto < 10){ // se acertar mais de 5 ganha 2 fichas
         puts("\nPARABÉNS! VOCÊ ALCANÇOU A MÉDIA!");
         *fichas += 2;
         *pontuacao += 1;
         puts("+2 🪙");
         return 0;
       }
       else{ // perde uma ficha...
         puts("\nVOCÊ NÃO ALCANÇOU A MÉDIA. NÃO DESISTA!");
         *fichas -= 1;
         puts("-1 🪙");
          return 0;
       }
     }
  }
}
void leitura_binaria(Cadastro *usuarios, int *conteudo_binario){
 int numbers0[15], numbers1[15],  numbers2[15],  numbers3[15], numbers4[15], numbers5[15]; // array que armazena os numeros lidos do arquivo binario
 FILE *file3; // LE O BINARIO E ARMAZENA OS VALORES NO VETOR
 file3 = fopen("numbers.bin", "rb");
 if (file3 == NULL) {
     perror("Erro ao abrir a pasta");    
 }
  size_t result0 = fread(numbers0, sizeof(int), 15, file3);
  size_t result1 = fread(numbers1, sizeof(int), 15, file3);
  size_t result2 = fread(numbers2, sizeof(int), 15, file3);
  size_t result3 = fread(numbers3, sizeof(int), 15, file3);
  size_t result4 = fread(numbers4, sizeof(int), 15, file3);
  size_t result5 = fread(numbers5, sizeof(int), 15, file3);
  
  if (result0 != 15 || result1 != 15 || result2 != 15 || result3 != 15 || result4 != 15 || result5 != 15) {
    *conteudo_binario = 0; 
  }
  for (int i = 0; i < 15; i++) {
    // printf("Ficha %d: %d\n", i + 1, numbers0[i]);
    // printf("NumberV1 %d: %d\n", i + 1, numbers1[i]);
    // printf("NumberV2 %d: %d\n", i + 1, numbers2[i]);
    // printf("NumberV3 %d: %d\n", i + 1, numbers3[i]);
    // puts("");
    usuarios[i].ficha = numbers0[i];
    usuarios[i].vitoria1 = numbers1[i];
    usuarios[i].vitoria2 = numbers2[i];
    usuarios[i].vitoria3 = numbers3[i];
    usuarios[i].vitoria4 = numbers4[i];
    usuarios[i].vitoria5 = numbers5[i];
 }
 fclose(file3);
}

void escritura_binaria(Cadastro *usuarios){  
  int numbers0[15], numbers1[15],  numbers2[15],  numbers3[15], numbers4[15], numbers5[15], i;   
  FILE *escreve2 = fopen("numbers.bin", "wb");
    for (i = 0; i < 15; i++){
      numbers0[i] = 10;
      numbers1[i] = 0;
      numbers2[i] = 0;
      numbers3[i] = 0;
      numbers4[i] = 0;
      numbers5[i] = 0;
      
      usuarios[i].ficha = 10;
      usuarios[i].vitoria1 = 0;
      usuarios[i].vitoria2 = 0;
      usuarios[i].vitoria3 = 0;
      usuarios[i].vitoria4 = 0;
      usuarios[i].vitoria5 = 0;
    }
    fwrite(numbers0, sizeof(int), 15, escreve2);
    fwrite(numbers1, sizeof(int), 15, escreve2);
    fwrite(numbers2, sizeof(int), 15, escreve2);
    fwrite(numbers3, sizeof(int), 15, escreve2);  
    fwrite(numbers4, sizeof(int), 15, escreve2);
    fwrite(numbers5, sizeof(int), 15, escreve2); 
  fclose(escreve2);    
}

void atualiza_binario(Cadastro *usuarios){
  int numbers0[15], numbers1[15],  numbers2[15],  numbers3[15], numbers4[15], numbers5[15], i;
  FILE *file2; 
  for (i = 0; i < 15; i++){
    numbers0[i] = usuarios[i].ficha;
    numbers1[i] = usuarios[i].vitoria1;
    numbers2[i] = usuarios[i].vitoria2;
    numbers3[i] = usuarios[i].vitoria3; 
    numbers4[i] = usuarios[i].vitoria4;
    numbers5[i] = usuarios[i].vitoria5;
  }  
  file2 = fopen("numbers.bin", "wb"); 
  if (file2 == NULL) {
    perror("Erro ao abrir o arquivo");  
  }  
  fwrite(numbers0, sizeof(int), 15, file2);
  fwrite(numbers1, sizeof(int), 15, file2);
  fwrite(numbers2, sizeof(int), 15, file2);
  fwrite(numbers3, sizeof(int), 15, file2);  
  fwrite(numbers4, sizeof(int), 15, file2);
  fwrite(numbers5, sizeof(int), 15, file2); 
  fclose(file2);
}

int duelo_cartas(int *fichas, int *pontuacao){

  int catalogo = 1, i, rodada = 1, comeco = 1, opcao_carta_user, opcao_casa, vitoria_user = -1;
  float resultado;
  char selecionar[10], tutorial[10],continuar[10], verbo_atk[25], verbo_def[25];
  int *numeros_user, *numeros_casa;
  Carta cartas_user[5], cartas_casa[5], nova_carta;
  int ponto_user[3] = {0, 0, 0};
  int ponto_casa[3] = {0, 0, 0}; // [0] = ponto de agua, [1] = ponto de fogo, [2] = ponto de neve
  while(1){
    if (catalogo == 1){
      puts("\n1. Jogar");
      puts("2. Como jogar? (Recomendado)");
      puts("3. Voltar\n");
    }
    printf("Digite a opção desejada: ");
    fgets(selecionar,sizeof(selecionar),stdin);           
    if (selecionar[0] != '1' && selecionar[0] != '2' && selecionar[0] != '3' || strlen(selecionar) > 2){
      puts("Resposta inválida!\n");
      catalogo = 0;
    }
    else if (selecionar[0] == '3'){
      return 1;
    }
    else if(selecionar[0] == '2'){
       exibe_tutorial4();
       while(1){
         printf("\nDeseja jogar? [S/N]: ");
         fgets(tutorial,sizeof(tutorial),stdin);
         if (strlen(tutorial) == 2 && tutorial[0] == 'n' || tutorial[0] == 'N'){
           return 1;
         }
         else if (strlen(tutorial) == 2 && tutorial[0] == 's' || tutorial[0] == 'S'){
         catalogo = 1;
         break;
         }
        else{
           puts("Resposta inválida!");
        }
      }
    }
    else if (selecionar[0] == '1'){
      numeros_user = gera_numeros(5,8);
      numeros_casa = gera_numeros(5,8);
      for (i = 0; i < 5; i++){  // monta o deck user
        int repetida = 0;
        nova_carta = criar_carta(numeros_user[i]); 
        for (int j = 0; j < i; j++){
            if (strcmp(cartas_user[j].nome, nova_carta.nome) == 0){ // verifica se a carta ja esta no deck
              repetida = 1;
              break;
            }
        }
        if (repetida == 0){
          cartas_user[i] = nova_carta; // adiciona a carta no deck
        }
        else{
          i--; // se ja estiver no deck, o indice continua o mesmo!!
        }
      }
      for (i = 0; i < 5; i++){ // mesmo procedimento mas para o deck da casa
        int repetida = 0;
        nova_carta = criar_carta(numeros_casa[i]); 
        for (int j = 0; j < i; j++){
            if (strcmp(cartas_casa[j].nome, nova_carta.nome) == 0){
              repetida = 1;
              break;
            }
        }
        if (repetida == 0){
          cartas_casa[i] = nova_carta;
        }
        else{
          i--;
        }
      }
      srand(time(NULL)); // o programa gera a escolha de carta aleatoria diretamente nessa funcao
      while(1){
        strcpy(continuar,"pause"); // utilizada para pausar o output
        if (comeco == 1){
          puts("\nRodada inicial");
          puts("As cartas foram distribuidas... Iniciem a PARTIDA!\n");
          comeco = 0;
        }
        else{
          printf("Rodada %d\n\n", rodada);
        }
        puts("Seu deck:");
        for (i = 0; i < 5; i++){
          if (cartas_user[i].nivel != 8){
            printf("%d. %-15s %s (Nvl %d)\n",i+1,cartas_user[i].nome, cartas_user[i].elemento, cartas_user[i].nivel);
          }
          else{
            printf("%d. %-15s %s (LEGENDARY)\n",i+1,cartas_user[i].nome, cartas_user[i].elemento);

          }
        }       
        if (rodada > 1){
           if (nova_carta.nivel != 8){
              printf("\nNew! '%s' %s (Nvl %d)\n", nova_carta.nome, nova_carta.elemento, nova_carta.nivel);
           }
          else{
          printf("\nNew! '%s' %s (LEGENDARY)\n", nova_carta.nome, nova_carta.elemento);
          }
        }
        opcao_carta_user = verifica_input2();
        opcao_casa =  rand() % 5 + 1;
        if (rodada % 2 == 1){
          if (cartas_user[opcao_carta_user-1].nivel != 8){
            printf("\nVocê %s a carta '%s' (%s Nvl %d)\n", verbo_ataque(),cartas_user[opcao_carta_user-1].nome,cartas_user[opcao_carta_user-1].elemento,cartas_user[opcao_carta_user-1].nivel);
          }
          else{
             printf("\nVocê %s a carta '%s' (%s MAX)\n", verbo_ataque(),cartas_user[opcao_carta_user-1].nome,cartas_user[opcao_carta_user-1].elemento);
          }
          if (cartas_casa[opcao_casa-1].nivel != 8){
            printf("\nA casa %s a carta '%s' (%s Nvl %d)\n",verbo_defesa(),cartas_casa[opcao_casa-1].nome,cartas_casa[opcao_casa-1].elemento,cartas_casa[opcao_casa-1].nivel); 
          }
          else{
             printf("\nA casa %s a carta '%s' (%s MAX)\n",verbo_defesa(),cartas_casa[opcao_casa-1].nome,cartas_casa[opcao_casa-1].elemento); 
          }
        }
        //                          intercala os VERBOS e ATAQUE/DEFESA!
        else{
          if (cartas_casa[opcao_casa-1].nivel != 8){
            printf("\nA casa %s a carta '%s' (%s Nvl %d)\n",verbo_ataque(),cartas_casa[opcao_casa-1].nome,cartas_casa[opcao_casa-1].elemento,cartas_casa[opcao_casa-1].nivel);
          }
          else{
             printf("\nA casa %s a carta '%s' (%s MAX)\n",verbo_ataque(),cartas_casa[opcao_casa-1].nome,cartas_casa[opcao_casa-1].elemento);
          }
          if (cartas_user[opcao_carta_user-1].nivel != 8){
            printf("\nVocê %s a carta '%s' (%s Nvl %d)\n", verbo_defesa(),cartas_user[opcao_carta_user-1].nome,cartas_user[opcao_carta_user-1].elemento,cartas_user[opcao_carta_user-1].nivel);
          }
          else{
            printf("\nVocê %s a carta '%s' (%s MAX)\n", verbo_defesa(),cartas_user[opcao_carta_user-1].nome,cartas_user[opcao_carta_user-1].elemento);
          }
        }
      //                                 verifica quem venceu a rodadada 
        if (strcmp(cartas_user[opcao_carta_user - 1].elemento, "💧") == 0 && strcmp(cartas_casa[opcao_casa - 1].elemento, "🔥") == 0) {        
          ponto_user[0] += 1;
        } 
        else if (strcmp(cartas_user[opcao_carta_user - 1].elemento, "🔥") == 0 && strcmp(cartas_casa[opcao_casa - 1].elemento, "❄️ ") == 0) {
          ponto_user[1] += 1;
        } 
        else if (strcmp(cartas_user[opcao_carta_user - 1].elemento, "❄️ ") == 0 && strcmp(cartas_casa[opcao_casa - 1].elemento, "💧") == 0) {
          ponto_user[2] += 1;
        }
        else if (strcmp(cartas_user[opcao_carta_user - 1].elemento, cartas_casa[opcao_casa - 1].elemento) == 0){
          if (cartas_user[opcao_carta_user - 1].nivel > cartas_casa[opcao_casa - 1].nivel){
            if(strcmp(cartas_user[opcao_carta_user - 1].elemento, "💧") == 0){ // verificacao de ponto do elemento
              ponto_user[0] += 1;
            }
            else if(strcmp(cartas_user[opcao_carta_user - 1].elemento, "🔥") == 0){
              ponto_user[1] += 1;
            }
            else{
              ponto_user[2] += 1;
            }
          }
          else if(cartas_user[opcao_carta_user - 1].nivel < cartas_casa[opcao_casa - 1].nivel){
            if(strcmp(cartas_casa[opcao_casa - 1].elemento, "💧") == 0){ // verificacao de ponto do elemento
              ponto_casa[0] += 1;
            }
            else if(strcmp(cartas_casa[opcao_casa - 1].elemento, "🔥") == 0){
              ponto_casa[1] += 1;
            }
            else{
              ponto_casa[2] += 1;
            }
          }
          else{
            puts("\nEMPATE NA RODADA. AMBOS OS LADOS JOGARAM A MESMA CARTA!");
          }
        }
        else{
          if(strcmp(cartas_casa[opcao_casa - 1].elemento, "🔥") == 0){
            ponto_casa[1] += 1;
          }
          if(strcmp(cartas_casa[opcao_casa - 1].elemento, "❄️ ") == 0){
            ponto_casa[2] += 1;
          }
          if(strcmp(cartas_casa[opcao_casa - 1].elemento, "💧") == 0){
            ponto_casa[0] += 1;
          }
        }
        while (1) { // ATUALIZA NOVA CARTA DA CASA
          int repetida = 0;
          numeros_casa = gera_numeros(1, 8);
          nova_carta = criar_carta(numeros_casa[0]);
          for (int j = 0; j < 5; j++) {
              if (strcmp(cartas_casa[j].nome, nova_carta.nome) == 0) {
                  repetida = 1;
                  break;
              }
          }
          if (repetida == 0) {
              cartas_casa[opcao_casa - 1] = nova_carta;
              break;
          }
        }   
        while (1) { // ATUALIZA A NOVA CARTA DO USER
          int repetida = 0;
          numeros_user = gera_numeros(1, 8);
          nova_carta = criar_carta(numeros_user[0]);
          for (int j = 0; j < 5; j++) {
              if (strcmp(cartas_user[j].nome, nova_carta.nome) == 0) {
                  repetida = 1;
                  break;
              }
          }
          if (repetida == 0) {
              cartas_user[opcao_carta_user - 1] = nova_carta; 
              break; 
          }
        }
        while (1) {
          puts("\nPressione ENTER para continuar...");
          fgets(continuar, sizeof(continuar), stdin);
          if (continuar[0] == '\n') {
             break; 
          }
        }  
        rodada++;
        puts("💧| 🔥 | ❄️  |");
        printf("%d | %2d | %2d | Você\n", ponto_user[0], ponto_user[1], ponto_user[2]);
        printf("%d | %2d | %2d | Casa\n\n", ponto_casa[0], ponto_casa[1], ponto_casa[2]);
        verifica_pontuacao(ponto_user,ponto_casa,&vitoria_user);
        if (vitoria_user != -1){ // alguem alcancou a pontuacao
          break;
        }
      }
      if (vitoria_user == 1){ // 1 = vitoria user, 0 = derrota user
        puts("+2 🪙");
        *fichas += 2;
        *pontuacao += 1;
      }
      else{
        *fichas -= 1;
        puts("-1 🪙");
      }
      return 0;
      free(numeros_user); // liberando espaco...
      free(numeros_casa);
    }
  }  
}

Carta criar_carta(int nivel) {
  Carta nova_carta;
  nova_carta.nivel = nivel;
  int *elemento;

  elemento = gera_numeros(1,3);
  if (elemento[0] == 1) { // Água
    strcpy(nova_carta.elemento, "💧");
    switch (nivel) {
        case 1: strcpy(nova_carta.nome, "Chuva dourada"); break;
        case 2: strcpy(nova_carta.nome, "Chupisco"); break;
        case 3: strcpy(nova_carta.nome, "Pacu"); break;
        case 4: strcpy(nova_carta.nome, "Sabesp"); break;
        case 5: strcpy(nova_carta.nome, "Baleia psíquica pré-histórica"); break;
        case 6: strcpy(nova_carta.nome, "Fred desimpedidos do mar"); break;
        case 7: strcpy(nova_carta.nome, "Geladeira Electrolux"); break;
        case 8: strcpy(nova_carta.nome, "Câncer d'água"); break;
        default: break;
    }
  } else if (elemento[0] == 2) { // Fogo
    strcpy(nova_carta.elemento, "🔥");
    switch (nivel) {
        case 1: strcpy(nova_carta.nome, "Fogão"); break;
        case 2: strcpy(nova_carta.nome, "Cachorro quente"); break;
        case 3: strcpy(nova_carta.nome, "Mamagma"); break;
        case 4: strcpy(nova_carta.nome, "Fireball"); break;
        case 5: strcpy(nova_carta.nome, "Peidante de fogo"); break;
        case 6: strcpy(nova_carta.nome, "Smilinguido"); break;
        case 7: strcpy(nova_carta.nome, "Inferno"); break;
        case 8: strcpy(nova_carta.nome, "Calor de Testa"); break;
        default: break;
    }
  } else { // Neve
    strcpy(nova_carta.elemento, "❄️ ");
    switch (nivel) {
        case 1: strcpy(nova_carta.nome, "Neve leve"); break;
        case 2: strcpy(nova_carta.nome, "Cubo de grelo"); break;
        case 3: strcpy(nova_carta.nome, "Sensei da neve"); break;
        case 4: strcpy(nova_carta.nome, "Sentinela gelada"); break;
        case 5: strcpy(nova_carta.nome, "Bola de neve"); break;
        case 6: strcpy(nova_carta.nome, "Fumaça fria"); break;
        case 7: strcpy(nova_carta.nome, "Penguin"); break;
        case 8: strcpy(nova_carta.nome, "Urso hétero"); break;
        default: break;
    }
  }
    return nova_carta;
}

int verifica_input2(){ // so pra n sujar a funcao principal do jogo
  char opcao_carta[10];
  int opcao;
  while (1){
    printf("\nEscolha sua carta: ");
    fgets(opcao_carta,sizeof(opcao_carta),stdin);
    if (strlen(opcao_carta) != 2 || opcao_carta[0] != '1' && opcao_carta[0] != '2' && opcao_carta[0] != '3' && opcao_carta[0] != '4' && opcao_carta[0] != '5'){
      puts("Digite o número da carta!");
    }
    else{
      opcao = atoi(opcao_carta);
      return opcao;
    }
  }
}
char* verbo_ataque() {
     char* verbos_ataque[] = {
        "atacou com",
        "atacou utilizando",
        "lançou",
        "utilizou",
        "conjurou",
        "aplicou um golpe com",
        "liberou poder com",
        "usou"
    };
    int indice = rand() % 8;
    return verbos_ataque[indice]; 
}

char* verbo_defesa() {
     char* verbos_defesa[] = {
        "defendeu com",
        "contra-atacou com",
        "tentou evitar utilizando",
        "bloqueou com",
        "respondeu com",
        "tentou parar com",
        "refletiu com",
        "se protegeu com",
        "buscou se defender com",
        "tentou se defender com"
    };
    int indice = rand() % 10;
    return verbos_defesa[indice];
}


void verifica_pontuacao(int ponto_user[], int ponto_casa[], int *vitoria_user){
   if(ponto_user[0] == 3){
     puts("Fim de partida! Você obteve 3 PONTOS DE ÁGUA!");
     *vitoria_user = 1;
   }
   else if(ponto_user[1] == 3){
     puts("Fim de partida! Você obteve 3 PONTOS DE FOGO!");
     *vitoria_user = 1;
   }
   else if(ponto_user[2] == 3){
     puts("Fim de partida! Você obteve 3 PONTOS DE NEVE!");
     *vitoria_user = 1;
   }
   else if(ponto_user[0] >= 1 && ponto_user[1] >= 1 && ponto_user[2] >= 1){
     puts("Fim de partida! Você obteve 1 PONTO DE CADA ELEMENTO!");
     *vitoria_user = 1;
   }
   if(ponto_casa[0] == 3){
     puts("Fim de partida! A casa conseguiu 3 PONTOS DE ÁGUA!");
     *vitoria_user = 0;
   }
   else if(ponto_casa[1] == 3){
     puts("Fim de partida! A casa fez 3 PONTOS DE FOGO!");
     *vitoria_user = 0;
   }
   else if(ponto_casa[2] == 3){
     puts("Fim de partida! A casa alcançou 3 PONTOS DE NEVE!");
     *vitoria_user = 0;
   }
   else if(ponto_casa[0] >= 1 && ponto_casa[1] >= 1 && ponto_casa[2] >= 1){
     puts("FIM DE PARTIDA! A casa conseguiu 1 PONTO DE CADA ELEMENTO!");
     *vitoria_user = 0;
   }
 }

void exibe_tutorial4(){
  char continuar[10];
  puts("\nCard Duel é um jogo de duelo de cartas, onde você enfrenta a famosa casa em uma batalha estratégica.\n");
  puts("O jogo começa com a distribuição de 5 cartas aleatórias para ambos os lados. A cada rodada, você e a casa escolhem uma carta para duelar.");
  while (1) {
    puts("\nPressione ENTER para continuar lendo...");
    fgets(continuar, sizeof(continuar), stdin);
    if (continuar[0] == '\n') {
       break; 
    }
  } 
  puts("As cartas são divididas em 3 atributos:");
  puts("Nome da carta, elemento e nível de poder.\n");
  puts("Cada elemento vence o outro, sendo assim:");
  puts("Água --> Fogo\nFogo --> Neve\nNeve --> Água\n");
  puts("Se o elemento de uma carta for igual ao outro, o nível de poder é utilizado para determinar o vencedor.");
  puts("Ao início de uma nova rodada, você e a casa recebem uma nova carta, mantendo sempre um deck de 5 cartas.");
  while (1) {
    puts("\nPressione ENTER para continuar lendo...");
    fgets(continuar, sizeof(continuar), stdin);
    if (continuar[0] == '\n') {
       break; 
    }
  } 
  puts("Seu objetivo é vencer o duelo, e você possui 2 maneiras de vencer: fazendo 3 PONTOS com o mesmo elemento ou fazendo no mínimo 1 PONTO com cada elemento.");
  puts("\nObs: Você não recebe uma carta repetida que já esteja no seu deck, mas tem chance de receber uma que pertence ao deck da casa, vice-versa.");
  puts("\n Você recebe 2 fichas por vitória, porém perde 1 ficha por derrota.");
}

int termo(int *fichas, int *pontuacao) {
    char palavras[100][6]; // 100 é o numero maximo de palavras e 6 é o tamanho maximo de cada palavra.
    int num_palavras = 0, indice, n_tentativa = 0;

    // Lê as palavras do arquivo
    FILE* arquivo = fopen("palavras.txt", "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
    }
    while (fgets(palavras[num_palavras], 6, arquivo)) {
        palavras[num_palavras][strcspn(palavras[num_palavras], "\n")] = 0; // Troca o \n por \0
        num_palavras++;
        
    }
    fclose(arquivo);


   
  
    srand(time(NULL));

   
    indice = rand() % num_palavras;
    //printf("Palavra escolhida: %s\n", palavras[indice]);

    if (indice % 2 == 1){
        indice -= 1;
  
    }   
    //printf("Palavra escolhida depois: %s\n", palavras[indice]);
    char* palavra_secreta = palavras[indice];

    char tentativa[20];
    int tamanho_tentativa;
    char resultado[12], tutorial[10], catalogo = 1, selecionar[10];
    while (1){
    if (catalogo == 1){
      puts("\n1. Jogar");
      puts("2. Como jogar? (Recomendado)");
      puts("3. Voltar\n");
    }

      printf("Digite a opção desejada: ");
      fgets(selecionar,sizeof(selecionar),stdin); 
    
      if (selecionar[0] != '1' && selecionar[0] != '2' && selecionar[0] != '3' || strlen(selecionar) > 2){
        puts("Resposta inválida!\n");
        catalogo = 0;
      }
      else if(selecionar[0] == '3'){
        return 1;
      }
      else if(selecionar[0] == '2'){
        exibe_tutorial5();
        while(1){
          printf("\nDeseja jogar? [S/N]: ");
          fgets(tutorial,sizeof(tutorial),stdin);
          if (strlen(tutorial) == 2 && tutorial[0] == 'n' || tutorial[0] == 'N'){
            return 1;
          }
          else if (strlen(tutorial) == 2 && tutorial[0] == 's' || tutorial[0] == 'S'){
            catalogo = 1;
            break;
          }
          else{
            puts("Resposta inválida!");
          }
        }
      }
      else if(selecionar[0] == '1'){
        break;
      }
    }
    
      printf("\nBem-vindo ao Termo, tente adivinhar a palavra secreta.\n");
      
      while (n_tentativa < 6) {
          n_tentativa ++;
          printf("Digite sua tentativa: ");
          fgets(tentativa, sizeof(tentativa), stdin);
          tamanho_tentativa = strlen(tentativa) - 1;
  
          // Verifica se a tentativa tem 5 letras
          if (tamanho_tentativa != 5) {
              printf("A palavra deve ter exatamente 5 letras.\n\n");
              continue;
          }
        else{
  
          tentativa[strcspn(tentativa, "\n")] = 0; //troca o \n por \0
        for (int i = 0; tentativa[i] != '\0'; i++) {
            tentativa[i] = tolower((unsigned char)tentativa[i]);
        }

          // Avalia a tentativa
          int usadas[6] = {0}; // Para controlar letras já avaliadas
          for (int i = 0; i < 5; i++) {
              if (tentativa[i] == palavra_secreta[i]) {
                  resultado[i] = 'C'; // Letra correta e na posição certa
                  usadas[i] = 1; // Marca que essa letra foi usada
              } else {
                  resultado[i] = 'X'; // Presume que a letra não está na palavra
              }
          }
  
          for (int i = 0; i < 5; i++) {
              if (resultado[i] == 'X') {
                  for (int j = 0; j < 5; j++) {
                      if (tentativa[i] == palavra_secreta[j] && !usadas[j]) {
                          resultado[i] = 'O'; // Letra está na palavra, mas na posição errada
                          usadas[j] = 1; // Marca que essa letra foi usada
                          break;
                      }
                  }
              }
          }
  
          resultado[5] = '\0'; // Termina a string de resultado
          for (int i = 0; i < 5; i++){
            if (resultado[i] == 'C'){
              printf("✅");
            }
            else if (resultado[i] == 'O'){
              printf("⚠️ ");
            }
            else{
              printf("❌");
            }
          }
          printf("    (Tentativas restantes: %d)", 6 - n_tentativa);
          //printf("Resultado: %s\n\n", resultado);
        puts("\n");
  
          if (strcmp(tentativa, palavra_secreta) == 0) {
              printf("Parabéns! Você adivinhou a palavra!\n");
              puts("+1 🪙");
              *fichas += 1;
              *pontuacao += 1;
              return 0;
          }
          if (n_tentativa == 6){
            printf("Você perdeu! A palavra era: %s\n", palavra_secreta);
            *fichas -= 1;
            puts("-1 🪙");
            return 0;
            
          }
      }  
    }  
}

void exibe_tutorial5(){
  puts("\nVoce escolheu jogar o TERMO. Termo é um jogo de adivinhação, onde você tem que adivinhar uma palavra de 5 letras, simples, né?");
  puts("\n--Você tem 6 tentativas para acertar a palavra.");
  puts("--A cada tentativa o console que informa se a letra que você digitou está ou não na palavra e se ela está ou não na posição correta.");
  puts("--O símbolo ✅ indica que você a certou a letra na posição correta.");
  puts("--O símbolo ⚠️  indica que a letra que você digitou está na palavra, mas não na posição correta.");
  puts("--O símbolo ❌ indica que a letra que você digitou não está na palavra.");
  puts("\nBoa Jogatina!");
}

void ver_ranking(Cadastro *usuarios, int NV){
  int i, total_vitoria;
  Ranking rank[NV];
  for(i = 0; i < NV; i++){
    strcpy(rank[i].nome, usuarios[i].username);
    total_vitoria = usuarios[i].vitoria1 + usuarios[i].vitoria2 + usuarios[i].vitoria3 + usuarios[i].vitoria4 + usuarios[i].vitoria5;
    rank[i].total_vitoria = total_vitoria;
  }
  ordenar_ranking(rank, NV);
  puts("\n                     RANKING");
  puts("~~~-~~~-~~~-~~~-~~~-~~~-~~~-~~~-~~~-~~~-~~~-~~~-~~~-~~~");
  for (int i = 0; i < NV; i++) {
      printf("TOP %d: %s (%d WINS)\n", i + 1, rank[i].nome, rank[i].total_vitoria);
  }
  puts("~~~-~~~-~~~-~~~-~~~-~~~-~~~-~~~-~~~-~~~-~~~-~~~-~~~-~~~");
}

void ordenar_ranking(Ranking rank[], int n) {
  for (int i = 0; i < n - 1; i++) {        
    for (int j = 0; j < n - i - 1; j++) {
      if (rank[j].total_vitoria < rank[j+1].total_vitoria) { // compara (j + 1 seria o proximo do i)
          Ranking temp = rank[j];        // armazena o elemento atual
          rank[j] = rank[j+1];         // move o prox elemento para a posicao atual
          rank[j+1] = temp;            // coloca o elemento armazenado na prox posicao
      }
    }
  }
}

void meu_perfil(char username[], int fichas, int vitoria1, int vitoria2, int vitoria3, int vitoria4, int vitoria5){
  printf("\nPerfil de %s\n",username);
  printf("%d 🪙\n",fichas);
    puts("       Tabela de Vitórias");
  puts("|---------------------------------|");
  printf("|Adivinhe o número: 🏆 (%dx)       |\n",vitoria1);
  puts("|---------------------------------|");
  printf("|Pedra, papel, tesoura: 🏆 (%dx)   |\n",vitoria2);
  puts("|---------------------------------|");
  printf("|Operação misteriosa: 🏆 (%dx)     |\n",vitoria3);
  puts("|---------------------------------|");
  printf("|Card duel: 🏆 (%dx)               |\n",vitoria4);
  puts("|---------------------------------|");
  printf("|Termo: 🏆 (%dx)                   |\n",vitoria5);
  puts("|---------------------------------|");
}

void guia_moeda(int *ficha){
  char resposta[15], resposta2[15]; strcpy(resposta, "index");
  int vez = 1;
  puts("\n                Guia de Moedas 🪙\n");
  puts("1. Como funciona a moeda?");
  puts("Saldo inicial: Toda conta começa com 10 moedas. Esse é o ponto de partida para você explorar e se divertir com os jogos.");
  puts("Ganhando moeda(s): Cada vitória nos games garante mais moedas para a sua conta, mas saiba que você perde uma moeda se perder no jogo. Você precisa jogar para descobrir em quais jogos você pode obter mais moedas.");
  puts("~~~-~~~-~~~-~~~-~~~-~~~-~~~-~~~-~~~-~~~-~~~-~~~-~~~-~~~\n");
  puts("2. Onde usar as moedas?");
  puts("A moeda pode ser usada na loja para desbloquear pequenas premiações como surpresas ou curiosidades.");
  puts("~~~-~~~-~~~-~~~-~~~-~~~-~~~-~~~-~~~-~~~-~~~-~~~-~~~-~~~\n");
  puts("3. E se eu zerar minhas moedas?");
  puts("Caso você esteja numa situação crítica, você pode receber 10 moedas acertando uma única pergunta.");
  while(strlen(resposta) != 0 && strcmp(resposta, "PERGUNTA") != 0){
    if (vez == 1){
      printf("\nPara isso digite 'PERGUNTA' ou, se quiser continuar, pressione ENTER... ");
      vez = 2;
    }
    else{
      printf("\nDigite 'PERGUNTA' ou pressione ENTER para continuar... ");
    }
    fgets(resposta, sizeof(resposta), stdin);
    resposta[strcspn(resposta, "\n")] = '\0'; // TIRANDO O \n PRA PODER COMPARAR AS SENHAS

  }
  if (strcmp(resposta, "PERGUNTA") == 0){
    puts("");
    while (1){
      printf("Qual a nota do projeto? ");
      fgets(resposta2, sizeof(resposta2), stdin);
      resposta2[strcspn(resposta2, "\n")] = '\0';
      if (strcmp(resposta2, "10") == 0){
        printf("Parabéns! Você ganhou 10 moedas! 🪙\n");
        *ficha += 10;
        break;
      }
      else{
        puts("Incorreto! Tente novamente.\n");
      }
    }
  }  
}

int loja(int *ficha){
  int catalogo = 1;
  char resp[15];
  
  while (1){
    resp[0] = '\0';
    if (catalogo == 1){
      puts("\nBem-vindo à Loja Aleatória! OS ITENS SÃO TOTALMENTE ALEATÓRIOS E TEM CHANCE DE SEREM REPETIDOS!\n");
      catalogo = 0;
    }
    printf("Saldo: %d 🪙\n\n", *ficha);
    puts("1. Curiosidade 🤔 (3 🪙 )");
    puts("2. Desenho 🎨 (5 🪙 )");
    puts("3. Piadinha 😂 (3 🪙 )");
    puts("4. Voltar\n");
    while (1){
      printf("O que deseja comprar? ");
      fgets(resp, sizeof(resp), stdin);
      if (strlen(resp) != 2 || (resp[0] != '1' && resp[0] != '2' && resp[0] != '3' && resp[0] != '4')){
        puts("Resposta inválida!\n");
      }
      else{
        break;
      }
    }
    if (resp[0] == '1'){
      if (*ficha >= 3){
        puts("");
        curiosidade();
        *ficha -= 3;
        if (comprar_novamente() == 0){
          return 0;
        }
      }
      else{
        puts("\nParece que você não possui moedas suficiente! Visite o Guia de Moedas ou vença os jogos para obter mais moedas!");
        return 0;
      }
    }
    else if (resp[0] == '2'){
      if (*ficha >= 5){
        puts("");
        desenho();
        *ficha -= 3;
        if (comprar_novamente() == 0){
          return 0;
        }
      }
      else{
        puts("\nParece que você não possui moedas suficiente! Visite o Guia de Moedas ou vença os jogos para obter mais moedas!");
        return 0;
      }
    }
  }
}

int comprar_novamente(){
  char resp2[15];
  resp2[0] = '\0';
  while (1){
    printf("Deseja comprar mais alguma coisa? [S/N]: ");
    fgets(resp2,sizeof(resp2),stdin);
    if (strlen(resp2) == 2 && resp2[0] == 'S' || resp2[0] == 'N' || resp2[0] == 's' || resp2[0] == 'n'){
      break;
    }
    else{
      puts("Resposta inválida!\n");
    }
  }
  if (resp2[0] == 'n' || resp2[0] == 'N'){
    return 0;
  }
  else{
    return 1;
  }
}

void curiosidade(){
  const char *curiosidades[] = {
    "Os humanos têm mais de 1000 tipos de bactérias na boca. Essas bactérias ajudam na digestão e na proteção contra patógenos. 🦷",
    "O chocolate foi usado como moeda na civilização maia. Os maias e astecas valorizavam tanto o cacau que o usavam para transações comerciais. 🍫",
    "O maior deserto do mundo não é o Saara, mas a Antártica. Embora a Antártica seja coberta de gelo, é considerada um deserto porque recebe muito pouca precipitação. ❄️",
    "As formigas não têm ouvidos. Elas sentem vibrações e sons através de sensores em suas pernas e corpo. 🐜",
    "Os corvos podem viver até 20 anos ou mais. Eles são conhecidos por sua inteligência e habilidades sociais complexas. 🦅",
    "O primeiro programador do mundo foi uma mulher. Ada Lovelace, uma matemática britânica, é considerada a primeira programadora por seu trabalho com a máquina analítica de Charles Babbage na década de 1800. 👩‍💻",
    "O primeiro vírus de computador foi criado em 1986. Chamado de 'Brain', ele foi desenvolvido por dois programadores paquistaneses e tinha como objetivo proteger software contra cópias ilegais. 🦠",
    "A primeira linguagem de programação de alto nível foi a Fortran, criada em 1957. Fortran (Formula Translation) foi desenvolvida para computação científica e ainda é usada em alguns campos hoje. 💻",
    "Existem mais estrelas no universo do que grãos de areia em todas as praias da Terra. Estima-se que haja cerca de 100 bilhões de galáxias, cada uma contendo bilhões de estrelas. 🌠",
    "O maior vulcão do sistema solar é Olympus Mons, em Marte. Ele é três vezes mais alto que o Monte Everest e possui uma base que é mais extensa que o estado do Arizona. 🏔️",
    "Os planetas do sistema solar não são sólidos como pensamos. Júpiter e Netuno, por exemplo, são compostos principalmente de gases e não têm uma superfície sólida como a Terra. 🌪️",
    "Os cientistas acreditam que cerca de 85% do universo é composto de matéria escura, que não emite luz e não pode ser vista diretamente, mas exerce influência gravitacional sobre a matéria visível. 🌑",
    "Os golfinhos têm nomes próprios. Eles usam um tipo de assobio específico para se identificarem, semelhante a como os humanos usam nomes. 🐬",
    "O coração de um polvo tem três corações. Dois corações bombeiam sangue para as brânquias, enquanto o terceiro bombeia para o resto do corpo. 🐙❤️",
    "Os humanos compartilham cerca de 60% do seu DNA com as bananas. Isso mostra como todos os organismos vivos na Terra estão interconectados em algum nível, mesmo que pareçam muito diferentes! 🍌",
    "O coração de uma andorinha bate até 1.000 vezes por minuto. Isso permite que elas sejam extremamente ágeis e rápidas em voo. 🐦",
    "As estrelas-do-mar têm a capacidade de 'comer' através de seus corpos. Elas podem ejetar seu estômago para fora e envolver suas presas, digerindo-as externamente antes de puxar o estômago de volta para o corpo. ⭐",
    "A luz do Sol leva cerca de 8 minutos e 20 segundos para chegar à Terra. Isso significa que quando olhamos para o Sol, estamos vendo a luz que ele emitiu mais de 8 minutos atrás. ☀️",
    "O nome 'C' vem da linguagem anterior chamada 'B'. A linguagem B foi desenvolvida por Ken Thompson e Dennis Ritchie na década de 1960, e quando Ritchie começou a trabalhar em uma nova linguagem que adicionava mais recursos, ele a chamou de 'C', simplesmente porque ela veio depois da linguagem B. Essa escolha de nome é um exemplo da simplicidade e da continuidade no desenvolvimento de linguagens de programação! 🖥️",
  "Cachorro mordido por cobra tem medo de linguiça. 🐍🐶"
  };
  int numero_de_curiosidades = sizeof(curiosidades) / sizeof(curiosidades[0]); // calcula o total
  int aleatorio = rand() % numero_de_curiosidades; // escolhe aleatoriamente
  printf("%s\n\n", curiosidades[aleatorio]);
  puts("                    😱😲😮🤯😳\n");

}

void desenho(){
  const char *desenhos[] = {
      "     .-\"\"\"\"\"-.\n"
      "   .'          '.\n"
      "  /   O      O   \\\n"
      " :           `    :\n"
      " |                |\n"
      " :    .------.    :\n"
      "  \\  '        '  /\n"
      "   '.          .'\n"
      "     '-......-'\n",

  "     ******       ******\n"
    "   **      **   **      **\n"
    "  **        ** **        **\n"
    "  **         ***         **\n"
    "   **                   **\n"
    "    **                 **\n"
    "      **             **\n"
    "        **         **\n"
    "          **     **\n"
    "            ** **\n"
    "              *\n",
    "    / \\__\n"
      "   (    @\\___\n"
      "   /         O\n"
      "  /   (_____/\n"
      " /_____/   U\n",

      "     .--.\n"
      "    |o_o |\n"
      "    |:_/ |\n"
      "   //   \\ \\\n"
      "  (|     | )\n"
      " /'\\_   _/`\\\n"
      " \\___)=(___/\n",

      "   /\\_/\\\n"
      "  ( o.o )\n"
      "   > ^ <\n",
  "   .-\"\"\"\"\"-.\n"
    "  /          \\\n"
    " |   O    O   |\n"
    " |   \\____/   |\n"
    "  \\          /\n"
    "   '-......-'\n",
  "   , _\n"
  "   (o,o)\n"
  "   |)__)  \n"
  "   -\"-\"- \n",
  "        /\\\n"
  "       /  \\\n"
  "      /    \\\n"
  "     /      \\\n"
  "    /        \\\n"
  "   /          \\\n"
  "  /____________\\\n"
  "      |    |\n"
  "      |____|\n",
  "         ccee88oo\n"
  "      C8O8O8Q8PoOb o8oo\n"
  "   dOB69QO8PdUOpugoO9bD\n"
  "  CgggbU8OU qOp qOdoUOdcb\n"
  "    6OuU  /p u gcoUodpP\n"
  "      \\\\//  /douUP\n"
  "        \\\\////\n"
  "          |||    \n"
  "          |||    \n"
  "          |||    \n"
  "          |||    \n"
  "          |||    \n"
  "         /|||\\   \n"
  "        / ||| \\  \n"
  "       /  |||  \\ \n",
  "        \\   |   /\n"
  "          .-'-.\n"
  "     --  /     \\  --\n"
  "        |       |\n"
  "     --  \\     /  --\n"
  "          `-.-'\n"
  "        /   |   \\\n",
  "              __====-_  _-====__\n"
  "          _--^^^#####//      \\#####^^^--_\n"
  "       _-^##########// (    ) \\##########^-_\n"
  "      -############//  |\\^^/|  \\############-\n"
  "    _/############//   (@::@)   \\############\\_\n"
  "   /#############((      \\//      ))#############\\\n"
  "  -###############\\    (oo)    //###############-\n"
  " -#################\\  / '' \\  //#################-\n"
  " -###################\\/  |  \\/###################-\n"
  "  -##################(   |   )##################-\n"
  "   -##################\\  |  //##################-\n"
  "    -##################\\ | //##################-\n"
  "     -##################\\|//##################-\n"
  "      -###################-###################-\n"
  "       -#################-#################-\n"
  "         -###############-###############-\n",
  "         .-.\n"
  "        (o o)\n"
  "        | O |\n"
  "        |   |\n"
  "       _|   |_\n"
  "      /       \\\n"
  "     |         |\n"
  "      \\       /\n"
  "       `-._.-'\n",
  "        , - ~ ~ ~ - ,\n"
  "    , '               ' ,\n"
  "   ,                       ,\n"
  "  ,                         ,\n"
  "  ,                         ,\n"
  "   ,                       ,\n"
  "    ' ,                 , '\n"
  "        ' - , _ _ _ ,  '\n",
  "              _  \n"
  "         _.-' `'-._  \n"
  "      .-'           '-.  \n"
  "    .'                 '.  \n"
  "   /                     \\  \n"
  "  ;                       ;  \n"
  "   \\                     /  \n"
  "    '.                 .'  \n"
  "      '-._         _.-'  \n"
  "          '-.___.-'  \n",
  "          /\\\n"
  "         /  \\\n"
  "        /    \\\n"
  "       /      \\\n"
  "      /________\\\n"
  "     /\\        /\\\n"
  "    /  \\      /  \\\n"
  "   /    \\    /    \\\n"
  "  /      \\  /      \\\n"
  " /________\\/________\\\n",
  "      /\\     /\\\n"
    "     {  `---'  }\n"
    "     {  O   O  }\n"
    "     ~~>  V  <~~\n"
    "      \\  \\|/  /\n"
    "       `-----'____\n"
    "       /     \\    \\_ \n"
    "      {       }\\  )_  )\n"
    "      |  \\_/  |/ /  /  \n"
    "       \\__/  /(_/  \n"
    "         (__/\n",
  "     ______\n"
  "  __//_||__\\___\n"
  " |  _   _     _  |\n"
  "'-(_)-------(_)--'\n",
  "     ,   ,   ,   ,\n"
  "    /|\\ /|\\ /|\\ /|\\\n"
  "   | o o o o o o o |\n"
  "    \\    `-'      /\n"
  "     `-__________-'\n",
  "       .-^-.\n"
  "     .'     '.\n"
  "    /   _ _   \\\n"
  "   /   (o o)   \\\n"
  "   |    \\_/    |\n"
  "   |           |\n"
  "    \\  \\___/  /\n"
  "     '._____.'\n",
      "    /\\\n"
      "   /  \\\n"
      "  /____\\\n"
      "  |    |\n"
      "  |____|\n"
                 // Os desenhos foram retirados do site: https://ascii.co.uk/art
  };
  int desenho_aleatorio = sizeof(desenhos) / sizeof(desenhos[0]); // calcula o total
  int aleatorio = rand() % desenho_aleatorio; // escolhe aleatoriamente
  printf("%s\n\n", desenhos[aleatorio]);
  puts("                  ✨🎨🖌️ 🖼️ ✨\n");
}