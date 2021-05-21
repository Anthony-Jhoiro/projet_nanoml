#include "reader.h"

void nextCharacter(reader cursor)
{
    cursor->currentChar = fgetc(cursor->file);
    printf("\e[0;34m%c\e[0;37m", cursor->currentChar);
}

reader createReader(char *filename)
{
    reader cursor = (reader)malloc(sizeof(t_reader));

    cursor->file = fopen(filename, "r");

    nextCharacter(cursor);

    return cursor;
}