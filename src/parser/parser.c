#include "parser.h"

void parser(char *filename)
{
    reader cursor = createReader(filename);

    tag *res = readText(cursor);

    printf("\n\n");
    printTag(res);

    fclose(cursor->file);
}

void nextCharacter(reader cursor)
{
    cursor->currentChar = fgetc(cursor->file);
    printf("%c", cursor->currentChar);

    // if (cursor->currentChar == EOF)
    // {
    //     fprintf(stderr, "Unexpected end of file.\n");
    //     exit(1);
    // }
}

reader createReader(char *filename)
{
    reader cursor = (reader)malloc(sizeof(t_reader));

    cursor->file = fopen(filename, "r");

    nextCharacter(cursor);

    return cursor;
}

int estChevronGauche(char c)
{
    return c == '<';
}

int estEspace(char c)
{
    return c == ' ' || c == '\n' || c == '\t' || c == EOF;
}

void readSpaces(reader cursor)
{
    while (estEspace(cursor->currentChar) && cursor->currentChar != EOF)
    {
        nextCharacter(cursor);
    }
}

tag *readText(reader cursor)
{
    tag *t = createTag(t_texte);

    tag *mot = lireMotSimple(cursor);

    while (mot != NULL)
    {
        addChild(t, mot);
        mot = lireMotSimple(cursor);
    }

    return t;
}

tag *lireMotSimple(reader cursor)
{
    // On passe les espaces
    readSpaces(cursor);

    char *buffer = malloc(BUFFER_SIZE);
    int length = 0;
    while ((!estEspace(cursor->currentChar)) && (!estChevronGauche(cursor->currentChar)) && length < BUFFER_SIZE - 1)
    {
        sprintf(buffer + length, "%c", cursor->currentChar);
        nextCharacter(cursor);
        length++;
    }
    if (length == 0)
    {
        return NULL;
    }

    return createTagMotSimple(t_mot_simple, buffer);
}
