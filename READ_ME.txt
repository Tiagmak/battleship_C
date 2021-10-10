Grupo_ O :
	- Tatiana Araújo up201805169
	- Tiago Macedo up201706035

IMPORTANTE!!: 
	Para compilar o ficheiro execute o comando 
		-make

	Dependendo do sistema operativo que estiver a usar poderá ter também de executar o comando: 
		- export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH

	Para executar o jogo corra o seguinte código 
		- ./main.c -q -> com opção para quadtrees
		- ./main.c -m -> com opção para matrizes
	Se se esquecer de inserir opção então o programa corre com quadtrees 

Este zip contém os ficheiros cabecalho.h, prep_jog.c, func_prep_jo.c, jog_jog.c, func_jog_jog.c, main.c, makefile, 1.txt e 2.txt. !!! FALTA ACRESCENTAR FICHEIROS!!!!

Makefile:
	Criamos 4 biblioteca dinâmica: libprep_jog,  libfunc_prep_jog, libjog_jog, libfunc_jog_jog, libfunc_quad, libfunc_quad_jog.
	A opção -fPIC indica ao compilador que deve gerar código binário que possa ser colocado em qualquer posição na memória.
	A opção -shared indica ao compilador que a biblioteca resultante vai ser um shared object, com extensão.so.

DESCRIÇÃO DOS FICHEIROS:
	FICHEIRO cabecalho.h - utilizamos para inicializar variáveis gerais, criar a struct do barco e da célula e as funções para "ligar" os ficheiros.
	FICHEIRO prep_jog.c -  será a biblioteca que irá servir para personalizar o jogo e é o elemento de ligação entre todas as funções do ficheiro func_prep_jog.c.
	FICHEIRO func_prep_jog.c - será a biblioteca que contém todas as funções que o ficheiro prep_jog.c irá precisar. 
	FICHEIRO jog_jog.c - esta será a biblioteca que serve para os jogadores jogarem entre si e fazer a ligação entre o jogo do jogador 1 e do jogador 2.
	FICHEIRO func_jog_jog.c - será a biblioteca que contém todas as funções que o ficheiro jog_jog.c irá precisar. 
	FICHEIRO fun_quad - esta bibioteca contém todas as funções necessárias para a implementação da quadtree para a parte de preparar o jogo.
	FICHEIRO func_quad_jog - esta bibioteca contém todas as funções necessárias para a implementação da quadtree para a parte do preparar jogo. 
	FICHEIRO 1.txt e 2.txt - contém o manual do jogo.

DESCRIÇÃO DO JOGO:
	Ao longo deste projeto trabalhamos 1 struct com 2 matrizes do tipo char por jogador. A matriz mapa que guarda as informações do tabuleiro do próprio jogador
e a matriz mapa_esc que guarda as informações relativas aos tiros que já disparou. 
	Ao posicionar cada barco colocamos as posições da matriz a apontar para uma struct barco sendo que as restantes posições ficam a apontar para null. Isto é 
possivel devido ao apontador para barco que existe na struct célula que contém os tabuleiros de jogo.

	Inicialmente damos oportunidade de o jogador consultar o manual do jogo e de seguida fazemos várias perguntas aos jogadores de forma a personalizarem o jogo.
Os jogadores podem posicionar os barcos juntos e com rotação á escolha.Depois do jogo estar definido os jogadores jogam á vez.
	Para mais informação consulte o manual do jogo ou ficheiros 1.txt e 2.txt.


NOTA: Nas quadtrees se o tamanho do tabuleiro for maior ou igual a 32 então criamos uma quadtree com tamanho 64. Se for menor criamos uma quadtree com tamanho 32.