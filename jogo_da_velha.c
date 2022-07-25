#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

int main() {

  load_player();
  load_stats();

  int op = 3;
  do {

    if (op == 3) {
      menu_principal();
    }

    startar();
    play();
    printf("O que deseja?\n1 - Jogar novamente\n2 - Sair do jogo\n3 - Voltar ao Menu\n");
    scanf("\n%d", &op);

  } while (op == 1 || op == 3);

  fechar_game();

}
