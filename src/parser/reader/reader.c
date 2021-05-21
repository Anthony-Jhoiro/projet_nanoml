#include "reader.h"

/**
 * Read the next character of a file. It will be store in the reader under `currentChar`
 * \param cursor cursor used to read the file
 */
void nextCharacter(reader cursor)
{
    cursor->currentChar = fgetc(cursor->file);
    printf("\e[0;34m%c\e[0;37m", cursor->currentChar);
}

/**
 * Create a reader from the filename. /!\ Remember to close the file after using it
 * \param filemane path to the file to read
 */
reader createReader(char *filename)
{
    reader cursor = (reader)malloc(sizeof(t_reader));

    cursor->file = fopen(filename, "r");

    nextCharacter(cursor);

    return cursor;
}

/**
 * Free the memory of the given reader
 * \param cursor reader to free
 */
void freeReader(reader cursor)
{
    fclose(cursor->file);
    free(cursor);
}