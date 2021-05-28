#include "parser.h"

/**
 * Parse a filename and return a tag struct
 * \param filemane path to the file to parse
 * \return a tag structure representing the content of the file
 */
a_tag  parser(const char *filename)
{
    reader cursor = createReader(filename);

    t_parser parser = createTexteEnrichiParser();

    a_tag res = parser.execute(cursor);

    freeReader(cursor);

    return res;
}

/**
 * Return 1 if the character is a '<'
 * \param c the character to control
 */
int estChevronGauche(char c)
{
    return c == '<';
}

/**
 * Return 1 if the given character is a space char (' ', '\t', '\n', EOF)
 * \param c character to control
 */
int estEspace(char c)
{
    return c == ' ' || c == '\n' || c == '\t' || c == EOF;
}

/**
 * Read the file until a non space character is found
 * \param cursor Cursor used to read the file
 */
void readSpaces(reader cursor)
{
    while (estEspace(cursor->currentChar) && cursor->currentChar != EOF)
    {
        nextCharacter(cursor);
    }
}

/**
 * Try to use a parser zero or multiple times. Add the parsed tags to a tagList and return it.
 * \param parser parser that needed 
 * \param cursor reader used to read the file
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

/**
 * Function that takes an array of parsers as argument and try to execute them. 
 * Return the parsed tag or NULL if no parser worked
 * 
 * \param cursor cursor used to read the file
 * \param parsers array of parsers
 * \param nbParsers number of parsers in the array
 */
a_tag ou(reader cursor, t_parser *parsers, int nbParsers)
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


/**
 * Compare 2 char* char by char. If they are the same return 1 els, return 0
 * \param str1 first char* to compare
 * \param str2 second char* to compare
 */ 
int compareStr(const char *str1, const  char *str2)
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
