#include "writer.h"

int strLength(char *word)
{
    if (word == NULL)
    {
        fprintf(stderr, "ERROR: NULL WORD");
        exit(12);
    }
    int i = 0;
    while (word[i] != '\0')
    {
        i++;
    }
    return i;
}

void printRow(int length)
{
    if (length < 2)
    {
        fprintf(stderr, "Error: Row to short");
    }
    printf("+");
    for (int i = 0; i < length - 2; i++)
    {
        printf("-");
    }
    printf("+");
}

void printSpaces(int length)
{
    for (int i = 0; i < length; i++)
    {
        printf(" ");
    }
}

void printPrefix(a_document doc)
{
    for (int i = 0; i < doc->prefixLength; i++)
    {
        printf("%c", doc->prefix[i]);
    }
}

void printSuffix(a_document doc)
{
    for (int i = doc->suffixLength - 1; i >= 0; i--)
    {
        printf("%c", doc->suffix[i]);
    }
    printf("\n");
}

void fillRow(a_document doc)
{
    printSpaces(LINE_SIZE - (doc->contentLength + doc->suffixLength + doc->prefixLength));
    printSuffix(doc);
    printPrefix(doc);
    doc->contentLength = 0;
}

void fillRowNoPrefix(a_document doc)
{
    printSpaces(LINE_SIZE - (doc->contentLength + doc->suffixLength + doc->prefixLength));
    printSuffix(doc);
    doc->contentLength = 0;
}

a_document initDoc()
{
    a_document doc = malloc(sizeof(document));
    doc->prefixLength = 0;
    doc->suffixLength = 0;
    doc->contentLength = 0;
    return doc;
}

int getMaxContentLength(a_document doc)
{
    return LINE_SIZE - doc->prefixLength - doc->suffixLength - doc->contentLength;
}

void appendPrefix(a_document doc, char *newPrefix)
{
    int i = 0;
    while (newPrefix[i] != '\0')
    {
        doc->prefix[doc->prefixLength] = newPrefix[i];
        doc->prefixLength++;
        i++;
    }
}

void appendSuffix(a_document doc, char *newSuffix)
{
    int i = 0;
    while (newSuffix[i] != '\0')
    {
        doc->suffix[doc->suffixLength] = newSuffix[i];
        doc->suffixLength++;
        i++;
    }
}

void writeMotSimple(a_document doc, tag *t)
{
    char *word = t->content;

    int maxLength = getMaxContentLength(doc);

    int wordLength = strLength(word);

    if (wordLength > maxLength)
    {
        fillRow(doc);
        int maxLength = getMaxContentLength(doc);
        if (wordLength > maxLength)
        {
            fprintf(stderr, "Error: Can not write word [%s]", word);
            exit(11);
        }
    }
    printf("%s", word);
    doc->contentLength += wordLength;
    if (wordLength != maxLength)
    {
        printf(" ");
        doc->contentLength++;
    }
}

void writeMotEnrichi(a_document doc, tag *t)
{
    tag *child = t->children->element;

    if (child->tagName == t_mot_simple)
    {
        writeMotSimple(doc, child);
    }
}

void writeContenu(a_document doc, tag *t)
{
    item *child = t->children;
    while (child != EMPTY_LIST)
    {
        tagsNames name = child->element->tagName;
        if (name == t_mot_enrichi)
        {
            writeMotEnrichi(doc, child->element);
        }
        else if (name == t_section)
        {
            // TODO : implement
        }
        else if (name == t_titre)
        {
            // TODO : implement
        }
        else if (name == t_liste)
        {
            // TODO : implement
        }

        child = child->next;
    }
}

void writeDocument(a_document doc, tag *t)
{
    a_state previousState = saveState(doc);

    printRow(getMaxContentLength(doc));
    appendPrefix(doc, "|");
    appendSuffix(doc, "|");
    fillRow(doc);

    tag *childContenu = t->children->element;

    writeContenu(doc, childContenu);

    fillRowNoPrefix(doc);
    loadState(previousState, doc);

    printRow(getMaxContentLength(doc));
}

void writeTexteEnrichi(a_document doc, tag *t)
{
    tag *childDocument = t->children->element;

    writeDocument(doc, childDocument);
}