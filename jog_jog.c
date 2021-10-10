//ESTE FICHEIRO SERVE PARA OS JOGADORES JOGAREM ENTRE SI
//VAI FAZER DE LIGAÇÃO ENTRE O JOGO DO JOGADOR 1 E O JOGADOR 2


#include "cabecalho.h"

void jogar_jogo(celula **t1, celula **t2, NODE* jog1, NODE* jog2){
    //uma pequena indicação que vão começar a jogar
    system("clear");
    printf("                                                    ##############################\n");
    printf("                                                    # \033[5;37m O JOGO VAI COMEÇAR!!!!!\033[0m   #\n");
    printf("                                                    ##############################\n\n\n\n");




    printf("PRESSIONE ENTER PARA CONTINUAR\n");

    char n;
    while(n != '\n'){
        scanf("%c", &n);
    }
    system("clear");

//--------------------------------------------------------------------------------------------------
   
    //variaveis que vão ser usadas para ler um ENTER
    //para avançar no jogo
    char resolve1;
    char n1;
    char resolve2;
    char n2;
    //--------------------------------------------------------------------------------------------------



    int contador = 0; //numero de jogadas que ja aconteçam, se for par é a vez do jogador 1, se for impar é a vez do jogador 2
    
    //irao ser as coordenadas introduzidas pelo computador
    int x=0;    
    int y=0;
    //--------------------------------------------------------------------------------------------------



    //este while repete enquanto nenhum jogador ganhar
    while(ponto_jogador1 != pontos_gerais && ponto_jogador2 != pontos_gerais){
        
        system("clear");

        if(contador % 2==0){ //vez do jogador 1 jogar
            if(contador>0){ //este if serve para na primeira jogadar nao dar informaçoes (pois ainda ninguem jogou)
                if(tipo_mat == 1)
                    mostrar_mapa(t1);//mostra como ficou o seu mapa depois da jogada do adversário
                else imprimir_quadtree(jog1);

                printf("O jogador 2 atirou na posição (%d, %d) ", x, y);
                
                if(tipo_mat==1)    
                    info_jogada(x, y, t1); //mostra ao jogador onde o seu adversário jogou e o que aconteceu na jogada
                //else info_jogada_quad(x, y, jog1);  

                printf("\n\nPRESSIONE ENTER PARA CONTINUAR.\n");
                char n;
                while(n != '\n'){
                    scanf("%c", &n);
                }
                system("clear");
                n=0;
            }

            if(tipo_mat == 1)
                mostrar_mapa_esc(t1);//mostra onde o jogador já atirou
            else imprimir_quadtree_esc(jog1);


            //O jogador dá as coordenadas onde quer acertar
            labelonde:
            printf("Jogador 1, para onde quer atirar?\n");
            scanf("%d", &x);
            scanf("%d", &y);
            if((x<1 || y<1) || (x>tamanho || y>tamanho)){
                printf("Por favor escolhe coordenadas aceitáveis\n");
                goto labelonde;
            }

            if(tipo_mat ==1){
                if((t2[x-1][y-1].mapa == '2') || (t2[x-1][y-1].mapa == '3')){
                    printf("Já atiras-te nessa posição\n");
                    goto labelonde;
                }
            }
            else{
                if((conteudo_mapas(jog2, x-1, y-1, 0) == '2') || (conteudo_mapas(jog2, x-1, y-1, 0) == '3')){
                    printf("Já atiras-te nessa posição\n");
                    goto labelonde;
                }
            }
            //--------------------------------------------------------------------------------------------------
            //altera as celulas dos jogadores conforme a jogada
            //indica o que aconteceu nessa jogada
            if(tipo_mat == 1)//mostra como ficou o seu mapa depois da jogada do adversário
                joga_jogador1(t1, t2, x, y);
            else {
                jog1 = joga_jogador1_quad(jog1, jog2, x, y); //erro minimo
                system("clear");
                imprimir_quadtree_esc(jog1);
                jog2 = atualizar_cell2(jog2, x, y);           
            //--------------------------------------------------------------------------------------------------

            
            printf("PRESSIONE ENTER PARA O JOGADOR 2 PODER JOGAR.\n");
            scanf("%c", &resolve1);
            
            while(n1 != '\n'){
                scanf("%c", &n1);
            }
            
            system("clear");
            n1 = '0';
            
        }
         }
        else if(contador % 2==1){ //vez do jogador 2
            
            if(tipo_mat == 1)
                mostrar_mapa(t2);  //mostra como ficou o seu mapa depois da jogada do adversário
            else imprimir_quadtree(jog2);

            printf("O jogador 1 atirou na posição (%d, %d) ", x, y);
            
            if(tipo_mat ==1)
                info_jogada(x, y, t2); //mostra ao jogador onde o seu adversário jogou e o que aconteceu na jogada
            //else info_jogada_quad(x, y, jog2);

            printf("\n\nPRESSIONE ENTER PARA CONTINUAR.\n");
            scanf("%c", &resolve2);
            char n;
            while(n != '\n'){
                scanf("%c", &n);
            }
            system("clear");
            n=0;
            

            if(tipo_mat == 1)
                mostrar_mapa_esc(t2);//mostra onde o jogador já atirou
            else
                imprimir_quadtree_esc(jog2);

            //O jogador dá as coordenadas onde quer acertar
            labelonde1:
            printf("Jogador 2, para onde quer atirar?\n");
            scanf("%d", &x);
            scanf("%d", &y);
            if((x<1 || y<1) || (x>tamanho || y>tamanho)){
                printf("Por favor escolhe coordenadas aceitáveis\n");
                goto labelonde1;
            }

            if(tipo_mat ==1){
                if((t2[x-1][y-1].mapa == '2') || (t2[x-1][y-1].mapa == '3')){
                    printf("Já atiras-te nessa posição\n");
                    goto labelonde;
                }
            }
            else{
                if((conteudo_mapas(jog1, x-1, y-1, 0) == '2') || (conteudo_mapas(jog1, x-1, y-1, 0) == '3')){
                    printf("Já atiras-te nessa posição\n");
                    goto labelonde;
                }
            }
            //--------------------------------------------------------------------------------------------------


            //altera as celulas dos jogadores conforme a jogada
            //indica o que aconteceu nessa jogada
            if(tipo_mat == 1)//mostra como ficou o seu mapa depois da jogada do adversário
                    joga_jogador2(t1, t2, x, y);
            else {
                jog2 = joga_jogador2_quad(jog1, jog2, x, y);
                system("clear");
                imprimir_quadtree_esc(jog2);
                jog1 = atualizar_cell1(jog1, x, y);
            }
            //--------------------------------------------------------------------------------------------------


            
            printf("PRESSIONE ENTER PARA O JOGADOR 1 PODER JOGAR.\n");
            scanf("%c", &resolve2);
            while(n2 != '\n'){
                scanf("%c", &n2);
            }
            system("clear");
            n2 = '0';
            
        }

        contador++;
    }


    printf("\033[0;91m"); //meter a cor do output a vermelho



    //avisa que o jogador 1 ganhou
    if(ponto_jogador1 == pontos_gerais){
        system("clear");
        printf("\n\n\n\n\n\n");
    printf("\n");
    printf("                                                        ################################\n");
    printf("                                                        #                              #\n");
    printf("                                                        #          O JOGADOR 1         #\n");
    printf("                                                        #             GANHOU           #\n");
    printf("                                                        #                              #\n");
    printf("                                                        ################################\n");
    printf("\n");
    }
    //--------------------------------------------------------------------------------------------------



    //avisa que o jogador 2 ganhou
    if(ponto_jogador2 == pontos_gerais){
        system("clear");
              printf("\n\n\n\n\n\n");
    printf("\n");
    printf("                                                        ################################\n");
    printf("                                                        #                              #\n");
    printf("                                                        #          O JOGADOR 2         #\n");
    printf("                                                        #             GANHOU           #\n");
    printf("                                                        #                              #\n");
    printf("                                                        ################################\n");
    printf("\n");
    }


    printf("\033[0m"); //reset à cor do output
    

}
