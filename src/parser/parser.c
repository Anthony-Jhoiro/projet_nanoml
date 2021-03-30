#include "parser.h"

void parser(char *filename)
{
    reader cursor = createReader(filename);

    readText(cursor);

    fclose(cursor->file);
}

void nextCharacter(reader cursor)
{
    cursor->currentChar = fgetc(cursor->file);

    if (cursor->currentChar == EOF)
    {
        fprintf(stderr, "Unexpected end of file.");
        exit(1);
    }
}

reader createReader(char *filename)
{
    reader cursor = (reader)malloc(sizeof(t_reader));

    cursor->file = fopen(filename, "r");

    nextCharacter(cursor);

    return cursor;
}

int isSyntaxChar(char c)
{
    return c == '<' || c == '>';
}

int isSpace(char c) {
    return c == ' ';
}

void readSpaces(reader cursor)
{
    while (isSpace(cursor->currentChar))
    {
        nextCharacter(cursor);
    }
}

int readWord(reader cursor, char* buffer) {
    
    int length = 0;
    while (cursor->currentChar != ' ' && cursor->currentChar != '<' && length < BUFFER_SIZE - 1 )
    {
        sprintf(buffer, "%s%c", buffer, cursor->currentChar);
        nextCharacter(cursor);
        length++;
    }

    return length;
    
}

tag* readText(reader cursor)
{

    readSpaces(cursor);

    
    char buffer[BUFFER_SIZE];
    while (readWord(cursor, buffer)) {
        
        printf("Word : %s\n", buffer);
        readSpaces(cursor);
        

    }
    return NULL;
}