#ifndef PARSER_H
#define PARSER_H

#include "../tag/tag.h"
#include <stdio.h>

typedef struct s_reader {
    FILE* file;
    char currentChar;
} t_reader;

typedef t_reader* reader;


typedef struct s_parser
{
    tag* (*execute)(reader);
} t_parser;


void nextCharacter(reader cursor);

void parser(char* filename);

reader createReader(char* filename);

tag readTag(reader cursor, tagsNames name);

/**
 * TODO : words with more than 256 characters
 */

tag* readText(reader cursor);

tag* lireMotSimple(reader cursor);

/**
 * \brief read an important word in the file (it reads "<important> + content + </important>")
 * 
 * \param cursor the file's cursor
 * 
 * \return an important tag
 * 
 * imporant tag exemple :
 * <important> exemple </important>
 * (spaces are facultative)
 */
tag* lireMotImportant(reader cursor);

tagList unOuPlus(t_parser parser, reader cursor);

tag *ou(reader cursor, t_parser *parsers, int nbParsers);



#endif
