FLAGS=-Wall \
      -g

LIBS=Cards.o \
     Player.o

all: main clean

main: $(LIBS) main.c
	gcc $(FLAGS) main.c -o main $(LIBS);

Cards.o: src/Cards.c hdr/Cards.h
	gcc $(FLAGS) -c src/Cards.c hdr/Cards.h

Player.o: src/Player.c hdr/Player.h
	gcc $(FLAGS) -c src/Player.c hdr/Player.h

clean:
	rm -rf *.o hdr/*.gch
