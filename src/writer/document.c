#include "writer.h"
#include <stdarg.h>


/**
 * \brief Crée un docuement et initialise toutes les valeures
 * \param flux : flux de destination pour le document
 */
a_document initDoc(FILE* flux)
{
    a_document doc = malloc(sizeof(document));
    doc->flux = flux;
    doc->prefixLength = 0;
    doc->suffixLength = 0;
    doc->contentLength = 0;
    doc->uppercase = 0;
    doc->titleIndex = 1;
    return doc;
}

/**
 * \brief Free the memory of a document
 */
void freeDoc(a_document doc) {
    free(doc);
}

/**
 * \brief Return the maximum number of caracters that can be written on the line
 */
int getMaxContentLength(a_document doc)
{
    return LINE_SIZE - doc->prefixLength - doc->suffixLength - doc->contentLength;
}

/**
 * \brief Ajoute la chaine de caractère au préfixe
 */
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

/**
 * \brief Ajoute la chaine de caractère au suffixe
 */
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

/**
 * Ecrit le préfixe du docuement dans le document
 */
void printPrefix(a_document doc)
{
    for (int i = 0; i < doc->prefixLength; i++)
    {
        fprintf(doc->flux, "%c", doc->prefix[i]);
    }
}

/**
 * \brief Ecrit le suffixe du docuement. Le suffixe est écrit à l'envers pour simplifer le développement
 */
void printSuffix(a_document doc)
{
    for (int i = doc->suffixLength - 1; i >= 0; i--)
    {
        fprintf(doc->flux, "%c", doc->suffix[i]);
    }
    fprintf(doc->flux, "\n");
}

/**
 * \brief Rempli la ligne avec des espaces, écrits le suffixe et retourne à la ligne. N'écrit pas le préfixe
 */
void fillRowNoPrefix(a_document doc)
{
    printSpaces(doc, getMaxContentLength(doc));
    printSuffix(doc);
    doc->contentLength = 0;
}

/**
 * \brief Rempli la ligne avec des espaces, écrits le suffixe, retourne à la ligne et ajoute le préfixe
 */
void fillRow(a_document doc)
{
    fillRowNoPrefix(doc);
    printPrefix(doc);
}



/**
 * \brief Ecrit un buffer dans le document
 */
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

/**
 * \brief Ecrit dans le document. Cette fonction a le même prototype de `fprintf` 
 * mais le flux est remplacé par un document
 */
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


/**
 * \brief Ecrit dans le document en majuscule. Cette fonction a le même prototype de `fprintf` 
 * mais le flux est remplacé par un document
 */
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
            buff[i] = buff[i] + DIST_A_a;
        }

    }
    
    writeBufferInDoc(doc, buff, length);

    va_end(args);

}


