all:
	gcc -c -Wall -fPIC -o cabecalho.o prep_jog.c
	gcc -shared -o libprep_jog.so cabecalho.o

	gcc -c -Wall -fPIC -o cabecalho.o func_prep_jog.c
	gcc -shared -o libfunc_prep_jog.so cabecalho.o	

	gcc -c -Wall -fPIC -o cabecalho.o jog_jog.c
	gcc -shared -o libjog_jog.so cabecalho.o

	gcc -c -Wall -fPIC -o cabecalho.o func_jog_jog.c
	gcc -shared -o libfunc_jog_jog.so cabecalho.o

	gcc -c -Wall -fPIC -o cabecalho.o func_quad.c
	gcc -shared -o libfunc_quad.so cabecalho.o

	gcc -c -Wall -fPIC -o cabecalho.o func_quad_jog.c
	gcc -shared -o libfunc_quad_jog.so cabecalho.o

	gcc -Wall main.c -o main -L. -l prep_jog -l func_prep_jog -l jog_jog -l func_jog_jog -l func_quad -l func_quad_jog

clean:
	rm -rf *.o