#include "parser.h"

void parser(char *filename)
{
    reader cursor = createReader(filename);

    t_parser parser = createTitreParser();

    tag *res = parser.execute(cursor);

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

// tag* lireMotEnrichi(reader cursor) {

//     t_parser mot_simple;
//     mot_simple.execute = lireMotSimple;

//     t_parser mot_important;
//     mot_important.execute = lireMotImportant;

//     t_parser parsers[2] = {mot_simple, mot_important};

//     return ou(cursor,parsers, 2);
// }

// tag *readText(reader cursor)
// {
//     tag *t = createTag(t_texte);

//     t_parser parserMotEnrichi;
//     parserMotEnrichi.execute = lireMotEnrichi;

//     t->children = unOuPlus(parserMotEnrichi, cursor);

//     // tag *mot = lireMotSimple(cursor);

//     // while (mot != NULL)
//     // {
//     //     addChild(t, mot);
//     //     mot = lireMotSimple(cursor);
//     // }

//     return t;
// }

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
 * 
 */
tagList unOuPlus(t_parser parser, reader cursor)
{
    tagList list = EMPTY_LIST;
    char buffer[BUFFER_SIZE];

    // Fail if not a valid tag
    if (!readOpeningTag(cursor, buffer))
    {
        fprintf(stderr, "Error : invalid tag.");
        exit(2);
    }

    // While the verify function return true, we use the parser
    while (parser.verify(buffer))
    {
        list = appendToList(list, parser.execute(cursor));

        
        int readStatus = readOpeningTag(cursor, buffer);
        if (!readStatus)
        {
            fprintf(stderr, "Error : invalid tag.");
            exit(2);
        }

        // If this is a closing tag or the end of the file return the list
        if (readStatus == 2 || cursor->currentChar == EOF)
        {
            return list;
        }
    }

    return list;
}

tag *ou(reader cursor, t_parser *parsers, int nbParsers)
{
    char buff[BUFFER_SIZE];
    if (!readOpeningTag(cursor, buff))
    {
        fprintf(stderr, "Invalid tag");
        exit(3);
    }

    for (int i = 0; i < nbParsers; i++)
    {
        if (parsers[i].verify(buff))
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

int readOpeningTag(reader cursor, char *buff)
{
    readSpaces(cursor);

    if (cursor->currentChar != '<')
    {
        buff[0] = '\0';
        return 1;
    }
    nextCharacter(cursor);

    if (cursor->currentChar == '/')
    {
        return 2;
    }

    int buffIndex = 0;

    while (cursor->currentChar != '>' && !estEspace(cursor->currentChar))
    {
        buff[buffIndex] = cursor->currentChar;
        nextCharacter(cursor);
        buffIndex++;
    }
    buff[buffIndex] = '\0';

    readSpaces(cursor); 
    
    int status = cursor->currentChar == '>';

    nextCharacter(cursor);

    return status;
}

int readClosingTag(reader cursor, char *buff)
{
    readSpaces(cursor);
    int buffIndex = 0;

    if (cursor->currentChar != '/')
    {
        return 0;
    }

    nextCharacter(cursor);

    while (cursor->currentChar != '>' && !estEspace(cursor->currentChar))
    {
        buff[buffIndex] = cursor->currentChar;
        buffIndex++;
        nextCharacter(cursor);
    }
    buff[buffIndex] = '\0';

    

    readSpaces(cursor);
    int status =  cursor->currentChar == '>';
    
    // We read one last character to start the next read at 
    // the begining of the next grammar item
    nextCharacter(cursor);    
    return status;
}