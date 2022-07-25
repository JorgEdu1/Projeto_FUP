#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

int indice_perf, indice_jog1, indice_jog2, n = 0, n2 = 0;

player * jogadores = 0;
stats * status = 0;
char jogo[3][3];

player * insert_player(player *jogadores, int *n, player novo) {

    //inserindo players com alocaçao dinamica no vetor de estrutura de players

  jogadores = (player * ) realloc(jogadores, ( *n+1) * sizeof(player));

  if (jogadores == 0) {

    printf
      ("\nERRO: nC#o foi possivel criar jogadores, feche o jogo e tente outra vez");

    return 0;

  }

  jogadores[*n] = novo;

  (*n)++;

  return jogadores;

}

stats * insert_stats(stats *status, int *n2, stats dados_novos) {

     //inserindo estatisticas com alocaçao dinamica no vetor de estrutura de stats

  status = (stats * ) realloc(status, ( * n2 + 1) * sizeof(stats));

  if (status == 0) {

    printf("\nERRO: nC#o foi possivel criar status do jogador, feche o jogo e tente outra vez");

    return 0;

  }

  status[ * n2] = dados_novos;

  ( * n2) ++;

  return status;

}

void save_player(player *jogadores, int *n) {

    //salvando o vetor de estrutura de player no arquivo

  FILE *f = fopen("jogadores.txt", "w"); 

  if (f == 0) {

    printf("ERRO ao abrir o arquivo");

    return;

  }

  for (int i = 0; i < *n; i++) {

    fprintf(f, "%s\n%d\n", jogadores[i].nome, jogadores[i].id);

  }

  fclose(f);

}

void load_player() {

    //carregando o vetor de players com o que ha dentro do arquvivo

  FILE *f = fopen("jogadores.txt", "r"); 

  if (f == 0) {

    printf("ERRO ao abrir o arquivo");

    return;

  }

  player novo;

  while (fscanf(f, "%s\n%d\n", novo.nome, & novo.id) == 2) {
  
    jogadores = insert_player(jogadores, &n, novo);

  }

  fclose(f);

}

player create_player() {

    //cria uma variavel player que posteriormente sera enviada para funçao insert_player, para ser inserida no vetor de player

  player a;
  int check_boolean = 3;

  printf("Digite o seu nome:\n");
  scanf(" %[^\n]", a.nome);
  printf("Digite o seu id unico:\n");
  do {

    if (check_boolean == 1) {
      printf("ID ja usado, tente outro!\n");
    }

    scanf(" %d", &a.id);

    for (int i = 0; i < n; i++) {

      if (a.id == jogadores[i].id) {

        check_boolean = 1;

      } else {

        check_boolean = 0;

      }

    }

  } while (check_boolean == 1);

  return a;

}

player * remove_player(player * jogadores, int * n, int id) {

    //remove jogadores do vetor de estrutura de players com alocaçao dinamica

  for (int i = 0; i < * n; i++) {

    if (jogadores[i].id == id) {

      jogadores[i] = jogadores[ * n - 1];
      jogadores = (player * ) realloc(jogadores, ( * n - 1) *sizeof(player));

      if (jogadores == 0) {

        printf("ERRO: nao foi possivel remover jogador");
        return 0;

      }

      (*n)--;
      break;

    }

  }

  return jogadores;

}

stats * remove_stats(stats * status, int * n2, int id) {

    //remove estatisticas do vetor de stats com alocaçao dinamica

  for (int i = 0; i < * n2; i++) {

    if (status[i].id == id) {

      status[i] = status[ * n2 - 1];

      status = (stats * ) realloc(status, ( * n2 - 1) * sizeof(stats));

      if (status == 0) {

        printf("ERRO: nao foi possivel remover status do jogador");

        return 0;

      }

      ( * n2) --;

      break;

    }

  }

  return status;

}

void edit_player() {

    //funcao que edita os dados dos jogadores

  printf("\nDigite o numero do perfil que deseja editar:");

  for (int i = 0; i < n; i++) {

    printf("\n%d - %s", i + 1, jogadores[i].nome);

  }

  scanf("\n%d", & indice_perf);
  indice_perf -= 1;
  printf("Digite o novo nome do perfil %s:", jogadores[indice_perf].nome);
  scanf("%s", jogadores[indice_perf].nome);

}

void search_status(stats * status, int * n2) {

    //funcao responsavel para printar as estatisticas de cada players

  int id;
  scanf("%d", & id);

  for (int i = 0; i < *n2; i++) {

    if (id == status[i].id) {

      printf("%s - %d\n", jogadores[i].nome, status[i].id);
      printf("Partidas Jogadas: %d\nVitorias: %d\nDerrotas: %d\nEmpates: %d\n", status[i].cont_game, status[i].cont_win, status[i].cont_loss, status[i].cont_emp);
      break;
    }

  }

}

void startar() {

    //zera a matriz do jogo da velha, caso o usuario decida jogar o jogo novamente

  int i, j;

  for (i = 0; i < 3; i++) {

    for (j = 0; j < 3; j++) {

      jogo[i][j] = ' ';

    }

  }

}

int validar(char letra) {

    //checka se o campo da matriz contem um X ou 0 dentro

  if (letra == 'x' || letra == '0') {

    return 1;

  } else {

    return 0;

  }

}

int validarCoordenada(int x, int y) {

    //valida se a coordenada dada pelo usuario entra dentro da alçada de um jogo da velha : (0 <= x >= 2)

  if (x >= 0 && x < 3) {

    if (y >= 0 && y < 3) {

      return 1;

    }

  }

  printf("\ndigite uma coordenada valida!\n");

  return 0;

}

int position_test(int x, int y) {

    //testa se a posiçao é vazia

  if (jogo[x][y] != 'x' && jogo[x][y] != '0') {

    return 1;

  }

  printf("\nDigite uma coordenada vazia!");
  return 0;

}

int linhas_tester() {

    //testa se a linha tem valores iguaisa

  int i, j, igual = 1;

  for (i = 0; i < 3; i++) {

    for (j = 0; j < 2; j++) {

      if (validar(jogo[i][j]) && jogo[i][j] == jogo[i][j + 1])

        igual++;

    }

    if (igual == 3)

      return 1;

    igual = 1;

  }

  return 0;

}

int colunas_tester() {

    //testa se a coluna tem valores iguais

  int i, j, igual = 1;

  for (i = 0; i < 3; i++) {

    for (j = 0; j < 2; j++) {

      if (validar(jogo[j][i]) && jogo[j][i] == jogo[j + 1][i])

        igual++;

    }

    if (igual == 3)

      return 1;

    igual = 1;

  }

  return 0;

}

int diagPrincipal_tester() {
    
    //testa se a Diagonal Principal tem valores iguais

  int i, igual = 1;

  for (i = 0; i < 2; i++) {

    if (validar(jogo[i][i]) && jogo[i][i] == jogo[i + 1][i + 1])

      igual++;

  }

  if (igual == 3)

    return 1;

  else

    return 0;

}

int diagSecundaria_tester() {

    //testa se a Diagonal Secundaria tem valores iguais

  int i, igual = 1;

  for (i = 0; i < 2; i++) {

    if (validar(jogo[i][3 - i - 1]) && jogo[i][3 - i - 1] == jogo[i + 1][3 - i - 2])

      igual++;

  }

  if (igual == 3)

    return 1;

  else

    return 0;

}

void printar() {

  int lin, col;

  printf("\n\t    0  1  2\n");

  for (lin = 0; lin < 3; lin++) {

    printf("\t%d ", lin);

    for (col = 0; col < 3; col++) {

      if (col < 2)

        printf(" %c |", jogo[lin][col]);

      else

        printf(" %c ", jogo[lin][col]);

    }

    if (lin < 2)

      printf("\n\t   ---------\n");

  }

}

void play() {

  int x, y, valida, jogadas = 0, ganhou = 0, ordem = 1;

  do {

    do {

      printar();

      if (ordem % 2 == 0) {
        printf("\nSua vez %s, marque com um 'X', digite a linha: ", jogadores[indice_jog2].nome);

      } else {

        printf("\nSua vez %s, marque com um '0', digite a linha: ", jogadores[indice_jog1].nome);

      }

      scanf("%d", & x);
      printf("Agora digite a coluna: ");
      scanf("%d", & y);
      valida = validarCoordenada(x, y);

      if (valida == 1){

        valida += position_test(x, y);
        
      }

    }while (valida != 2);

    if (ordem % 2 == 0)

      jogo[x][y] = 'x';

    else

      jogo[x][y] = '0';

    jogadas++;                        
    ordem++;  
    ganhou += linhas_tester();
    ganhou += colunas_tester();
    ganhou += diagPrincipal_tester();
    ganhou += diagSecundaria_tester();

  } while (ganhou == 0 && jogadas < 9);

  printar();

  if (ganhou != 0) {

    if (ordem % 2 == 0) {

      printf("\nParabens. Voce venceu %s!\n", jogadores[indice_jog1].nome);

      status[indice_jog1].cont_game++;
      status[indice_jog2].cont_game++;
      status[indice_jog1].cont_win++;
      status[indice_jog2].cont_loss++;

    } else if (ordem % 2 != 0) {

      printf("\nParabens. Voce venceu %s!\n", jogadores[indice_jog2].nome);

      status[indice_jog1].cont_game++;
      status[indice_jog2].cont_game++;
      status[indice_jog2].cont_win++;
      status[indice_jog1].cont_loss++;

    }

  }

  if (ganhou == 0) {

    printf("\nQue feio. Ninguem venceu!\n\n");
    status[indice_jog1].cont_game++;
    status[indice_jog2].cont_game++;
    status[indice_jog1].cont_emp++;
    status[indice_jog2].cont_emp++;

  }

}

void save_stats(stats *status, int *n2) {

  FILE *x = fopen("status.txt", "w");

  if (x == 0) {

    printf("ERRO ao abrir o arquivo");
    return;

  }

  for (int i = 0; i < *n2; i++) {

    fprintf(x, "%d\n%d\n%d\n%d\n%d\n", status[i].id, status[i].cont_game, status[i].cont_win, status[i].cont_loss, status[i].cont_emp);

  }

  fclose(x);

}

void load_stats() {

  FILE * x = fopen("status.txt", "r");

  if (x == 0) {

    printf("ERRO ao abrir o arquivo");
    return;

  }

  stats novo;
  while (fscanf(x, "%d\n%d\n%d\n%d\n%d\n", & novo.id, & novo.cont_game, & novo.cont_win, & novo.cont_loss, & novo.cont_emp) == 5) {

    status = insert_stats(status, &n2, novo);

  }

  fclose(x);

}

void deletar_perf() {

  printf("\nEscreva o id do jogador para deletar:");

  for (int i = 0; i < n; i++) {

    printf("\n%d - %s", jogadores[i].id, jogadores[i].nome);

  }

  printf("\n");
  int id_delete;
  scanf(" %d", &id_delete);
  jogadores = remove_player(jogadores, & n, id_delete);
  status = remove_stats(status, & n, id_delete);

}

void list_player() {

  printf("ID - Nome");
  for (int i = 0; i < n; i++) {

    printf("\n%d - %s", jogadores[i].id, jogadores[i].nome);

  }
  printf("\n");

}

void fechar_game() {

  save_player(jogadores, &n);
  save_stats(status, &n2);
  free(jogadores);
  free(status);
  exit(n);

}

void menu_principal() {
  
  int escolha;
  do {

    printf("\nBem vindo ao Jogo da Velha\n 1 - Criar Perfil de Jogador\n 2 - Deletar Perfil de Jogador \n 3 - Editar Perfil de Jogador\n 4 - listar Perfis de Jogador\n 5 - Estatisticas\n 6 - Fechar jogo\n 7 - Jogar!\n");
    scanf("%d", &escolha);

    if (escolha == 1) {

     

      player novo = create_player();
      stats dados_novos;
      jogadores = insert_player(jogadores, &n, novo);
      dados_novos.id = novo.id;
      dados_novos.cont_game = 0;
      dados_novos.cont_win = 0;
      dados_novos.cont_loss = 0;
      dados_novos.cont_emp = 0;
      status = insert_stats(status, &n2, dados_novos);

    } else if (escolha == 2) {

      deletar_perf();

    } else if (escolha == 3) {

      edit_player();

    } else if (escolha == 4) {

      list_player();

    } else if (escolha == 5) {

      printf("Escreva o id do jogador para ver as estatisticas dele:\n");
      list_player();
      search_status(status, &n2);

    } else if (escolha == 6) {

      fechar_game();

    } else if (escolha == 7) {

      for (int i = 0; i < n; i++) {

        printf("\n%d - %s", i + 1, jogadores[i].nome);

      }

      printf("\nescolha o perfil do player 1:");
      scanf("%d", &indice_jog1); 
      printf("escolha o perfil do player 2:");
      scanf("%d", &indice_jog2);
      indice_jog1 -= 1;
      indice_jog2 -= 1;

    }

  } while (escolha != 7);

}