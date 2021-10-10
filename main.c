#include "cabecalho.h"


/*esta função imprime no terminal os ficheiro 1.txt e 2.txt que contêm um manual do jogo.
*/

void escreve(){
    system("clear");
    printf("\n\nMANUAL DO JOGO:\n\n");

    FILE* f;
    char c;
    f = fopen("1.txt","r");
    while((c=getc(f))!=EOF){
        printf("%c",c);
    }

    fclose(f);

    mostrar_bitmap_geral(bitmap3);
    printf("\nBarco do tipo 3.\n\n");
    mostrar_bitmap_geral(bitmapL);
    printf("\nBarco do tipo L.\n\n");
    mostrar_bitmap_geral(bitmap4);
    printf("\nBarco do tipo 4.\n\n");
    mostrar_bitmap_geral(bitmapT);
    printf("\nBarco do tipo T.\n\n");
    mostrar_bitmap_geral(bitmapDef);
    printf("\nBarco do tipo Def.\n\n");


    FILE* g;
    char d;
    g = fopen("2.txt","r");
    while((d=getc(g))!=EOF){
        printf("%c",d);
    }

    fclose(g);
}  


int main(int argc, char **argv){
    system("clear");
    int opt2;
    // Se o jogador se esquecer de indicar se quer jogar com quadtrees ou com matrizes então fica com quadtree
    if(argc==1){
        tipo_mat=0;
        tipo_quad=1;
    }
    else{
        while ( (opt2 = getopt(argc, argv, "mq")) != -1 ) {
   	 	  switch (opt2){
			case 'm': 
				tipo_mat = 1; // O jogador quer jogar com matrizes
				break;

			case 'q': 
				tipo_quad = 1; //O jogador quer jogar com quadtree
				break;
		  }		
        }
    }


    printf("Criado por:\n");
    printf("           Tiago Macedo,   201706035\n");
    printf("           Tatiana Araújo, 201805169\n");
    printf("\n\n\n\n\n\n");
    printf("\n");
    printf("                                                        #############################\n");
    printf("                                                        #                           #\n");
    printf("                                                        #          BATALHA          #\n");
    printf("                                                        #           NAVAL           #\n");
    printf("                                                        #                           #\n");
    printf("                                                        #############################\n");
    printf("\n");
    printf("                                                  PRESSIONE 'R' PARA VER AS REGRAS DO JOGO\n");
    printf("                                                            OU ENTER PARA COMEÇAR.\n\n\n");


    
    char n;
    char b;
    
    scanf("%c", &n);

    int flague=0;
    
    //este while irá analisar todos os input até ler um ENTER "\n"
    while(n != '\n'){

        if((n == 'R' || n == 'r') && flague==0){
            scanf("%c", &b);
            escreve();
            flague=1;

            printf("\n");
            printf("                                                 PRESSIONE ENTER PARA COMEÇAR\n");
        }
        scanf("%c", &n);
        if(n == '\n'){
            system("clear");
        }

    }

    preparar_jogo();
    return 0;
}
