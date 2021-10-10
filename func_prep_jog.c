//ESTE FICHEIRO É USADO PARA COLOCAR TODAS AS FUNÇÕES UTILIZADAS PELO FICHEIRO prep_jog

#include "cabecalho.h"
#include <stdlib.h>
#include <time.h>
//esta função mostra o bitmap dos barcos
void mostrar_bitmap_geral(char bitmap[5][5]){
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            printf("%c ", bitmap[i][j]);
        }
        printf("\n");
    }
}

//esta função mostra os tabuleiros dos jogadores
//esta função tambem é usada no ficheiro jog_jog
void mostrar_mapa(celula **t){
    
    //faz a primeira linha de numeros
    printf("\033[0;31m"); //mete a cor do output a vermelho

    //numera as colunas
    int i=1;
    printf("   |");
    for(; i<10; i++){
        printf(" %d |", i);
    }
    for(;i<=tamanho; i++){
        printf(" %d|", i);
    }
    printf("\n");
    printf("\033[0m"); //faz reset à cor do output

    //faz a primeira linha para separar
    for(int barra=0; barra<=tamanho; barra++){
        printf("----");
    }
    printf("\n");

    //corre as linhas e preenche os espaços das celulas
    for(int j=0; j<tamanho; j++){
        //numera as linhas
        int linha = j+1;
        if(linha < 10){
            printf(" \033[0;91m%d\033[0m |", linha);
        }
        else{
            printf("\033[0;91m%d\033[0m |", linha);
        }
        
        //meter os numeros
        for(int k =0; k<tamanho; k++){
            if(t[j][k].mapa == '0'){//mete um zero se a celula tiver vazia
                printf(" %c |", t[j][k].mapa);
            }
            else if(t[j][k].mapa == '1'){//mete um 1 a verde
                printf(" \033[1;92m%c\033[0m |", t[j][k].mapa);
            }
            else if(t[j][k].mapa == '2'){//mete um 2 a vermelho
                printf(" \033[5;91m%c\033[0m |", t[j][k].mapa);
            }
            else if(t[j][k].mapa == '3'){//mete um 3 a azul
                printf(" \033[1;94m%c\033[0m |", t[j][k].mapa);
            }

        }
        printf("\n");
        for(int barra=0; barra<=tamanho; barra++){
            printf("----");
        }
        printf("\n");
    }
    

}

//mostra o mapa às escuras
void mostrar_mapa_esc(celula **t_esc){
     //faz a primeira linha de numeros
    printf("\033[0;31m"); //mete a cor do output a vermelho

    int i=1;
    printf("   |");
    for(; i<10; i++){
        printf(" %d |", i);
    }
    for(;i<=tamanho; i++){
        printf(" %d|", i);
    }
    printf("\n");
    printf("\033[0m"); //faz reset à cor do output


    //faz a primeira barra para separar
    for(int barra=0; barra<=tamanho; barra++){
        printf("----");
    }
    printf("\n");


    //corre as linhas e preenche os espaços das celulas
    for(int j=0; j<tamanho; j++){
        //metes as letras
        int linha = j+1;
        if(linha < 10){
            printf(" \033[0;31m%d\033[0m |", linha);
        }
        else{
            printf("\033[0;31m%d\033[0m |", linha);
        }
        

        //meter os numeros
        for(int k =0; k<tamanho; k++){
            if(t_esc[j][k].mapa_esc == '1'){//mete um 1 a azul
                printf("\033[1;34m %c\033[0m |", t_esc[j][k].mapa_esc);
            }

            else if(t_esc[j][k].mapa_esc == '2'){//mete um 2 a vermelho
                printf("\033[5;31m %c\033[0m |", t_esc[j][k].mapa_esc);
            }
            else{
                printf(" %c |", t_esc[j][k].mapa_esc);
            }

        }
        printf("\n");
        for(int barra=0; barra<=tamanho; barra++){
            printf("----");
        }
        printf("\n");
    }
    
    
}

//esta função irá preencher a struct
void criar_struct(celula** t1){
    for(int j=0; j<tamanho; j++){
        for(int k =0; k<tamanho; k++){
            t1[j][k].mapa = '0';
            t1[j][k].ocupado = 0;
            t1[j][k].mapa_esc = '0';
        }
    }

}



//função para escolher numero random do tabuleiro
int random_tabuleiro(){
    //srand(time(NULL));
    int d;
    d = 20 + rand() % 21;

    return d;
}


//os jogadores escolhem as dimensões do tabuleiro
int manual_tabuleiro(){
    int dim;
    printf("Quais as dimensões que deseja que o tabuleiro tenha?(20 - 40): ");
    scanf("%d",&dim);
    if(dim>=20 && dim<= 40){
        return dim;
    }
    else{ 
        printf("Escolha um tamanho aceitável!\n\n");
        return manual_tabuleiro();
    }
    
}


//função para escolher aleatóriamente o numero de barcos
void barcos_random(int n){
    N_B = 5 + rand() % ((n*n/25)-4);
    printf("Cada jogador ficou com %d barcos.\n\n", N_B);
    
}


//os jogadores escolhem o numero de barcos
void barcos_manual(int n){
    label2:
    printf("Escolha o número de barcos (5 - %d): ", n*n/25);
    scanf("%d", &N_B);
     
    if(N_B < 5 || N_B > n*n/25){
        printf("Escolha uma opção válida!\n\n");
        goto label2;
    }
    
}




//função para definir quantos barcos de cada tipo há
void definir_barco_random(){
    int contador = N_B - 5;//esta variavel vai contanto os barcos que ainda faltam atribuir um tipo
                           //sendo que já há um de cada tipo
    

    //definir quantos barcos sao do tipo 3
    int temporario = rand() % (contador+1);  
    numero3 += temporario;
    contador -= temporario;

    if(contador == 0){
        goto labelfinal2;
    }

    //definir quantos barcos sao do tipo L
    temporario = rand() % (contador+1);  
    numeroL += temporario;
    contador -= temporario;


    if(contador == 0){
        goto labelfinal2;
    }

    //definir quantos barcos sao do tipo 4
    temporario = rand() % (contador+1);  
    numero4 += temporario;
    contador -= temporario;


    if(contador == 0){
        goto labelfinal2;
    }

    //definir quantos barcos sao do tipo T
    temporario = rand() % (contador+1);  
    numeroT += temporario;
    contador -= temporario;


    //para o tipo Def são os restantes
    numeroDef += contador;

    

    labelfinal2:
    printf("Ficaram com %d barcos do tipo 3, %d de barcos do tipo L, ", numero3, numeroL);
    printf("%d barcos do tipo 4, %d barcos do tipo T e %d barcos do tipo Def.\n\n\n\n", numero4, numeroT, numeroDef);
}



//função para definir quantos barcos de cada tipo há, de forma manual
void definir_barco_manual(){

    system("clear");
    printf("5 dos vossos barcos são automaticamente definidos pelo jogo (um barco de cada tipo).\n\n");
    int contador = N_B -5;//esta variavel vai contanto os barcos que ainda faltam atribuir um tipo
                          //sendo que já há um de cada tipo
    
    
    int temporario;
    
    //definir quantos barcos sao do tipo 3
    printf("Já têm 1 barco do tipo 3: \n");
    mostrar_bitmap_geral(bitmap3);

    labeltipo3:
    printf("Quantos mais barcos do tipo 3 querem? Podem ter até mais %d.\n", contador);
    scanf("%d", &temporario);
    if(temporario<0 || temporario> contador){
        printf("Escolham uma opção aceitavél!\n\n\n");
        goto labeltipo3;
    }
    numero3 += temporario;
    contador -= temporario;



    system("clear");
    if(contador==0){//estes if vao ver se todos os barcos a estao atribuidos
        goto labelfinal;
    }

    //definir quantos barcos sao do tipo L
    printf("Já têm 1 barco do tipo L: \n");
    mostrar_bitmap_geral(bitmapL);

    labeltipoL:
    printf("Quantos mais barcos do tipo L querem? Podem ter até mais %d.\n", contador);
    scanf("%d", &temporario);
    if(temporario<0 || temporario> contador){
        printf("Escolham uma opção aceitavél!\n\n\n");
        goto labeltipoL;
    }
    numeroL += temporario;
    contador -= temporario;
    
    system("clear");
    if(contador==0){
        goto labelfinal;
    }

    //definir quantos barcos sao do tipo 4
    printf("Já têm 1 barco do tipo 4: \n");
    mostrar_bitmap_geral(bitmap4);

    labeltipo4:
    printf("Quantos mais barcos do tipo 4 querem? Podem ter até mais %d.\n", contador);
    scanf("%d", &temporario);
    if(temporario<0 || temporario> contador){
        printf("Escolham uma opção aceitavél!\n\n\n");
        goto labeltipo4;
    }
    numero4 += temporario;
    contador -= temporario;
    


    system("clear");
    if(contador==0){
        goto labelfinal;
    }

    //definir quantos barcos sao do tipo T
    printf("Já têm 1 barco do tipo T: \n");
    mostrar_bitmap_geral(bitmapT);

    labeltipoT:
    printf("Quantos mais barcos do tipo T querem? Podem ter até mais %d.\n", contador);
    scanf("%d", &temporario);
    if(temporario<0 || temporario> contador){
        printf("Escolham uma opção aceitavél!\n\n\n");
        goto labeltipoT;
    }
    numeroT += temporario;
    contador -= temporario;

    system("clear");
    if(contador==0){
        goto labelfinal;
    }

    //os restante são os barcos do tipo Def
    numeroDef += contador;
    mostrar_bitmap_geral(bitmapDef);
    printf("Ficaram com %d barcos do tipo Def.\n", numeroDef);

    labelfinal:
    printf("Ficaram com %d barcos do tipo 3, %d barcos do tipo L, ", numero3, numeroL);
    printf("%d barcos do tipo 4, %d barcos do tipo T e %d barcos do tipo Def.\n\n\n\n", numero4, numeroT, numeroDef);
}





// criar as structs dos barcos
// e preenche as variaveis das struct para cada tipo de barcos
void criar_frota(barco** frota){

    for(int i=0; i<N_B; i++){
        frota[i] = (barco*) malloc(sizeof(barco));
    }

    //a partir daqui copiamos os bitmaps dos barcos para as suas structs 
    int corre=0; 
    for(int t3 = 0; t3 < numero3; t3++){//para correr as structs do barco tipo 3
         for(int linhas=0;linhas<5; linhas++){
             for(int colunas=0; colunas<5; colunas++){
                 frota[corre] -> bitmap[linhas][colunas] = bitmap3[linhas][colunas];
             }
         }
         frota[corre] -> pontos = 3;
         frota[corre] -> atingido =0;
         frota[corre] -> tipo = '3';
         corre++;
    }

    for(int tL =0; tL < numeroL; tL++){//para correr as structs do barco tipo L
        for(int linhas=0;linhas<5; linhas++){
             for(int colunas=0; colunas<5; colunas++){
                 frota[corre] -> bitmap[linhas][colunas] = bitmapL[linhas][colunas];
             }
         }
         frota[corre] -> pontos = 4;
         frota[corre] -> atingido =0;
         frota[corre] -> tipo = 'L';
         corre++;
    }

    for(int t4 =0; t4 < numero4; t4++){//para correr as structs do barco tipo 4
        for(int linhas=0;linhas<5; linhas++){
             for(int colunas=0; colunas<5; colunas++){
                 frota[corre] -> bitmap[linhas][colunas] = bitmap4[linhas][colunas];
             }
         }
         frota[corre] -> pontos = 4;
         frota[corre] -> atingido =0;
         frota[corre] -> tipo = '4';
         corre++;
    }

    for(int tT =0; tT < numeroT; tT++){//para correr as structs do barco tipo T
        for(int linhas=0;linhas<5; linhas++){
             for(int colunas=0; colunas<5; colunas++){
                 frota[corre] -> bitmap[linhas][colunas] = bitmapT[linhas][colunas];
             }
         }
         frota[corre] -> pontos = 5;
         frota[corre] -> atingido =0;
         frota[corre] -> tipo = 'T';
         corre++;
    }

    for(int tDef =0; tDef < numeroDef; tDef++){//para correr as structs do barco tipo Def
        for(int linhas=0;linhas<5; linhas++){
             for(int colunas=0; colunas<5; colunas++){
                 frota[corre] -> bitmap[linhas][colunas] = bitmapDef[linhas][colunas];
             }
         }
         frota[corre] -> pontos = 5;
         frota[corre] -> atingido =0;
         frota[corre] -> tipo = 'D';
         corre++;
    }

    
}

// Esta função verifica se no modo matriz as coordenadas que foram dadas pelas funções posicionar_barcos_manual e posicionar_barcos_random
//são válidas. Se não forem retornamos 0, se forem inserimos o barco no tabuleiro na posição indicada e retornamos 1.
int posicionar_barcos_matriz(celula** jogador, barco** frota, int k, int x, int y){
    //verifica se sao coordenadas aceitáveis
    int z=1;
    for(int i= x-1; i<=x+1; i++){
        int u=1;
        for(int j = y-1; j<=y+1; j++){
            if ((i<0 || j<0) || (i>=tamanho || j>= tamanho)){
                printf("\033[3;31mNesta posição o barco sai do mapa.\033[0m\n\n");
                return 0;
            }
            
            if(frota[k] -> bitmap[z][u] == '1'){
                if (i<0 || j<0 || i>=tamanho || j>= tamanho){
                    printf("\033[3;31mNesta posição o barco sai do mapa.\033[0m\n\n");
                    return 0;
                }
            }
            if(jogador[i][j].ocupado == 1 && frota[k] -> bitmap[z][u] == '1'){
                printf("\033[3;31mNão pode ser essa posição pois está demasiado próxima de um barco.\033[0m\n\n");
                return 0;
            }
            u++;
        }
        z++;
    }
    

    frota[k] -> linha = x+1;
    frota[k] -> coluna = y+1;

    
    z=1; //o z vai ser a linha do bitmap
    for(int i= x-1; i<=x+1; i++){
        int u=1;   //o u vai ser a coluna do bitmap
        for(int j = y-1; j<=y+1; j++){
            if ((i<0 || j<0) || (i>=tamanho || j>= tamanho)){
                continue;
            }
            if(frota[k] -> bitmap[z][u] == '1'){
                jogador[i][j].mapa = '1';//passar os 1s do bitmap para o tabuleiro
                jogador[i][j].barco1 = frota[k]; //o apontador barco da celula passa a apontar para a struct da frota
                jogador[i][j].ocupado = 1;
            }
            u++;
        }
        z++;
    }
    return 1;
}

//função recursiva para rodar barcos, rodando 90 graus de cada vez
void rodar_barcos(barco** frota, int numero, int rot){
    int a = 4;
	int b = 0;
    char temp[5][5];
	for(int i = 0; i < 5; i++ ){
		for(int j = 0; j < 5; j++){
			temp[b][a] = frota[numero]->bitmap[i][j]; 
			b++; 
		}
		a--;
		b=0;
	}
    
    
	for(int i = 0; i < 5; i++ ){
		for(int j = 0; j < 5; j++){
			frota[numero]->bitmap[i][j] = temp[i][j];  
		}

	}

    rot -= 90;
    if(rot != 0){ 
        rodar_barcos(frota, numero, rot);
    }
	else return;
}




//esta função recursiva serve para posicionar os barcos aleatoriamente
NODE* posicionar_barcos_random(NODE* jog, celula** jogador, barco** frota, int k){
    if(k==N_B){
        return jog;
    }

    //escolher uma posição aleatoriamente
    int x;
    int y;
    labelmapa:
    x = rand()%(tamanho-1);
    y = rand()%(tamanho-1);

    //escolher a rotação aleatoriamente
    int ran;
    ran = rand() % 4;
    if(ran !=0){
        rodar_barcos(frota, k, 90*ran);//manda para a função para rodar o barco
    }
    frota[k]-> rotacao =90*ran;

   if ( tipo_mat ==1 ){
        int l = posicionar_barcos_matriz(jogador, frota, k, x,y);
            if (l == 0) goto labelmapa; // se retornar 0 quer dizer que as coordenadas não são válidas 
                                        //e é necessário escolher outras.
    
    }
    else{
        int e = verifica_coor(jog,frota, k, x, y); //verifica se as coordenadas dadas são válidas
        if (e==0) goto labelmapa; // se retornar 0 quer dizer que as coordenadas não são válidas 
                                  //e é necessário escolher outras.
        else jog = posicionar_barcos_quad(jog,frota, k, x, y); // se as coordenadas forem válidas então estamos em condições de inseri-las na quadtre

    }

    
    return posicionar_barcos_random(jog,jogador, frota, k+1);//volta a chamar a função para o barco seguinte
}







NODE* posicionar_barcos_manual(NODE* jog, celula** jogador, barco** frota, int k){
    system("clear");
    system("clear");
    if(k==N_B){
        return jog;
    }
    if(tipo_mat==1)
        mostrar_mapa(jogador);
    else imprimir_quadtree(jog);


    //mostrar o bitmap do barco para o jogador ver que barco é que vai posicionar
    mostrar_bitmap_geral(frota[k] -> bitmap);

    labelmapa1:
    
    printf("Quer rodar este barco?  Não(0)  Sim(1)  Aleatório(2)\n");
    int r;
    scanf("%d", &r);
    
    //se o jogador obtar por rodar o barco, manda para a função e guarda na struct
    if(r==1){
        int flague=0;
        while(flague==0){
            printf("Quer rodar 90º(1), 180º(2), 270º(3) ou 0º/360º(4)\n");
            int rr;
            scanf("%d", &rr);
            if(rr == 1){
                printf("rodar 90\n");
                rodar_barcos(frota, k, 90);
                frota[k]-> rotacao =90;
                flague=1;
            }
            else if(rr == 2){
                rodar_barcos(frota, k, 180);
                frota[k]-> rotacao =180;
                flague =1;
            }
            else if(rr == 3){
                rodar_barcos(frota, k, 270);
                frota[k]-> rotacao =270;
                flague = 1;
            }
            else if(rr ==4){
                frota[k]-> rotacao =0;
                flague = 1;
            }
        } 
    }

    else if(r==2){//se quiser rodar aleatoriamente, 
        int ran;
        ran = rand() % 4;
        if(ran != 0){
            rodar_barcos(frota, k, 90*ran);
        }
        frota[k]-> rotacao =ran*90;
        
    }
    else if(r ==0){//se nao quiser rodar
        frota[k]-> rotacao =0;
    }

    else{
        goto labelmapa1;
    }

    //faz scan às coordenadas de onde quer posicionar o barco
    printf("Onde quer posicionar este barco? \n");
    mostrar_bitmap_geral(frota[k] -> bitmap);
    labelmapa:
    printf("\nOs números que escolher serão o ponto central do bitmap.\n");
    printf("(As coordenadas que escolher têm que ser entre 1 e %d, inclusive)\n", tamanho);
    
    int x, y;
    printf("linha: ");
    scanf("%d", &x);
    printf("coluna: ");
    scanf("%d", &y);

    //verifica se sao coordenadas aceitáveis
    if((x<1 || x> tamanho) || (y<1 || y > tamanho)){
        printf("Escolha uma opção válida!\n\n");
        goto labelmapa;
    }
    x -= 1;
    y -= 1;
    if ( tipo_mat ==1 ){
        int l = posicionar_barcos_matriz(jogador, frota, k, x,y);//verifica se as coordenadas dadas são válidas
        if (l==0) goto labelmapa; // se retornar 0 quer dizer que as coordenadas não são válidas 
                                  //e é necessário escolher outras.
    }
    else{
        int e = verifica_coor(jog,frota, k, x, y);//verifica se as coordenadas dadas são válidas
        if (e==0) goto labelmapa; // se retornar 0 quer dizer que as coordenadas não são válidas 
                                  //e é necessário escolher outras.
        else jog = posicionar_barcos_quad(jog,frota, k, x, y); // se as coordenadas forem válidas então estamos em condições de inseri-las na quadtre
    }


    
    return posicionar_barcos_manual(jog,jogador, frota, k+1);
}




