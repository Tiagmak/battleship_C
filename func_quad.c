//ESTE FICHEIRO É USADO PARA COLOCAR TODAS AS FUNÇÕES UTILIZADAS PELO FICHEIRO prep_jog
//QUE TENHAM A VERCOM A UTILIZAÇÃOD DE QUADTREE

#include "cabecalho.h"


POINT make_point(int xp,int yp) {
  POINT p;
  p.x = xp;      // usar   COORDX(p) = xp;
  p.y = yp;      // usar   COORDY(p) = yp;
  return p;
}



// Nesta função inicializamos a struct first. 
// Inicialmente esta struct é uma leaf com o tamanho total do tabuleiro e não tem pontos
NODE* criar_quad(int extremox, int extremoy, int tamanho){
  
  NODE *first = malloc(sizeof(NODE));    

  first -> extremo = make_point(extremox,extremoy);
  first->tamanho = tamanho;
  first->no.leaf.flague =0;
  first->tipo = LEAF;
  first -> no.leaf.cell = NULL;
  first -> no.leaf.valor = NULL;
  return first;
}

//esta função vê o que a matriz tem em determinada posição e devolver o seu conteúdo
char conteudo_mapas(NODE* first,int linha,int coluna, int flag){
  if (first == NULL) return '0';

    if(first -> tipo == ROOT){
        int qual = qual_quad(first, linha, coluna);
        return conteudo_mapas(first -> no.subs[qual], linha, coluna,flag);
    }
    else{
      if(first->no.leaf.valor == NULL){ 
            return '0';
        }
        else{
            if(first->no.leaf.valor->x == linha && first->no.leaf.valor-> y == coluna){
                if (flag == 0) return first->no.leaf.cell->mapa;
                else return first->no.leaf.cell->mapa_esc;
            }
            else{
                return '0';
            }
        }

    }
}
//Nesta função imprimimos a quadtree
void imprimir_quadtree(NODE* first ){

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
            if(conteudo_mapas(first,j,k,0) == '0'){//mete um zero se a celula tiver vazia
                printf(" 0 |");
            }
            else if(conteudo_mapas(first,j,k,0) == '1'){//mete um 1 a verde
                printf(" \033[1;92m1\033[0m |");
            }
            else if(conteudo_mapas(first,j,k,0) == '2'){//mete um 2 a vermelho
                printf(" \033[5;91m2\033[0m |");
            }
            else if(conteudo_mapas(first,j,k,0) == '3'){//mete um 3 a azul
                printf(" \033[1;94m3\033[0m |");
            }

        }
        printf("\n");
        for(int barra=0; barra<=tamanho; barra++){
            printf("----");
        }
        printf("\n");
    }
}
//mostra o mapa ás escuras
void imprimir_quadtree_esc(NODE* first ){
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
            if(conteudo_mapas(first,j,k,1) == '1'){//mete um 1 a azul
                printf("\033[1;34m 1\033[0m |");
            }

            else if(conteudo_mapas(first,j,k,1)  == '2'){//mete um 2 a vermelho
                printf("\033[5;31m 2\033[0m |");
            }
            else{
                printf(" %c |", conteudo_mapas(first,j,k,1) );
            }

        }
        printf("\n");
        for(int barra=0; barra<=tamanho; barra++){
            printf("----");
        }
        printf("\n");
    }  
}


// Esta função serviu para mostrar a quadtree
/*void escreve(NODE *first){

  if (first == NULL) return;


  if(first -> tipo == ROOT){
        printf("È UMA ROOT\n");

	for (int i = 0; i < 4; i++) 
	    escreve(first -> no.subs[i]);   
    }
    else{
      if(first->no.leaf.valor == NULL){      
            printf("nao tem numero\n");
        }
        else{
            printf("    %d     %d   \n", first->no.leaf.valor->x, first->no.leaf.valor->y);
        }

    }
}*/


// Nesta função determinamos a que quadrante pertence um ponto
int qual_quad(NODE *first, int linha, int coluna){
    if((linha - (COORDX(first->extremo))) < first->tamanho /2){
        if((coluna - (COORDY(first->extremo))) < first->tamanho /2){
            return 0; //primeiro quadrante  == subs[0]     
        }
        else{
            return 1; //segundo quadrante == subs[1]
        }
    }
    else if((coluna - (COORDY(first->extremo))) < first->tamanho /2){
        return 2; //terceiro quadrante == subs[2]
    }
    return 3; //quarto quadrante == subs[3]   
}



int dirs[4][2] = {{0,0}, {0,1},{1,0},{1,1}};

// Nesta função dividimos o nó em 4partes. Para isso criamos 4 nós e colocamos
// os nós dados a apontar para os respetivos nós criados.
NODE *dividir(NODE *first){    
  // O tamanho de cada um dos nós será metade do tamanho do nó inicial
  int n = first->tamanho /2;
  int linha, coluna;
  linha = COORDX(first->extremo);
  coluna = COORDY(first->extremo);
  int valorx, valory;  //os valores que o no tinha
  valorx = first ->no.leaf.valor->x;
  valory = first ->no.leaf.valor->y;

  for (int i=0; i < 4; i++) 
    first -> no.subs[i] = criar_quad(linha+dirs[i][0]*n,coluna+dirs[i][1]*n,n);


  //A seguir vamos ver a qual dos novos nós  criados o ponto que estava no nó inicial pertence e 
  // vamos inseri-lo no nó correto
  int quad = qual_quad(first, valorx, valory);

  first -> no.subs[quad] = inserir_ponto(first -> no.subs[quad], valorx, valory, first->no.leaf.cell-> barco1);    // inserção do anterior
  first->tipo = ROOT;

  return first;
}


//Esta função cria a leaf já com células e retorna a leaf final
NODE* transforma (int linha, int coluna, int extremox, int extremoy, int tamanho , barco* navio){
  NODE *first = malloc(sizeof(NODE));    

  first -> extremo = make_point(extremox,extremoy);
  first->tamanho = tamanho;
  first->no.leaf.flague =1;
  first->tipo = LEAF;
  struct POINT *w = malloc(sizeof(POINT));
  w->x = linha;
  w->y = coluna;
  first->no.leaf.valor = w;
  celula *n = malloc(sizeof(celula));
  n->mapa = '1';
  n->mapa_esc = '0';
  n->barco1 = navio;
  n->ocupado = 1;
  first->no.leaf.cell = n;
  return first;
}


// Nesta função inserimos um ponto na quadtree.
NODE * inserir_ponto(NODE *first, int linha, int coluna, barco* navio) { 
  
  if(first -> tipo == ROOT){
               
    int temp = qual_quad(first, linha, coluna);
    
    first-> no.subs[temp] = inserir_ponto(first->no.subs[temp], linha, coluna,navio);

    return first; 
  }
  // Se o nó é uma folha que ainda não tem nenhum ponto lá, então estamos em condições
  // para colocar lá o ponto 
  else if(first->no.leaf.flague == 0){
        int n = first->tamanho;
        int x = COORDX(first->extremo);
        int y = COORDY(first->extremo);
        first = transforma(linha, coluna, x, y,n,navio);
        return first;
    }
  // Se for uma leaf, mas já tiver uma folha então temos que dividir o nó
  else {     
        first = dividir(first);
        return inserir_ponto(first, linha, coluna,navio);
    }
}


// esta função receber uma cell já consatruida e cria uma leaf com esta célula
NODE *transforma_cell(int linha, int coluna, int extremox, int extremoy, int tamanho , celula *cello){
  NODE *first = malloc(sizeof(NODE));   

  first -> extremo = make_point(extremox,extremoy);
  first->tamanho = tamanho;
  first->no.leaf.flague =1;
  first->tipo = LEAF;
  struct POINT *w = malloc(sizeof(POINT));
  w->x = linha;
  w->y = coluna;
  first->no.leaf.valor = w;
  celula *n = malloc(sizeof(celula));
  n -> mapa_esc = cello -> mapa_esc;
  n -> mapa = cello -> mapa;
  n -> barco1 =  cello -> barco1;
  first -> no.leaf.cell = n;

  return first;
}



// Como já sabemos a posição exata de onde vamos inserir a cell então criamos a leaf
NODE *inserir_ponto_cell(NODE *first, int linha, int coluna, celula * cell){
  int n = first->tamanho;
  int x = COORDX(first->extremo);
  int y = COORDY(first->extremo);
  first = transforma_cell(linha, coluna, x, y, n, cell);
  return first;

}



//dividir o nó que apenas tem informação sobre o mapa escuro em 4 quadrantes
NODE *dividir_escuro(NODE *first){    
  // O tamanho de cada um dos nós será metade do tamanho do nó inicial
  int n = first->tamanho /2;
  int linha, coluna;
  linha = COORDX(first->extremo);
  coluna = COORDY(first->extremo);
  int valorx, valory;  //os valores que o no tinha
  valorx = first ->no.leaf.valor->x;
  valory = first ->no.leaf.valor->y;
  celula *temp = malloc(sizeof(celula));
  temp = first ->no.leaf.cell;

  for (int i=0; i < 4; i++) 
    first -> no.subs[i] = criar_quad(linha+dirs[i][0]*n,coluna+dirs[i][1]*n,n);


  //A seguir vamos ver a qual dos novos nós  criados o ponto que estava no nó inicial pertence e 
  // vamos inseri-lo no nó correto
  int quad = qual_quad(first, valorx, valory);

  if(first->no.leaf.cell != NULL){
    first -> no.subs[quad] = inserir_ponto_cell(first -> no.subs[quad], valorx, valory, temp);    // inserção do anterior
    first->tipo = ROOT;

    return first;
  }

  first -> no.subs[quad] = inserir_ponto_escuro(first -> no.subs[quad], valorx, valory, first->no.leaf.cell-> barco1);    // inserção do anterior
  first->tipo = ROOT;

  return first;
}






//cria uma celula que só tem informação sobre o mapa escuro, coloco a leaf a apontar para a célula e de seguida retorno a leaf
NODE* transforma_escuro (int linha, int coluna, int extremox, int extremoy, int tamanho , barco* navio){
  NODE *first = malloc(sizeof(NODE));    

  first -> extremo = make_point(extremox,extremoy);
  first->tamanho = tamanho;
  first->no.leaf.flague =1;
  first->tipo = LEAF;
  struct POINT *w = malloc(sizeof(POINT));
  w->x = linha;
  w->y = coluna;
  first->no.leaf.valor = w;
  celula *n = malloc(sizeof(celula));
  n -> mapa = '0';
  n ->mapa_esc = '1';
  n->barco1 = navio;
  first->no.leaf.cell = n;
  return first;
}




//uma função que vou acrescentar uma celula só a mostrar o escuro (e nao acertou)
NODE * inserir_ponto_escuro(NODE *first, int linha, int coluna, barco* navio) { 
  
  if(first -> tipo == ROOT){
               
    int temp = qual_quad(first, linha, coluna);
    
    first-> no.subs[temp] = inserir_ponto_escuro(first->no.subs[temp], linha, coluna,navio);

    return first; 
  }
  // Se o nó é uma folha que ainda não tem nenhum ponto lá, então estamos em condições
  // para colocar lá o ponto 
  else if(first->no.leaf.flague == 0){
        int n = first->tamanho;
        int x = COORDX(first->extremo);
        int y = COORDY(first->extremo);
        first = transforma_escuro(linha, coluna, x, y,n,navio);
        return first;
    }
  // Se for uma leaf, mas já tiver uma folha então temos que dividir o nó
  else {     
        first = dividir_escuro(first);
        return inserir_ponto_escuro(first, linha, coluna,navio);
    }
}




//dividir o nó que tem informação sobre o mapa escuro, a dizer que acertei num barco, em 4 quadrantes
NODE *dividir_escuro_acertei(NODE *first){    
  // O tamanho de cada um dos nós será metade do tamanho do nó inicial
  int n = first->tamanho /2;
  int linha, coluna;
  linha = COORDX(first->extremo);
  coluna = COORDY(first->extremo);
  int valorx, valory;  //os valores que o no tinha
  valorx = first ->no.leaf.valor->x;
  valory = first ->no.leaf.valor->y;

  celula *temp = malloc(sizeof(celula));
  temp = first ->no.leaf.cell;


  for (int i=0; i < 4; i++) 
    first -> no.subs[i] = criar_quad(linha+dirs[i][0]*n,coluna+dirs[i][1]*n,n);


  //A seguir vamos ver a qual dos novos nós  criados o ponto que estava no nó inicial pertence e 
  // vamos inseri-lo no nó correto
  int quad = qual_quad(first, valorx, valory);

  if(first->no.leaf.cell != NULL){
    first -> no.subs[quad] = inserir_ponto_cell(first -> no.subs[quad], valorx, valory, temp);    // inserção do anterior
    first->tipo = ROOT;

    return first;
  }
  first->tipo = ROOT;

  return first;
}




// esta função receber uma cell já consatruida e cria uma leaf com esta célula, só tem informaçao do mapa escuro a dizer que acertei num barco inimigo
NODE* transforma_escuro_acertei (int linha, int coluna, int extremox, int extremoy, int tamanho , barco* navio){
  NODE *first = malloc(sizeof(NODE));    

  first -> extremo = make_point(extremox,extremoy);
  first->tamanho = tamanho;
  first->no.leaf.flague =1;
  first->tipo = LEAF;
  struct POINT *w = malloc(sizeof(POINT));
  w->x = linha;
  w->y = coluna;
  first->no.leaf.valor = w;
  celula *n = malloc(sizeof(celula));
  n -> mapa = '0';
  n ->mapa_esc = '2';
  n->barco1 = navio;
  first->no.leaf.cell = n;
  return first;
}


//Vou inserir uma célula quadtree com informação de que acertei num barco
NODE * inserir_ponto_escuro_acertei(NODE *first, int linha, int coluna, barco* navio) { 
  
  if(first -> tipo == ROOT){
               
    int temp = qual_quad(first, linha, coluna);
    
    first-> no.subs[temp] = inserir_ponto_escuro_acertei(first->no.subs[temp], linha, coluna,navio);

    return first; 
  }
  // Se o nó é uma folha que ainda não tem nenhum ponto lá, então estamos em condições
  // para colocar lá o ponto 
  else if(first->no.leaf.flague == 0){
        int n = first->tamanho;
        int x = COORDX(first->extremo);
        int y = COORDY(first->extremo);
        first = transforma_escuro_acertei(linha, coluna, x, y,n,navio);
        return first;
    }
  // Se for uma leaf, mas já tiver uma folha então temos que dividir o nó
  else {     
        first = dividir_escuro_acertei(first);
        return inserir_ponto_escuro_acertei(first, linha, coluna,navio);
    }
}



//dividir o nó que tem informação sobre o mapa escuro, a dizer que falhou num barco
NODE *dividir_mapa_falhou(NODE *first){    
  // O tamanho de cada um dos nós será metade do tamanho do nó inicial
  int n = first->tamanho /2;
  int linha, coluna;
  linha = COORDX(first->extremo);
  coluna = COORDY(first->extremo);
  int valorx, valory;  //os valores que o no tinha
  valorx = first ->no.leaf.valor->x;
  valory = first ->no.leaf.valor->y;

  celula *temp = malloc(sizeof(celula));
  temp = first ->no.leaf.cell;


  for (int i=0; i < 4; i++) 
    first -> no.subs[i] = criar_quad(linha+dirs[i][0]*n,coluna+dirs[i][1]*n,n);


  //A seguir vamos ver a qual dos novos nós  criados o ponto que estava no nó inicial pertence e 
  // vamos inseri-lo no nó correto
  int quad = qual_quad(first, valorx, valory);

  if(first->no.leaf.cell != NULL){
    first -> no.subs[quad] = inserir_ponto_cell(first -> no.subs[quad], valorx, valory, temp);    // inserção do anterior
    first->tipo = ROOT;

    return first;
  }

  //first -> no.subs[quad] = inserir_ponto_mapa_falhou(first -> no.subs[quad], valorx, valory, first->no.leaf.cell-> barco1);    // inserção do anterior
  first->tipo = ROOT;

  return first;
}




// esta função receber uma cell já construida e cria uma leaf com esta célula, só tem informaçao do mapa ea dizer que falhou num barco inimigo
NODE* transforma_mapa_falhou (int linha, int coluna, int extremox, int extremoy, int tamanho , barco* navio){
  NODE *first = malloc(sizeof(NODE));    

  first -> extremo = make_point(extremox,extremoy);
  first->tamanho = tamanho;
  first->no.leaf.flague =1;
  first->tipo = LEAF;
  struct POINT *w = malloc(sizeof(POINT));
  w->x = linha;
  w->y = coluna;
  first->no.leaf.valor = w;
  celula *n = malloc(sizeof(celula));
  n -> mapa = '3';
  n ->mapa_esc = '0';
  n->barco1 = navio;
  first->no.leaf.cell = n;
  return first;
}




//Insiro uma cell que altera o mapa a dizer que o jogador falhou
NODE * inserir_ponto_mapa_falhou(NODE *first, int linha, int coluna, barco* navio) { 
  
  if(first -> tipo == ROOT){
               
    int temp = qual_quad(first, linha, coluna);
    
    first-> no.subs[temp] = inserir_ponto_mapa_falhou(first->no.subs[temp], linha, coluna,navio);

    return first; 
  }
  // Se o nó é uma folha que ainda não tem nenhum ponto lá, então estamos em condições
  // para colocar lá o ponto 
  else if(first->no.leaf.flague == 0){
        int n = first->tamanho;
        int x = COORDX(first->extremo);
        int y = COORDY(first->extremo);
        first = transforma_mapa_falhou(linha, coluna, x, y,n,navio);
        return first;
    }
  // Se for uma leaf, mas já tiver uma folha então temos que dividir o nó
  else {     
        first = dividir_mapa_falhou(first);
        return inserir_ponto_mapa_falhou(first, linha, coluna,navio);
    }
}





//Esta função verifica se determinadas coordenadas já existem na quad-tree
//se existirem devolve 1, senão devolvve0
int pesquisa(NODE *first, int linha, int coluna){
    if (first == NULL) return 0;

    //Se for uma root então vemos a que quandrante as coordenadas indicadas pertencem e procuramos nessse quadrante
    if(first -> tipo == ROOT){ 
        int qual = qual_quad(first, linha, coluna);
        return pesquisa(first -> no.subs[qual], linha, coluna);
    }
    else{
      if(first->no.leaf.valor == NULL){  // Se o nó não tem nenhum valor
            return 0;
        }
        else{
            // Se a quadtree já tiver essas coordenadas então retorna 1, senão retorna 0
            if(first->no.leaf.valor->x == linha && first->no.leaf.valor-> y == coluna){
                return 1;
            }
            else{
                return 0; // não tem o nr
            }
        }

    }

}
//Função que verifica se as coordenadas que o jogador escolhe ou que a função posicionar_barcos_random escolhe
// são válidas. Se forem retorna 1. Se não retorna 0.
int verifica_coor(NODE *jog , barco** frota, int k, int x, int y){
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
                    return 0;;
                }
            }
            if(pesquisa(jog,i,j)==1 && frota[k] -> bitmap[z][u] == '1'){
                printf("\033[3;31mNão pode ser essa posição pois está demasiado próxima de um barco.\033[0m\n\n");
                return 0;
            }
            u++;
        }
        z++;
    }
    return 1;
}

// Nesta função passamos por todos os bitmaps e onde tiver '1' então acrescentamos á quadtree 
NODE* posicionar_barcos_quad(NODE *jog, barco** frota, int k, int x, int y){
    //Adicionamos o ponto á quad tree
    int z=1; //o z vai ser a linha do bitmap
    for(int i= x-1; i<=x+1; i++){
        int u=1;   //o u vai ser a coluna do bitmap
        for(int j = y-1; j<=y+1; j++){
            if ((i<0 || j<0) || (i>=tamanho || j>= tamanho)){
                continue;
            }
            if(frota[k] -> bitmap[z][u] == '1'){
              jog = inserir_ponto(jog,i,j, frota[k]);
            }
            u++;
        }
        z++;
    }
return jog;

}

