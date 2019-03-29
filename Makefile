all: Cards.o main.c
	gcc -Wall main.c -o main.out Cards.o;

Cards.o: src/Cards.c hdr/Cards.h
	gcc -c src/Cards.c hdr/Cards.h
