#include "writer.h"

void printUpperCase(a_document doc, char *word)
{

    for (int i = 0; word[i] != '\0'; i++)
    {
        char c = word[i];
        if ('a' <= c && c <= 'z')
        {
            fprintf(doc->flux, "%c", c + DIST_A_a);
        }
        else
        {
            fprintf(doc->flux, "%c", c);
        }
    }
}

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

void printRow(a_document doc)
{
    printPrefix(doc);
    int length = getMaxContentLength(doc);
    if (length < 2)
    {
        fprintf(stderr, "Error: Row to short");
    }
    fprintf(doc->flux, "+");
    for (int i = 0; i < length - 2; i++)
    {
        fprintf(doc->flux, "-");
    }
    fprintf(doc->flux, "+");

    printSuffix(doc);
    doc->contentLength = 0;

}

void printSpaces(a_document doc, int length)
{
    for (int i = 0; i < length; i++)
    {
        fprintf(doc->flux, " ");
    }
}