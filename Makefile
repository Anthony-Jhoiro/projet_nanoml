nanoml : parser.o nanoml.o tag.o tagList.o
	gcc -o nanoml parser.o nanoml.o tag.o  tagList.o

nanoml.o : nanoml.c 
	gcc -c nanoml.c 

parser.o : src/parser/parser.c
	gcc -c src/parser/parser.c

tag.o : src/tag/tag.c
	gcc -c src/tag/tag.c

tagList.o : src/tagList/tagList.c
	gcc -c src/tagList/tagList.c
