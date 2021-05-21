#include "../parser.h"

int verifyMotSimple(char *tagName)
{
    return tagName[0] == '\0';
}

a_tag parseMotSimple(reader cursor)
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
        return TAG_NULL;
    }

    return createTagMotSimple(e_mot_simple, buffer);
}

t_parser createMotSimpleParser()
{
    t_parser parser;
    parser.execute = parseMotSimple;
    parser.verify = verifyMotSimple;

    return parser;
}