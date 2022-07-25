#ifndef FUNCOES_H
#define FUNCOES_H

typedef struct {

    //estrutura usada para criar o vetor de estrutura de players
    char nome[50];
    int id;

}player;

typedef struct {

    //estrutura usada para criar o vetor de estrutura de estatisticas dos players
    int id;
    int cont_game;
    int cont_win;
    int cont_loss;
    int cont_emp;

}stats;

player * insert_player(player * jogadores, int * n, player novo);
stats * insert_stats(stats *status, int *n2, stats dados_novos);
void save_player(player *jogadores, int *n);
void load_player();
player create_player();
player * remove_player(player * jogadores, int * n, int id);
stats * remove_stats(stats * status, int * n2, int id);
void edit_player();
void search_status(stats * status, int * n2);
void startar();
int validar(char letra);
int validarCoordenada(int x, int y);
int position_test(int x, int y);
int linhas_tester();
int colunas_tester();
int diagPrincipal_tester();
int diagSecundaria_tester();
void printar();
void play();
void save_stats(stats *status, int *n2);
void load_stats();
void deletar_perf();
void list_player();
void fechar_game();
void menu_principal();

#endif