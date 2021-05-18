#include "writer.h"

a_document initDoc()
{
    a_document doc = malloc(sizeof(document));
    doc->flux = stdout;
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

void printPrefix(a_document doc)
{
    for (int i = 0; i < doc->prefixLength; i++)
    {
        fprintf(doc->flux, "%c", doc->prefix[i]);
    }
}

void printSuffix(a_document doc)
{
    for (int i = doc->suffixLength - 1; i >= 0; i--)
    {
        fprintf(doc->flux, "%c", doc->suffix[i]);
    }
    fprintf(doc->flux, "\n");
}

void fillRow(a_document doc)
{
    printSpaces(doc, getMaxContentLength(doc));
    printSuffix(doc);
    printPrefix(doc);
    doc->contentLength = 0;
}

void fillRowNoPrefix(a_document doc)
{
    printSpaces(doc, getMaxContentLength(doc));
    printSuffix(doc);
    doc->contentLength = 0;
}