#ifndef PARSER_H
#define PARSER_H

#include "../tag/tag.h"
#include <stdio.h>

typedef struct s_reader {
    FILE* file;
    char currentChar;
} t_reader;

typedef t_reader* reader;


typedef struct s_parser
{
    tag* (*execute)(reader);
    int (*verify)(char*);
} t_parser;


void nextCharacter(reader cursor);

void parser(char* filename);

reader createReader(char* filename);

tag readTag(reader cursor, tagsNames name);

/**
 * TODO : words with more than 256 characters
 */

tag* readText(reader cursor);

int estEspace(char c);

void readSpaces(reader cursor);

int estChevronGauche(char c);

tag* lireMotSimple(reader cursor);

/**
 * \brief read an important word in the file (it reads "<important> + content + </important>")
 * 
 * \param cursor the file's cursor
 * 
 * \return an important tag
 * 
 * imporant tag exemple :
 * <important> exemple </important>
 * (spaces are facultative)
 */
tag* lireMotImportant(reader cursor);

tagList unOuPlus(t_parser parser, reader cursor);

tag *ou(reader cursor, t_parser *parsers, int nbParsers);


int compareStr(char* str1, char* str2);


//----------- parser pour chaque tag ------------------

// Document
t_parser createDocumentParser();

// Annexes
t_parser createAnnexeParser();

// Mot important
t_parser createImportantParser();

int verifyImportant(char *tagName);

// Mot simple
t_parser createMotSimpleParser();

// Liste
t_parser createListeParser();

// item
t_parser createItemParser();

// Section
t_parser createSectionParser();

// Mot simple
t_parser createMotSimpleParser();

int verifyMotSimple(char* tagName);

// Mot Enrichi
t_parser createMotEnrichiParser();

// retourLigne
t_parser createRetourLigneParser();

int verifyRetourLigne(char* tagName);



tag* lireMotSimple(reader cursor);

tag* lireMotImportant(reader cursor);

tag* lireMotEnrichi(reader cursor);


int readOpeningTag(reader cursor, char* buff);

int readClosingTag(reader cursor, char* buff);

#endif
