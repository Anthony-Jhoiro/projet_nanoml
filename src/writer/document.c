#include "writer.h"
#include <stdarg.h>

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

void writeBufferInDoc(document *doc, char* buff, int wordLength) {
    int maxLength = getMaxContentLength(doc);

    if (wordLength > maxLength)
    {
        fillRow(doc);
        int maxLength = getMaxContentLength(doc);
        if (wordLength > maxLength)
        {
            fprintf(stderr, "Error: Can not write word [%s]", buff);
            exit(11);
        }
    }
    fprintf(doc->flux, "%s", buff);
    doc->contentLength += wordLength;
    if (wordLength != maxLength) {
        fprintf(doc->flux, " ");
        doc->contentLength++;
    }
}

void writeInDoc(document *doc, char *format, ...)
{
    va_list args;
    va_start(args, format);
    char buff[BUFFER_SIZE + 2];

    int length = vsprintf(buff, format, args);

    buff[length] = '\0';

    int wordLength = strLength(buff);
    
    writeBufferInDoc(doc, buff, length);

    va_end(args);
}

void writeInDocUppercase(document *doc, char *format, ...){

    va_list args;
    va_start(args, format);
    char buff[BUFFER_SIZE + 2];

    int length = vsprintf(buff, format, args);

    buff[length] = '\0';

    int wordLength = strLength(buff);

    // uppercase the buffer
    for (int i = 0; buff[i] != '\0'; i++){

        if(buff[i] >= 'a' && buff[i] <= 'z'){
            buff[i] = buff[i] + ('A' - 'a');
        }

    }
    
    writeBufferInDoc(doc, buff, length);

    va_end(args);

}


