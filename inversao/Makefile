parametros=-Wall -lm
nomeprog=inv

all: $(nomeprog)

$(nomeprog): main.o linear.o utils.o
	gcc -o $(nomeprog) main.o linear.o utils.o $(parametros)

main.o: main.c
	gcc -c main.c $(parametros)

linear.o: linear.c linear.h
	gcc -c linear.c $(parametros)

utils.o: utils.c utils.h
	gcc -c utils.c $(parametros)

clean:
	rm -f *.o *.ghc $(nomeprog)
