main: main.o refugee.o
	gcc -o main main.o refugee.o

refugee.o: refugee.h refugee.c
	gcc -c refugee.c

main.o: refugee.o main.c
	gcc -c main.c

clean:
	rm -f *.o
	rm -f main