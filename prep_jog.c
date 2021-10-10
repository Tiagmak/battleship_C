/*
    ESTE FICHEIRO SERVE PERSONALIZAR O JOGO
    É O ELEMENTO DE LIGAÇÃO ENTRE TODAS AS FUNÇÕES DO FICHEIRO "func_prep_jog"
*/

#include "cabecalho.h"


void preparar_jogo(){
    //definir as dimensões do tabuleiro
    //o jogador pode escolher de forma manual ou aleatória
        srand(time(NULL));

    int d_t;
    label:
    printf("Quer definir as dimensões do tabuleiro?(1) Ou quer que o jogo defina aleatóriamente?(2): ");
    scanf("%d", &d_t);
    if(d_t == 1){
        tamanho = manual_tabuleiro();
    }
    else if(d_t==2){
        tamanho = random_tabuleiro();
    }
    else{
        printf("Escolha uma opção válida!\n\n");
        goto label;
    }
    //--------------------------------------------------------------------------------------------------
  
    //cria as celulas dos jogadores
    //cria a celula jogador1 (t1)
    celula **t1 = (celula **)malloc(tamanho * sizeof(celula *));
    for (int i = 0; i < tamanho; ++i){
    t1[i] = (celula *)malloc(tamanho * sizeof(celula));
    }

    //cria a celula jogador2 (t2)
    celula **t2 = (celula **)malloc(tamanho * sizeof(celula *));
    for (int i = 0; i < tamanho; ++i){
    t2[i] = (celula *)malloc(tamanho * sizeof(celula));
    }

	if(tipo_mat==1){
        criar_struct(t1);
        criar_struct(t2);
    }
    else {
        for(int i=0; i<tamanho; i++){
        free(t1[i]);
        free(t2[i]);
        }
        free(t1);
        free(t2);
    }
    
    int p;
    if(tamanho <= 32)  p = 32;
    else p = 64;

    //criamos as quadtrees. 1 para cada jogador
    struct NODE *jog1 = criar_quad(0, 0, p); 
    struct NODE *jog2 = criar_quad(0, 0, p); 
    
    if(tipo_mat == 1){
        free(jog1);
        free(jog2);
    }

    system("clear");
    //mostramos aos jogadores a estrutura do seu tabuleiro caso tenham optado por matrizes
    if(tipo_mat==1)
     mostrar_mapa(t1);
    //mostramos aos jogadores a estrutura do seu tabuleiro caso tenham optado por quadtree
    else imprimir_quadtree(jog1);

    printf("O tabuleiro do jogo é %d x %d.\n\n", tamanho, tamanho);
    printf("PRESSIONE ENTER PARA CONTINUAR\n");
    char resolve;
    scanf("%c", &resolve);
    char n;
    while(n != '\n'){
        scanf("%c", &n);
    }
    system("clear");
    //--------------------------------------------------------------------------------------------------


    //definir o numero de barcos
    //O jogador pode fazê-lo de forma aleatória ou de forma manual 
    int flague=0;
    while(flague==0){

        printf("Quer definir o número de barcos?(1) Ou que o computador o faça?(2)\nO número de barcos vai ser o mesmo para ambos os jogadores.\n");
    
        int qual;
        scanf("%d", &qual);
    
        if(qual ==1){
            barcos_manual(tamanho);
            printf("\n\n");
            flague=1;
        }
        else if(qual == 2){
            barcos_random(tamanho);
            printf("\n\n");
            flague=1;
        }
        else{
            printf("Escolha uma opção valida.\n");
        
        }
    }
    //--------------------------------------------------------------------------------------------------
    

    //Os jogadores definem quantos barcos de cada tipo querem ter
    //tanto pode ser feit0 de forma manual ou aleatório
    //Do  Numero total de Barcos (N_B) previamente reservamos um para cada tipo
    if(N_B>5){
        int modo_barco;
        label3:
        printf("Querem definir quantos barcos de cada tipo têm? sim(1) não(2)\n(Os barcos serão iguais para os dois jogadores)\n");
        scanf("%d", &modo_barco);
        if(modo_barco ==1){
            definir_barco_manual();
        }
        else if(modo_barco == 2){
            definir_barco_random();
        }
        else{
            goto label3;
        }
    }

    else{ //se o numero de barcos for 5, automáticamente teremos um barco de cada tipo

        printf("Ficaram com %d barcos do tipo 3, %d de barcos do tipo L, ", numero3, numeroL);
        printf("%d barcos do tipo 4, %d barcos do tipo T e %d barcos do tipo Def.\n", numero4, numeroT, numeroDef);
        printf("\n\n\n");

    }
    //--------------------------------------------------------------------------------------------------
    
    printf("PRESSIONE ENTER PARA CONTINUAR\n");
    char resolve1;
    scanf("%c", &resolve1);
    char n1;
    while(n1 != '\n'){
        scanf("%c", &n1);
    }
    system("clear");



    //criamos um array de struct barco(criamos uma frota) para cada jogador 
    //estes contêm as informações dos barcos dos jogadores
    //aqui criamos a frota do jogador 1;
    barco* frota_do_1[N_B];
    criar_frota(frota_do_1);

    //aqui criamos a frota do jogador 2;
    barco* frota_do_2[N_B];
    criar_frota(frota_do_2);
//--------------------------------------------------------------------------------------------------
    
    //definir a posição dos barcos do jogador 1
    //a posição pode ser definida manualmente ou aleatóriamente

    labelposicionar1:
    printf("Jogador 1, quer posicionar os barcos(1) ou quer que o computador faça por si(2)?\n");
    printf("(Jogador 2, não vale olhar ;) )");
    int d;
    scanf("%d", &d);
    if(d==1){
        jog1 = posicionar_barcos_manual(jog1,t1, frota_do_1, 0);
    }
    else if(d == 2){
        jog1=posicionar_barcos_random(jog1,t1, frota_do_1, 0);
        system("clear");
        system("clear");
    }
    else{
        goto labelposicionar1;
    }

    if(tipo_mat==1)
        mostrar_mapa(t1);
    else imprimir_quadtree(jog1);

    printf("Este é o seu tabuleiro final, jogador 1.\n\n\n\n");
        
    printf("PRESSIONE ENTER PARA CONTINUAR\n");
    char resolve2;
    scanf("%c", &resolve2);
    char n2;
    while(n2 != '\n'){
        scanf("%c", &n2);
    }
    system("clear");
    //--------------------------------------------------------------------------------------------------

    //definir a posição dos barcos do jogador 2
    //a posição pode ser definida manualmente ou aleatóriamente

    labelposicionar2:
    printf("Jogador 2, queres ser tu a posicionar os barcos(1) ou queres que o computador faça por ti(2)?\n");
    printf("(Jogador 1, não vale olhar ;) )");
    scanf("%d", &d);
    if(d==1){
        jog2 = posicionar_barcos_manual(jog2,t2, frota_do_2, 0);
    }
    else if(d==2){
        jog2=posicionar_barcos_random(jog2,t2, frota_do_2, 0);
        system("clear");
        system("clear");
    }
    else{
        goto labelposicionar2;
    }
    if(tipo_mat==1)
        mostrar_mapa(t2);
    else imprimir_quadtree(jog2);
    printf("Este é o seu tabuleiro final, jogador 2.\n\n\n\n");
    //--------------------------------------------------------------------------------------------------7
  
    pontos_gerais = (numero3 * 3) + (numeroL * 4) + (numero4 * 4) + (numeroT * 5) + (numeroDef * 5);
    


    printf("PRESSIONE ENTER PARA CONTINUAR\n");
    char resolve3;
    scanf("%c", &resolve3);
    char n3;
    while(n3 != '\n'){
        scanf("%c", &n3);
    }
    system("clear");

    //como já passamos toda a informação para as respetivas celulas
    //Podemos libertar a memoria que nao usaremos
    for(int f=0; f<N_B; f++){
        free(frota_do_1[f]);
        free(frota_do_2[f]);
    }


    //depois do jogo estar personalizado 
    //passamos para a função jogar_jogo
    jogar_jogo(t1, t2, jog1,jog2);


    //Quando o jogo acabar, podemos libertar a memoria
    if(tipo_mat==1){
        for(int i=0; i<tamanho; i++){
            free(t1[i]);
            free(t2[i]);
        }
        free(t1);
        free(t2);
    }
    else {
        free(jog1);
        free(jog2);
    }
}
