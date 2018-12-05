all: share.o
	gcc -o test share.o

share.o: share.c
	gcc -c share.c

run:
	./test

clear:
	rm *.o
	rm ./test
