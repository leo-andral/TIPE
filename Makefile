.PHONY : run clean clean_obj clean_exec

run : generation_carte
	./generation_carte
	

image.o : image.h
bruit.o : image.h
math2.o : 
gen_DC.o : gen_DC.h
generation_carte.o : image.h gen_DC.h

bruit: bruit.o image.o math2.o
	gcc bruit.o image.o math2.o -lm -o bruit -Wall -fsanitize=address

generation_carte : generation_carte.o gen_DC.o image.o
	gcc generation_carte.o gen_DC.o image.o -lm -o generation_carte -Wall -fsanitize=address


clean : clean_obj clean_exec
	
clean_obj : 
	rm -f *.o

clean_exec :
	rm -f bruit generation_carte