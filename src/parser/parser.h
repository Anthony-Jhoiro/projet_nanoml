#ifndef PARSER_H
#define PARSER_H

#include "../global.h"
#include <stdio.h>

typedef struct s_reader {
    FILE* file;
    char currentChar;
} t_reader;

typedef t_reader* reader;

void nextCharacter(reader cursor);

void parser(char* filename);

reader createReader(char* filename);

tag readTag(reader cursor, tagsNames name);

/**
 * TODO : words with more than 256 characters
 */

tag* readText(reader cursor);




#endif
