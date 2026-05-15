.PHONY : run clean clean_obj clean_exec

run : bruit
	./bruit



image.o : image.h
bruit.o : image.h
math2.o : 
gen_DC.o :

bruit: bruit.o image.o math2.o
	gcc bruit.o image.o math2.o -lm -o bruit -Wall -fsanitize=address

gen_DC : gen_DC.o
	gcc gen_DC.o -lm -o gen_DC -Wall -fsanitize=address



clean : clean_obj clean_exec
	
clean_obj : 
	rm -f *.o

clean_exec :
	rm -f bruit gen_DC