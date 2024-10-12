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
      puts("\n1 - Normal (+1 ficha)");
      puts("2 - Dificíl (+2 fichas)");
      puts("3 - IMPOSSÍVEL (+3 fichas)");
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
            printf("Total de chutes: %d\n\n", 4 - vidas); 
            vitoria = 1;
            *pontuacao += 1;
            break;
          }
        }
      }
      if (vitoria == 0){
        printf("\nQUE PENA! VOCÊ PERDEU!\nO NÚMERO ERA %d :(\n", random[0]);
        *fichas -= 1;
      }
      else{
        *fichas += 1;
        puts("Você recebeu 1 ficha como recompensa!");
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
            printf("Total de chutes: %d\n\n", 5 - vidas);            
            vitoria = 1;
            *pontuacao += 1;
            break;
          }
        }
      }
      if (vitoria == 0){
        printf("\nQUE PENA! VOCÊ PERDEU!\nO NÚMERO ERA %d :(\n", random[0]);
        *fichas -= 1;
      }
      else{
        puts("Você recebeu 2 fichas como recompensa!");
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
            printf("Total de chutes: %d\n\n", 8 - vidas);   
            vitoria = 1;
            *pontuacao += 1;
            break;
          }
        }
      }
      if (vitoria == 0){
        printf("\nQUE PENA! VOCÊ PERDEU!\nO NÚMERO ERA %d :(\n", random[0]);
        *fichas -= 1;
      }
      else{
        *fichas += 3;
        puts("Você recebeu 3 fichas como recompensa!");
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
              while (1){
                printf("PREPARADO PARA A PRÓXIMA RODADA? ");
                fgets(qualquer_coisa,sizeof(qualquer_coisa),stdin);
                if (qualquer_coisa[0] == 's' || qualquer_coisa[0] == 'S'){
                  puts("PRÓXIMA RODADA COMEÇANDO...\n");
                  break;
                }
                else if (qualquer_coisa[0] == 'n' || qualquer_coisa[0] == 'N'){
                  puts("ENTÃO PREPARE-SE! PRÓXIMA RODADA COMEÇANDO...\n");
                  break;
                } 
                else{
                  puts("ISSO NÃO ESTÁ NO MEU VOCABULÁRIO!\n");                     
                }// continuar a logica, falta implementar se o usuario perdeu ou ganhou!
              }
            }
            else{
              if (pt_casa == 2){
                puts("OH NÃO! VOCÊ PERDEU O DUELO!");
                *fichas -= 1;
              }
              else{
                puts("MUITO BEM! VOCÊ GANHOU O DUELO!");
                *fichas += 1;
                *pontuacao += 1;
                puts("Você recebeu 1 ficha como recompensa!");
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
// void binario(Cadastro *usuarios){
//   FILE *file3;
//   int numbers[15], i;
//   for (i = 0; i < 15; i++){
//     numbers[i] = usuarios[i].vitoria1;
//   }
//   file3 = fopen("numbers.bin", "wb"); 
//   if (file3 == NULL) {
//       puts("Erro ao abrir o arquivo 'numbers.bin'!\n");
//   }
//   size_t result = fwrite(numbers, sizeof(int), 15, file3);
//   if (result != 15) {
//     puts("Erro ao abrir o arquivo 'numbers.bin'!\n");
//   }
//   fclose(file3);
  
//    FILE *file4;
  
//    file4 = fopen("numbers.bin", "rb");
//    if (file4 == NULL) {
//      puts("Erro ao abrir o arquivo 'numbers.bin'!\n");
//    }
  
//    size_t result2 = fread(numbers, sizeof(int), 15, file4);
//    if (result2 != 15) {
//      puts("Erro ao abrir o arquivo 'numbers.bin'!\n");
//    } else {
//        for (int i = 0; i < 15; i++) {
//            printf("Number %d: %d\n", i + 1, numbers[i]);
//        }
//    }
  
//    fclose(file4);
// }

// main:

// ///////////////
// FILE *file2;
// int numbers[10];
// for (i = 0; i < 10; i++){
//   numbers[i] = usuarios[i].vitoria1;
// }
// file2 = fopen("numbers.bin", "wb"); 
// if (file2 == NULL) {
//     perror("Error opening file");
//     return 1;
// }
// size_t result = fwrite(numbers, sizeof(int), 10, file2);
// if (result != 10) {
//     perror("Error writing to file");
//     return 1;
// }
// fclose(file2);

//  FILE *file;

//  file = fopen("numbers.bin", "rb");
//  if (file == NULL) {
//      perror("Error opening file");
//      return 1;
//  }

//  size_t result2 = fread(numbers, sizeof(int), 10, file);
//  if (result2 != 10) {
//      perror("Error reading file");
//  } else {
//      for (int i = 0; i < 10; i++) {
//          printf("Number %d: %d\n", i + 1, numbers[i]);
//      }
//  }

//  fclose(file);
// //////////////