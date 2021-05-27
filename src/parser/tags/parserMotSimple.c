#include "../parser.h"

char parseSpecialChar(char *code)
{
    if (compareStr(code, "lt"))
        return '<';
    if (compareStr(code, "amp"))
        return '&';
    if (compareStr(code, "quot"))
        return '"';
    if (compareStr(code, "apos"))
        return '\'';
    if (compareStr(code, "gt"))
        return '>';

    fprintf(stderr, "Error : invalid character [&%s;]", code);
    exit(5);
}

char readSpecialChar(reader cursor)
{
    char buffer[MAX_ESCAPE_CHARACTER_SIZE];
    for (int i = 0; i < MAX_ESCAPE_CHARACTER_SIZE - 1; i++)
    {
        nextCharacter(cursor);
        if (cursor->currentChar == ';')
        {
            buffer[i] = '\0';
            return parseSpecialChar(buffer);
        }

        buffer[i] = cursor->currentChar;
    }
    buffer[MAX_ESCAPE_CHARACTER_SIZE - 1] = '\0';
    fprintf(stderr, "Error : invalid character [&%s]", buffer);
    exit(5);
}

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
        if (cursor->currentChar == '&')
        {
            // Special character :
            char specialChar = readSpecialChar(cursor);
            sprintf(buffer + length, "%c", specialChar);
        }
        else
        {
            // Normal character
            sprintf(buffer + length, "%c", cursor->currentChar);
        }

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
