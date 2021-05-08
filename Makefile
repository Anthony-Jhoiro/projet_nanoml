nanoml : parser.o nanoml.o tag.o tagList.o
	gcc -o nanoml *.o

nanoml.o : nanoml.c 
	gcc -c nanoml.c 

# TODO : update .c list
parser.o : src/parser/parser.c src/parser/parserAnnexes.c src/parser/parserDocument.c src/parser/parserImportant.c src/parser/parserItem.c src/parser/parserListe.c src/parser/parserMotSimple.c src/parser/parserSection.c
	gcc -c src/parser/*.c

tag.o : src/tag/tag.c
	gcc -c src/tag/tag.c

tagList.o : src/tagList/tagList.c
	gcc -c src/tagList/tagList.c

clean:
	rm -f *.o
	rm -f nanoml