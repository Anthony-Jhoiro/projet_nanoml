nanoml : parser.o nanoml.o
	gcc -o nanoml parser.o nanoml.o

nanoml.o : nanoml.c 
	gcc -c nanoml.c 

parser.o : src/parser/parser.c
	gcc -c src/parser/parser.c
