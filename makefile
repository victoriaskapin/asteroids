CC = gcc
CFLAGS = -pedantic -Wall -std=c99 

all: tp2

lista.o: lista.c lista.h 
	$(CC) $(CFLAGS) -o lista.o -c lista.c
	
modulo.o: modulo.c iterador.c lista.c nave.c lista.h iterador.h modulo.h config.h nave.h
	$(CC) $(CFLAGS) -o modulo.o -c modulo.c

nave.o: nave.c iterador.c modulo.c nave.h iterador.h modulo.h config.h
	$(CC) $(CFLAGS) -o nave.o -c nave.c

asteroides.o: asteroides.c iterador.c modulo.c asteroides.h iterador.h modulo.h config.h lista.h nave.h
	$(CC) $(CFLAGS) -o asteroides.o -c asteroides.c

disparos.o: disparos.c 
	$(CC) $(CFLAGS) -o disparos.o -c disparos.c -lm

utilidades.o: utilidades.c
	$(CC) $(CFLAGS) -o utilidades.o -c utilidades.c -lm -lSDL2

iterador.o: iterador.c lista.c lista.h iterador.h
	$(CC) $(CFLAGS) -o iterador.o -c iterador.c

main.o: main.c iterador.c modulo.c nave.c lista.c asteroides.c asteroides.h lista.h modulo.h iterador.h nave.h config.h lista.c lista.h utilidades.h
	$(CC) $(CFLAGS) -o main.o -c main.c

tp2: lista.o modulo.o nave.o iterador.o main.o asteroides.o disparos.o utilidades.o
	$(CC) $(CFLAGS) -o tp2 lista.o modulo.o disparos.o utilidades.o nave.o iterador.o main.o asteroides.o -lm -lSDL2
	
clean:
	rm *.o
