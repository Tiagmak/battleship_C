//ESTE FICHEIRO É USADO PARA COLOCAR TODAS AS FUNÇÕES UTILIZADAS PELO FICHEIRO jog_jog

#include "cabecalho.h"


//esta função irá modificar as celulas conforme a jogada do jogador 1
void joga_jogador1(celula **t1, celula **t2,int x1, int y1){
    //as coordenadas da jogada do jogador 1
    int x = x1-1;
    int y = y1-1;


    if(t2[x][y].mapa =='0'){
        t2[x][y].mapa ='3';
        t1[x][y].mapa_esc='1';
        mostrar_mapa_esc(t1);
        printf("Acertou em água\n");
        return;
    }

    else if(t2[x][y].mapa =='1'){
        t2[x][y].mapa ='2';
        t2[x][y].barco1 -> atingido++;
        t1[x][y].mapa_esc = '2';
        ponto_jogador1++;
        
        mostrar_mapa_esc(t1);

        printf("Acertou num barco inimigo");
        if(t2[x][y].barco1 -> atingido == t2[x][y].barco1 -> pontos){
            printf(" e ainda o afundou");
            afundados_do_1++;
        }

        printf("\n\n\n\n");

        if(afundados_do_1>0){
            printf("Já afundou %d barcos. Ainda falta afundar %d barcos.\n", afundados_do_1, N_B -afundados_do_1);
        }


    }
}




//esta função irá modificar as celulas conforme a jogada do jogador 2
void joga_jogador2(celula **t1, celula **t2,int x, int y){
    //as coordenadas da jogada do jogador 1
    x--;
    y--;

    if(t1[x][y].mapa =='0'){
        t1[x][y].mapa ='3';
        t2[x][y].mapa_esc='1';
        mostrar_mapa_esc(t2);
        printf("Acertou em água\n");
        return;
    }

    t1[x][y].mapa ='2';
    t1[x][y].barco1 -> atingido++;
    t2[x][y].mapa_esc = '2';
    ponto_jogador2++;
    
    mostrar_mapa_esc(t2);

    printf("Acertou num barco inimigo");
    if(t1[x][y].barco1 -> atingido == t1[x][y].barco1 -> pontos){
        printf(" e ainda o afundou");
        afundados_do_2++;
    }

    printf("\n\n\n\n");
    if(afundados_do_2>0){
            printf("Já afundou %d barcos. Ainda falta afundar %d barcos.\n", afundados_do_2, N_B-afundados_do_2);
        }
}


//esta função dira ao jogador qual foi a jogada que o adversario fez, se acertou num barco ou nao, etc...
void info_jogada(int x1, int y1, celula** jogador){

    //mostra ao jogador se acetou em água
    int x = x1-1;
    int y = y1-1;
    if(jogador[x][y].mapa == '3'){
        printf("e acertou em água.\n");
        return;
    }

    //se o jogador acetrtou num barco
    //mostrará qual foi o tipo de barco que o jogador acertou
    switch(jogador[x][y].barco1 -> tipo) {
        case '3':
            printf("e acertou num barco do tipo 3");
            break;
        case 'L':
            printf("e acertou num barco do tipo L");
            break;
        case '4':
            printf("e acertou num barco do tipo 4");
            break;    //as coordenadas da jogada do jogador 1

        case 'T':
            printf("e acertou num barco do tipo T");
            break;
        default:
            printf("e acertou num barco do tipo Def");
            break;
    }

    //se afundou o barco completa a frase
    if(jogador[x][y].barco1 -> atingido == jogador[x][y].barco1 -> pontos){
        printf(" e afundou o barco.");
    }

    printf("\n");

}
