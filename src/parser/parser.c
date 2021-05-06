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

tag* lireMotEnrichi(reader cursor) {

    t_parser mot_simple;
    mot_simple.execute = lireMotSimple;

    t_parser mot_important;
    mot_important.execute = lireMotImportant;

    t_parser parsers[2] = {mot_simple, mot_important};

    return ou(cursor,parsers, 2);
}

tag *readText(reader cursor)
{
    tag *t = createTag(t_texte);

    t_parser parserMotEnrichi;
    parserMotEnrichi.execute = lireMotEnrichi;

    t->children = unOuPlus(parserMotEnrichi, cursor);

    // tag *mot = lireMotSimple(cursor);

    // while (mot != NULL)
    // {
    //     addChild(t, mot);
    //     mot = lireMotSimple(cursor);
    // }

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



int passerTag(reader cursor, char *strTag)
{
    readSpaces(cursor);

    int i = 0;
    while (strTag[i] != '\0')
    {
        printf("%c, %c", cursor->currentChar, strTag[i]);
        if (cursor->currentChar != strTag[i])
        {
            return 0;
        }
        nextCharacter(cursor);
        i++;
    }
    return 1;
}

tag *lireMotImportant(reader cursor)
{
    printf("Lire mot important\n");
    // Find the right tag
    if (passerTag(cursor, "<important>"))
    {
        // Create Mot simple parser structure
        t_parser p;
        p.execute = lireMotSimple;

        // Read words
        tagList children = unOuPlus(p, cursor);

        // Create tag
        tag* importantTag = createTag(t_mot_important);

        importantTag->children = children;
        
        // If the closing tag do not match throw an error
        if (!passerTag(cursor, "</important>")) {
            fprintf(stderr, "Error : expected </important>");
            exit(1);
        }
        // return the tag
        return importantTag;
    }

    return TAG_NULL;
}

tagList unOuPlus(t_parser parser, reader cursor)
{
    tagList list = EMPTY_LIST;

    tag *t = parser.execute(cursor);
    while (t != NULL)
    {
        printTag(t);
        list = appendToList(list, t);
        t = parser.execute(cursor);
    }
    return list;
}

tag *ou(reader cursor, t_parser *parsers, int nbParsers)
{
    long position = ftell(cursor->file);

    tag *t = TAG_NULL;
    for (int i = 0; i < nbParsers; i++)
    {
        t = parsers[i].execute(cursor);
        if (t != TAG_NULL)
        {
            return t;
        }
        fseek(cursor->file, position, SEEK_SET);
    }

    return t;
}
