.PHONY : build run clean clean_obj clean_exec
.DEFAULT_GOAL := run

# Variables
CFLAGS = -lm -Wall -fsanitize=address
libraries = image.o math2.o gen_DC.o
objects = $(libraries) bruit.o generation_carte.o
executables = bruit generation_carte

# Compilation rules
image.o : image.h
bruit.o : image.h
math2.o : math2.h
gen_DC.o : gen_DC.h math2.h
generation_carte.o : image.h gen_DC.h math2.h

bruit: bruit.o $(libraries)
	gcc -o bruit $(CFLAGS) bruit.o $(libraries) 

generation_carte : generation_carte.o $(libraries)
	gcc -o generation_carte $(CFLAGS) generation_carte.o $(libraries)

build : $(executables)

# Run rules
run : generation_carte
	./generation_carte

# Cleaning rules
clean : clean_obj clean_exec
	
clean_obj : 
	rm -f $(objects)

clean_exec :
	rm -f $(executables)