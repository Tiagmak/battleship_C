
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define COORDX(P)  ((P).x)
#define COORDY(P)  ((P).y)
//os bitmaps de cada tipo de barco
char bitmap3[5][5] = {{'0', '0', '0', '0', '0'}, {'0', '0', '1', '0', '0'}, {'0', '0', '1', '0', '0'}, {'0', '0', '1', '0', '0'}, {'0', '0', '0', '0', '0'}};
char bitmapL[5][5] = {{'0', '0', '0', '0', '0'}, {'0', '0', '1', '0', '0'}, {'0', '0', '1', '0', '0'}, {'0', '0', '1', '1', '0'}, {'0', '0', '0', '0', '0'}};
char bitmap4[5][5] = {{'0', '0', '0', '0', '0'}, {'0', '0', '0', '0', '0'}, {'0', '0', '1', '1', '0'}, {'0', '0', '1', '1', '0'}, {'0', '0', '0', '0', '0'}};
char bitmapT[5][5] = {{'0', '0', '0', '0', '0'}, {'0', '1', '1', '1', '0'}, {'0', '0', '1', '0', '0'}, {'0', '0', '1', '0', '0'}, {'0', '0', '0', '0', '0'}};
char bitmapDef[5][5]={{'0', '0', '0', '0', '0'}, {'0', '0', '0', '1', '0'}, {'0', '1', '1', '1', '0'}, {'0', '0', '1', '0', '0'}, {'0', '0', '0', '0', '0'}};

int pontos_gerais;          //quantos pontos irá haver no total (a soma dos pontos de todos os barcos)
int ponto_jogador1 = 0;     //quantos pontos o jogador 1 tem (quantas vezes acertou num barcos inimigo)
int ponto_jogador2 = 0;     //quantos pontos o jogador 2 tem (quantas vezes acertou num barcos inimigo)
int afundados_do_1 = 0;     //quantos barcos inimigos o jogador 1 afundou
int afundados_do_2 = 0;     //quantos barcos inimigos o jogador 2 afundou
int tamanho;                //dimensões do tabuleiro
int N_B;                    // numero total de barcos
int numero3 = 1;            // numero total de barcos tipo 3
int numeroL = 1;            // numero total de barcos tipo L
int numero4 = 1;            // numero total de barcos tipo 4
int numeroT = 1;            // numero total de barcos tipo T
int numeroDef=1;            // numero total de barcos tipo Def

int tipo_quad = 0;          //  Fica 1 se o jogador quiser jogar com quadtrees
int tipo_mat = 0;           //  Fica 1 se o jogador quiser jogar com matriz


typedef struct barco{
    char bitmap[5][5];      //bitmap do barco
    int linha;              //linha onde esta o centro do bitmap
    int coluna;             //coluna onde esta o centro do bitmap
    int pontos;             //quantos vale o barco (quantidade de '1's que tem)
    int rotacao;            //guarda a rotaçao do barco
    int atingido;           //quantas vezes é que o barco foi atingido
    char tipo;              //qual é o tipo do barco
}barco;


typedef struct{
    char mapa;              //tabuleiro onde o jogador tem os seus barcos, 0 - vazio, 1- barco, 2 - barco atingido, 3 - água
    struct barco *barco1;   //apontador para a struct barco
    int ocupado;            //se a posição do tabuleiros está a ser ocupada por um barco ou não
    char mapa_esc;          //tabuleiro onde mostra onde o jogador acertou, 0 -vazio, 1- água, 2  - barco atingido

} celula;
typedef struct POINT{
    int x;
    int y;
}POINT;



typedef enum {ROOT, LEAF} Tipos;

typedef struct NODE{
    Tipos tipo;
    POINT extremo; //coordenadas do ponto superior direito
    int tamanho;   //indica a largura do nó

    union{
        struct NODE *subs[4]; //subquadrantes de um nó

        struct {
            celula *cell;
            POINT *valor;   //para depois mudar aqui para celula
            int flague;    //para ver se tinha valor ou nao
        }leaf;
    }no;
}NODE;



void preparar_jogo();
void escreve();

// funções usadas pelo preparar jogo
int manual_tabuleiro();
int random_tabuleiro();
void criar_struct(celula**);
void mostrar_mapa(celula **);
void barcos_manual(int );
void barcos_random(int );
void definir_barco_manual();
void definir_barco_random();
void criar_frota(barco** );
NODE* posicionar_barcos_random(NODE*, celula** , barco**, int );
NODE* posicionar_barcos_manual(NODE*, celula** , barco** , int );
void mostrar_mapa_esc(celula **);
void mostrar_bitmap_geral(char[5][5]);

void jogar_jogo(celula **, celula **, NODE* , NODE*);

// funções usadas pelo jogar jogo
void joga_jogador1(celula **, celula **,int, int);
void joga_jogador2(celula **, celula **,int, int);
void info_jogada(int, int , celula** );


NODE* criar_quad(int , int , int);
POINT make_point(int ,int);
NODE * inserir_ponto(NODE*, int , int , barco*);
int qual_quad(NODE*, int , int );
NODE* posicionar_barcos_quad(NODE*, barco** , int , int , int );
void imprimir_quadtree (NODE*  );
int verifica_coor(NODE *, barco**, int, int, int);
void imprimir_quadtree_esc(NODE* );
void info_jogada_quad(int , int, NODE *);
void info_barco(int, int, NODE *);

char conteudo_mapas(NODE* ,int ,int , int);

NODE* joga_jogador1_quad(NODE* , NODE* , int, int);
int pesquisa(NODE* , int, int);
NODE * inserir_ponto_escuro(NODE *, int, int, barco*); 
NODE * inserir_ponto_escuro_acertei(NODE *, int, int, barco*);
NODE* joga_jogador2_quad(NODE* , NODE* , int, int);
NODE* atualizar_cell2(NODE *, int, int);
NODE* atualizar_cell1(NODE *, int, int);


NODE * inserir_ponto_mapa_falhou(NODE *, int, int, barco*);