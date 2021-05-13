#include "parser.h"

tag* parser(char *filename)
{
    reader cursor = createReader(filename);

    t_parser parser = createTexteEnrichiParser();

    tag *res = parser.execute(cursor);

    fclose(cursor->file);

    return res;
}

void nextCharacter(reader cursor)
{

    cursor->currentChar = fgetc(cursor->file);
    printf("\e[0;34m%c\e[0;37m", cursor->currentChar);

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

int passerTag(reader cursor, char *strTag)
{
    readSpaces(cursor);

    int i = 0;
    while (strTag[i] != '\0')
    {
        if (cursor->currentChar != strTag[i])
        {
            return 0;
        }
        nextCharacter(cursor);
        i++;
    }
    return 1;
}

/**
 * TODO handle errors && case empty tag
 * TODO : rename zero ou plus
 * 
 */
tagList zeroOuPlus(t_parser parser, reader cursor)
{
    tagList list = EMPTY_LIST;

    // Fail if not a valid tag
    readOpeningTag(cursor);

    // While the verify function return true, we use the parser
    while (parser.verify(cursor->currentTag))
    {
        list = appendToList(list, parser.execute(cursor));

        int readStatus = readOpeningTag(cursor);

        // If this is a closing tag or the end of the file return the list
        if (readStatus == -1 || cursor->currentChar == EOF)
        {
            return list;
        }
    }

    return list;
}

tag *ou(reader cursor, t_parser *parsers, int nbParsers)
{
    for (int i = 0; i < nbParsers; i++)
    {
        if (parsers[i].verify(cursor->currentTag))
        {
            return parsers[i].execute(cursor);
        }
    }
    return TAG_NULL;
}

int compareStr(char *str1, char *str2)
{

    int cpt = 0;

    while (str1[cpt] != '\0')
    {
        if (str1[cpt] != str2[cpt])
        {
            return 0;
        }
        cpt++;
    }

    return str2[cpt] == '\0';
}

/**
 * Read a tag. If the tag is not valid throw an error and exit the process. If the second character of the tag is a '/' 
 * this is a closing tag also we are returning -1 and we d not read the rest of the tag. If the tag is valid, its 
 * text content is moved to cursor->currentTag.
 * 
 * Exemples :
 * 
 * * "<hello>" => return 1, cursor->currentTag = 'hello'
 * * "</hello>" => return -1, cursor->currentTag keeps its previous value
 * * "<hello $" => exit the process with error code 3.
 * 
 * :param cursor The cursor used to read the file. 
 * 
 */
int readOpeningTag(reader cursor)
{
    readSpaces(cursor);

    int status;

    if (cursor->currentChar != '<')
    {
        cursor->currentTag[0] = '\0';
        return 1;
    }
    nextCharacter(cursor);

    if (cursor->currentChar == '/')
    {
        return -1;
    }

    int buffIndex = 0;

    while (cursor->currentChar != '>' && !estEspace(cursor->currentChar))
    {
        cursor->currentTag[buffIndex] = cursor->currentChar;
        nextCharacter(cursor);
        buffIndex++;
    }
    cursor->currentTag[buffIndex] = '\0';

    readSpaces(cursor);

    if (cursor->currentChar == '>')
    {
        nextCharacter(cursor);
        return 1;
    }

    fprintf(stderr, "\n\e[0;35mError: Invalid tag\e[0;37m\n");
    exit(3);
}

/**
 * Read a closing tag. If the tag is not valid throw an error and exit the process with status 2
 */
void readClosingTag(reader cursor)
{
    readSpaces(cursor);
    int buffIndex = 0;

    if (cursor->currentChar == '/')
    {
        nextCharacter(cursor);

        while (cursor->currentChar != '>' && !estEspace(cursor->currentChar))
        {
            cursor->currentTag[buffIndex] = cursor->currentChar;
            buffIndex++;
            nextCharacter(cursor);
        }
        cursor->currentTag[buffIndex] = '\0';

        readSpaces(cursor);
        if (cursor->currentChar == '>')
        {
            nextCharacter(cursor);
            return;
        }
    }

    fprintf(stderr, "\n\e[0;35mError: Invalid closing tag\e[0;37m\n");
    exit(2);
}

/**
 * Assert that the cursor current tag name is equal to the given tagname. 
 * If it fails exit the process with error code 1.
 */
void assertCurrentTag(reader cursor, char *tagName)
{
    if (!compareStr(cursor->currentTag, tagName))
    {
        fprintf(stderr, "\n\e[0;35mError: expecting \"%s\", got [%s]\e[0;37m\n", tagName, cursor->currentTag);
        exit(1);
    }
}
