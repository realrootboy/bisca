FLAGS=-Wall \
      -g

all: main clean

main: Cards.o main.c
	gcc $(FLAGS) main.c -o main.out Cards.o

Cards.o: src/Cards.c hdr/Cards.h
	gcc $(FLAGS) -c src/Cards.c hdr/Cards.h

clean:
	rm -rf *.o hdr/*.gch
