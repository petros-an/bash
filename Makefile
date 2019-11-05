all: src/options.c include/options.h
	gcc -o bin/options src/options.c -g3
