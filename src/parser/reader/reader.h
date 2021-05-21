#ifndef READER_H
#define READER_H

#include <stdio.h>
#include "../../global.h"

typedef struct s_reader {
    FILE* file;
    char currentChar;
    char currentTag[BUFFER_SIZE];
} t_reader;

typedef t_reader* reader;


void nextCharacter(reader cursor);
reader createReader(char* filename);

#endif