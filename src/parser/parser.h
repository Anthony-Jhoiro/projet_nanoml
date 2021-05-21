#ifndef PARSER_H
#define PARSER_H

#include "../tag/tag.h"
#include <stdio.h>

typedef struct s_reader {
    FILE* file;
    char currentChar;
    char currentTag[BUFFER_SIZE];
} t_reader;

typedef t_reader* reader;


typedef struct s_parser
{
    t_tag* (*execute)(reader);
    int (*verify)(char*);
} t_parser;

void assertCurrentTag(reader cursor, char* tagName);


void nextCharacter(reader cursor);

t_tag* parser(char* filename);

reader createReader(char* filename);

t_tag readTag(reader cursor, t_tagName name);

/**
 * TODO : words with more than 256 characters
 */

t_tag* readText(reader cursor);

int estEspace(char c);

void readSpaces(reader cursor);

int estChevronGauche(char c);

t_tag* lireMotSimple(reader cursor);

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
t_tag* lireMotImportant(reader cursor);

tagList zeroOuPlus(t_parser parser, reader cursor);

t_tag *ou(reader cursor, t_parser *parsers, int nbParsers);


int compareStr(char* str1, char* str2);


//----------- parser pour chaque tag ------------------
// Texte enrichi
t_parser createTexteEnrichiParser();

// Document
t_parser createDocumentParser();

// Annexes
t_parser createAnnexesParser();

// Annexe unitaire
t_parser createAnnexeUnitaireParser();

int verifyAnnexeUnitaire(char* tagName);


// Mot important
t_parser createImportantParser();

int verifyImportant(char *tagName);

// Mot simple
t_parser createMotSimpleParser();

// Liste
t_parser createListeParser();

int verifyListe(char* tagName);

// item
t_parser createItemParser();

// listeTexte
t_parser createListeTexteParser();

// texteListe
t_parser createTexteListeParser();

// Section
t_parser createSectionParser();

int verifySection(char* _);

// Contenu
t_parser createContenuParser();

// contenu unique
t_parser createContenuUniqueParser();

int verifyContenuUnique(char *tagName);

// Mot simple
t_parser createMotSimpleParser();

int verifyMotSimple(char* tagName);

// Mot Enrichi
t_parser createMotEnrichiParser();

int verifyMotEnrichi(char* tagName);

// retourLigne
t_parser createRetourLigneParser();

int verifyRetourLigne(char* tagName);

// texte
t_parser createTexteParser();

// titre
t_parser createTitreParser();

int verifyTitre(char *tagName);



t_tag* lireMotSimple(reader cursor);

t_tag* lireMotImportant(reader cursor);

t_tag* lireMotEnrichi(reader cursor);


int readOpeningTag(reader cursor);

void readClosingTag(reader cursor);

#endif
