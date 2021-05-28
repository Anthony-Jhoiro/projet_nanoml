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

int toRomanNumber(int num, char *buff, int buffSize)
{
    int i;
    for (int i = 0; i < buffSize; i++)
    {
        if (num >= 1000) // 1000 - m
        {
            buff[i] = 'M';
            num -= 1000;
        }

        else if (num >= 900) // 900 -  cm
        {
            if (i + 1 == buffSize)
            {
                fprintf(stderr, "Error : title index to big.");
                exit(11);
            }
            buff[i] = 'C';
            i++;
            buff[i] = 'M';
            num -= 900;
        }

        else if (num >= 500) // 500 - d
        {
            buff[i] = 'd';
            num -= 500;
        }

        else if (num >= 400) // 400 -  cd
        {
            if (i + 1 == buffSize)
            {
                fprintf(stderr, "Error : title index to big.");
                exit(11);
            }
            buff[i] = 'C';
            i++;
            buff[i] = 'D';
            num -= 400;
        }

        else if (num >= 100) // 100 - c
        {
            buff[i] = 'C';
            num -= 100;
        }

        else if (num >= 90) // 90 - xc
        {
            if (i + 1 == buffSize)
            {
                fprintf(stderr, "Error : title index to big.");
                exit(11);
            }
            buff[i] = 'X';
            i++;
            buff[i] = 'C';
            num -= 90;
        }

        else if (num >= 50) // 50 - l
        {
            buff[i] = 'L';
            num -= 50;
        }

        else if (num >= 40) // 40 - xl
        {
            if (i + 1 == buffSize)
            {
                fprintf(stderr, "Error : title index to big.");
                exit(11);
            }
            buff[i] = 'X';
            i++;
            buff[i] = 'L';
            num -= 40;
        }

        else if (num >= 10) // 10 - x
        {
            buff[i] = 'X';
            num -= 10;
        }

        else if (num >= 9) // 9 - ix
        {
            if (i + 1 == buffSize)
            {
                fprintf(stderr, "Error : title index to big.");
                exit(11);
            }
            buff[i] = 'I';
            i++;
            buff[i] = 'X';
            num -= 9;
        }

        else if (num >= 5) // 5 - v
        {
            buff[i] = 'V';
            num -= 5;
        }

        else if (num >= 4) // 4 - iv
        {
            if (i + 1 == buffSize)
            {
                fprintf(stderr, "Error : title index to big.");
                exit(11);
            }
            buff[i] = 'I';
            i++;
            buff[i] = 'V';
            num -= 4;
        }

        else if (num >= 1) // 1 - i
        {
            buff[i] = 'I';
            num -= 1;
        }
        else if (num <= 0)
        {
            return i;
        }
    }

    if (i + 1 == buffSize)
    {
        fprintf(stderr, "Error : title index to big.");
        exit(11);
    }
}
