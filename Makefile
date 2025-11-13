.PHONY : clean run

all : run clean

bruit.o :
	gcc -c bruit.c

image.o :
	gcc -c image.c

math2.o :
	gcc -c math2.c

bruit: bruit.o image.o math2.o
	gcc bruit.o image.o math2.o -lm -o bruit -Wall -fsanitize=address

run : bruit
	./bruit

clean :
	rm -f *.o 