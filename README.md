#Plataforma de Jogos (Projeto 2)

Integrantes:
* Danilo Cardoso Pradella (mixsz) - 24.124.069-6
* Felipe Pereira Munerato - 24.124.067-0
* Caue Yusuke Bonets Ohta - 24.124.098-8

Objetivo do Projeto:
Este projeto tem como objetivo fornecer entretenimento ao usuário através de mini jogos, incluindo um sistema de moedas, ranking de pontuação e uma loja com prêmios virtuais.

Arquivos Necessários para Execução
* main.c
* biblioteca.c
* biblioteca.h
* usuario.txt (apenas a criação)
* palavras.txt
* numbers.bin
* .replit
Observação: Caso o programa não execute corretamente, ajuste o arquivo .replit para conter o seguinte:
run = "gcc main.c biblioteca.c -o main && ./main"
language = "c"

Documentação do Projeto - Plataforma de Jogos

Cadastro de Conta
Para o cadastro, o usuário deve inserir:

Username: mínimo de 3 e máximo de 16 caracteres, sem espaços.
Senha: mínimo de 3 dígitos e máximo 16.
Após inserir os dados, o programa solicitará a confirmação:

"S/s" para confirmar e criar a conta.
"N/n" para cancelar e retornar ao menu.
Cada conta é armazenada em dois arquivos: no arquivo TXT (nome e senha do usuário) e no arquivo binário (quantidade de moedas e vitórias de cada jogo). Todos os usuários começam com 10 moedas.

Limite de Contas
É possível criar até 15 contas. Ao tentar exceder esse limite, uma mensagem de erro será exibida.

Login
Após o cadastro, o usuário será redirecionado ao menu principal e poderá acessar sua conta inserindo nome de usuário e senha. O programa prosseguirá apenas se as informações estiverem corretas.

Menu Principal
Após o login, o menu apresenta dez opções, numeradas de 0 a 9, incluindo jogos, informações, uma loja e a opção de sair. Entradas fora desse intervalo são inválidas. As opções são:

1. Adivinhe o Número

Objetivo: Adivinhar o número gerado aleatoriamente.
Níveis de Dificuldade:
1 - Normal (+1 ficha)
2 - Difícil (+2 fichas)
3 - Impossível (+3 fichas)
Outras Opções:
4 - Como jogar? (tutorial)
5 - Voltar (menu principal)

2. Pedra, Papel, Tesoura
Objetivo: Vencer duas rodadas contra o sistema escolhendo entre pedra, papel ou tesoura.
Menu do Jogo:
1 - Jogar
2 - Como jogar? (tutorial)
3 - Voltar (menu principal)

3. Operação Misteriosa
Objetivo: Identificar o operador correto (soma, subtração, multiplicação ou divisão) usado na operação, o jogo aumenta a dificuldade conforme a rodada.
Menu do Jogo:
1 - Jogar
2 - Como jogar? (tutorial)
3 - Voltar (menu principal)

4. Card Duel
Objetivo: Vencer o sistema em um duelo de cartas.
As cartas possuem três elementos e oito níveis, cada uma com um nome único.
O jogo, assim como os outros, fornece um tutorial (recomendado) para jogadores iniciantes pois tem uma lógica um pouco complexa para quem nunca jogou.
Inspirado em um minijogo do Club Penguin.

5. Termo
Objetivo: Adivinhar a palavra de 5 letras escolhida aleatoriamente a partir de um arquivo TXT.
Inspirado no jogo “Termo”.

6. Meu Perfil
Permite ao usuário visualizar seu saldo de fichas e a quantidade de vitórias em cada jogo.

7. Ranking de Vitórias
Exibe, em ordem decrescente, o nome e a quantidade de vitórias de cada usuário, sendo assim uma tabela do primeiro ao último lugar.

8. Loja
Oferece prêmios virtuais e a opção de retornar ao menu:
* Curiosidade
* Desenho
* Humor
Voltar
Observação: As curiosidades foram retiradas do ChatGPT, desenhos do site ASCII Art, e as piadas foram inventadas ou retirada de redes sociais.

9. Guia de Moedas
Explica o funcionamento das moedas.
Inclui uma pergunta opcional para ganhar +10 moedas (sem limite de uso), caso respondida corretamente.

0. Sair
Encerra o programa com a mensagem: Até breve [nome do usuário]!

Informações Adicionais

Formas de Finalizar o Programa:
* Ação "8" (Sair).
* Função de confirmação, caso o input seja "n/N".

Username Único: O sistema impede usernames duplicados, notificando o usuário.

Tutoriais: Cada jogo possui uma função exibe_tutorialX (onde X é o número do jogo) para manter o código principal organizado.

Jogabilidade: O usuário pode jogar independente da quantidade de moedas que possuir. Por exemplo: 
Se o usuário tiver 0 moeda e perder um jogo, ele ficará com -1 moeda. 
A única coisa que ele não conseguirá fazer é receber os prêmios na loja. Porém no Guia de fichas (opção 9) ele poderá receber 10 fichas (sem limite) se responder corretamente a pergunta proposta.
