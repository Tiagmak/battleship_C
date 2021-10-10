//ESTE FICHEIRO É USADO PARA COLOCAR TODAS AS FUNÇÕES UTILIZADAS PELO FICHEIRO jog_jog
//QUE TENHAM A VER COM UTILIZAÇÃODE QUADTREES

#include "cabecalho.h"

void info_jogada_quad(int x, int y, NODE *jog){
    x = x-1;
    y = y-1;

    if(conteudo_mapas(jog, x, y,0) == '3'){
        printf("e acertou em água.\n");
        return;
    }
    else{
        //info_barco(x, y, jog);
        printf("acertou num barco\n");
    }
}


/*
void info_barco(int x, int y, NODE *first){
    if (first == NULL) return ;

    if(first -> tipo == ROOT){
        int qual = qual_quad(first, x, y);
        info_barco(x, y, first -> no.subs[qual]);
    }

    else{
      if(first->no.leaf.valor == NULL){ 
            return ;
        }
        else{
            if(first->no.leaf.valor->x == x && first->no.leaf.valor-> y == y){
               
                switch(first->no.leaf.cell->barco1 -> tipo) {
                 case '3':
                    printf("e acertou num barco do tipo 3");
                    break;
                case 'L':
                    printf("e acertou num barco do tipo L");
                    break;
                case '4':
                    printf("e acertou num barco do tipo 4");
                    break;   

                case 'T':
                    printf("e acertou num barco do tipo T");
                    break;
                default:
                    printf("e acertou num barco do tipo Def");
                    break;
                }
                if(first->no.leaf.cell->barco1 -> atingido == first->no.leaf.cell->barco1 -> pontos){
                    printf(" e afundou o barco.");
                }   
            
            }
            else{
                return ;
            }
        }

    }
}*/


//esta função vê o que a quadtree tem em determinada posição e devolver o seu conteúdo
// Se a flag for 0 retorna o conteúdo do mapa, se for 1 retorna o conteúdo do mapa_esc
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



//Recebemos uma cell que tem lá informação e alteramos o carater do mapa escuro para falhou num barco
void mudar_cell_falhou_escuro(NODE* first,int linha,int coluna){
  if (first == NULL) return;

    if(first -> tipo == ROOT){
        int qual = qual_quad(first, linha, coluna);
        //return 
        mudar_cell_falhou_escuro(first -> no.subs[qual], linha, coluna);
    }
    else{
      if(first->no.leaf.valor == NULL){ 
            return; 
        }
        else{
            if(first->no.leaf.valor->x == linha && first->no.leaf.valor-> y == coluna){
                celula *n = malloc(sizeof(celula));
                n -> mapa = first->no.leaf.cell -> mapa;
                n -> barco1 = first->no.leaf.cell -> barco1;
                n -> mapa_esc = '1';
                first->no.leaf.cell = n;
                return ;
            }
            else{
                return;
            }
        }

    }
}




//Recebemos uma cell que tem lá informação e alteramos o carater do mapa escuro para acertou num barco
void mudar_cell_acertou_escuro(NODE* first,int linha,int coluna){
  if (first == NULL) return; 

    if(first -> tipo == ROOT){
        int qual = qual_quad(first, linha, coluna);
        //return
         mudar_cell_acertou_escuro(first -> no.subs[qual], linha, coluna);
    }
    else{
      if(first->no.leaf.valor == NULL){ 
            return; 
        }
        else{
            if(first->no.leaf.valor->x == linha && first->no.leaf.valor-> y == coluna){
                celula *n = malloc(sizeof(celula));
                n -> mapa = first->no.leaf.cell -> mapa;
                n -> barco1 = first->no.leaf.cell -> barco1;
                n -> mapa_esc = '2';
                first->no.leaf.cell = n;
                return; 
            }
            else{
                return; 
            }
        }

    }
}






//Recebemos uma cell que tem lá informação e alteramos a informação no mapa para mostrar que o adversário acertou num barco nosso
void mudar_cell_acertou_mapa(NODE* first,int linha,int coluna){
    if (first == NULL) return; //NULL;

    if(first -> tipo == ROOT){
        int qual = qual_quad(first, linha, coluna);

         mudar_cell_acertou_mapa (first -> no.subs[qual], linha, coluna);
    }
    else{
      if(first->no.leaf.valor == NULL){ 
            return;
        }
        else{
            if(first->no.leaf.valor->x == linha && first->no.leaf.valor-> y == coluna){
                celula *n = malloc(sizeof(celula));
                n -> mapa = '2';
                n -> barco1 = first->no.leaf.cell -> barco1;
                n -> mapa_esc = first -> no.leaf.cell -> mapa_esc;
                first->no.leaf.cell = n;
                return;
            }
            else{
                return;
            }
        }

    }
}






//Recebemos uma cell que tem lá informação e alteramos a informação no mapa para mostrar que o adversário falhou o tiro
void mudar_cell_falhou_mapa(NODE* first,int linha,int coluna){
  if(first == NULL){
  }
  if (first == NULL) return; 

    if(first -> tipo == ROOT){
        int qual = qual_quad(first, linha, coluna);
        mudar_cell_falhou_mapa (first -> no.subs[qual], linha, coluna);
    }
    else{
      if(first->no.leaf.valor == NULL){ 
            return; 
        }
        else{
            if(first->no.leaf.valor->x == linha && first->no.leaf.valor-> y == coluna){
                celula *n = malloc(sizeof(celula));
                n -> mapa = '3';
                n -> barco1 = first->no.leaf.cell -> barco1;
                n -> mapa_esc = first -> no.leaf.cell -> mapa_esc;
                first->no.leaf.cell = n;
                return; 
            }
            else{
                return;
            }
        }

    }
}






//esta função irá modificar as quad tree conforme a jogada do jogador 1
NODE* joga_jogador1_quad(NODE* jog1, NODE* jog2, int x, int y){
    x = x-1;
    y = y-1;
    
    //ve o que ha no mapa do jog2 para ver onde acertou
    if(conteudo_mapas(jog2, x, y, 0) == '0'){ //quer dizer que nao ha nenhum barco em jog2
        if(pesquisa(jog1, x, y) == 0){//eu nao tenho nenhuma cell com aquele valor
            jog1 =  inserir_ponto_escuro(jog1, x, y, NULL); //uma função que vou acrescentar uma celula só a mostrar o escuro (e nao acertou logo o barco é null)
        }
        else{//eu tenho uma cell naquele valor
            mudar_cell_falhou_escuro(jog1, x, y);
        }

    }
    else{//quer dizer que acertei num barco de jog2
        if(pesquisa(jog1, x, y) == 0){//eu nao tenho nenhuma celula com aquele valor
            jog1 = inserir_ponto_escuro_acertei(jog1, x, y, NULL);
        }
        else{//eu tenho uma celula com esse valor
            mudar_cell_acertou_escuro(jog1, x, y);
        }
    }

    return jog1;
}






//esta função irá modificar as quad tree conforme a jogada do jogador 2
NODE* joga_jogador2_quad(NODE* jog1, NODE* jog2, int x, int y){
    x = x-1;
    y = y-1;
    //ve o que ha no mapa do jog2 para ver onde acertou
    if(conteudo_mapas(jog1, x, y, 0) == '0'){ //quer dizer que nao ha nenhum barco em jog2
        if(pesquisa(jog2, x, y) == 0){//eu nao tenho nenhuma cell com aquele valor
            jog2 =  inserir_ponto_escuro(jog2, x, y, NULL); //uma função que vou acrescentar uma celula só a mostrar o escuro (e nao acertou)

        }
        else{//eu tenho uma cell naquele valor
            mudar_cell_falhou_escuro(jog2, x, y);
        }

    }
    else{//quer dizer que acertei num barco de jog2
        if(pesquisa(jog2, x, y) == 0){//eu nao tenho nenhuma celula com aquele valor
            jog2 = inserir_ponto_escuro_acertei(jog2, x, y, NULL); //Uma função a que vou acrescentar uma célula, a mostrar o escuro (acertei num barco)
        }
        else{//eu tenho uma celula com esse valor

            mudar_cell_acertou_escuro(jog2, x, y);
        }
    }

    return jog2;
}


// Atualiza a Cell do jogador 2
NODE* atualizar_cell2(NODE * first, int x, int y){
    x = x-1;
    y = y-1;
    if (conteudo_mapas(first, x, y, 0) == '1'){//acertou num navio meu
        mudar_cell_acertou_mapa(first, x, y);
        ponto_jogador1 ++;
        return first;
    }
    else{//acertou em agua, posso ter ou nao celula
        if(pesquisa(first, x, y) == 0){//eu nao tenho nenhuma cell com aquele valor
            first = inserir_ponto_mapa_falhou(first, x, y, NULL); //Insiro uma cell que altera o mapa a dizer que o jogaodr falhou
            return first;
        }
        else{//eu tenho uma cell lá
            mudar_cell_falhou_mapa(first, x, y);
        }


    }
    

    return first;
}


// Atualiza a Cell do jogador 1
NODE* atualizar_cell1(NODE * first, int x, int y){
    x = x-1;
    y = y-1;
    if (conteudo_mapas(first, x, y, 0) == '1'){//acertou num navio meu
        mudar_cell_acertou_mapa(first, x, y);
        ponto_jogador2 ++;
        return first;
    }
    else{//acertou em agua, posso ter ou nao celula
        if(pesquisa(first, x, y) == 0){//eu nao tenho nenhuma cell com aquele valor
            first = inserir_ponto_mapa_falhou(first, x, y, NULL); //Insiro uma cell que altera o mapa a dizer que o jogaodr falhou
            return first;
        }
        else{//eu tenho uma cell lá
            mudar_cell_falhou_mapa(first, x, y);
        }


    }
    

    return first;
}