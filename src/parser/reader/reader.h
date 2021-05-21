#ifndef READER_H
#define READER_H

#include <stdio.h>
#include "../../global.h"

/**
 * Structure representing a reader. A reader read a file character by character. It can store the active tag in a buffer.
 */
typedef struct s_reader {
    FILE* file;
    char currentChar;
    char currentTag[BUFFER_SIZE];
} t_reader;

typedef t_reader* reader;

/**
 * Read the next character of a file. It will be store in the reader under `currentChar`
 * \param cursor cursor used to read the file
 */
void nextCharacter(reader cursor);

/**
 * Create a reader from the filename. /!\ Remember to close the file after using it
 * \param filemane path to the file to read
 */
reader createReader(char* filename);

/**
 * Free the memory of the given reader
 * \param cursor reader to free
 */
void freeReader(reader cursor);

#endif