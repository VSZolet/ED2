all: saida
	@echo "Concluido";

saida: mainArvoreb.o criaArvoreb.o buscaArvoreb.o insereArvoreb.o printArvoreb.o removeArvoreb.o
	gcc -o saida mainArvoreb.o criaArvoreb.o buscaArvoreb.o insereArvoreb.o printArvoreb.o removeArvoreb.o

mainArvoreb.o: mainArvoreb.c arvoreb.h
	gcc -o mainArvoreb.o -c mainArvoreb.c

criaArvoreb.o: criaArvoreb.c arvoreb.h
	gcc -o criaArvoreb.o -c criaArvoreb.c

buscaArvoreb.o: buscaArvoreb.c arvoreb.h
	gcc -o buscaArvoreb.o -c buscaArvoreb.c

insereArvoreb.o: insereArvoreb.c arvoreb.h
	gcc -o insereArvoreb.o -c insereArvoreb.c

printArvoreb.o: printArvoreb.c arvoreb.h
	gcc -o printArvoreb.o -c printArvoreb.c

removeArvoreb.o: removeArvoreb.c arvoreb.h
	gcc -o removeArvoreb.o -c removeArvoreb.c

clean:
	rm -f *.o

execClean:
	rm -f saida
