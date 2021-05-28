#ifndef PARSER_H
#define PARSER_H

#include "../tag/tag.h"
#include "reader/reader.h"

#define MAX_ESCAPE_CHARACTER_SIZE 6

/**
 * Defines a parser.
 * A parser is a structure composed of 2 functions :
 * - `execute` => a function that parse a a texte using a `reader`and returning a tag
 * - `verify` => a function that takes a `char*` represeting the current tag as a parameter and return true if it is its tag
 */
typedef struct s_parser
{
    a_tag  (*execute)(reader);
    int (*verify)(char*);
} t_parser;

/**
 * Check if the current tag is equal to the secound parameter. If it is not, thorw an error and exit the programm 
 * \param cursor cursor of the current file with a current tag
 * \param tagName expected name of the tag
*/
void assertCurrentTag(reader cursor, char* tagName);

/**
 * Parse a filename and return a tag struct
 * \param filemane path to the file to parse
 * \return a tag structure representing the content of the file
 */
a_tag parser(const char* filename);

/**
 * Return 1 if the given character is a space char (' ', '\t', '\n', EOF)
 * \param c character to control
 */
int estEspace(char c);

/**
 * Read the file until a non space character is found
 * \param cursor Cursor used to read the file
 */
void readSpaces(reader cursor);

/**
 * Return 1 if the character is a '<'
 * \param c the character to control
 */
int estChevronGauche(char c);

/**
 * Try to use a parser zero or multiple times. Add the parsed tags to a tagList and return it.
 * \param parser parser that needed 
 * \param cursor reader used to read the file
 */
tagList zeroOuPlus(t_parser parser, reader cursor);

/**
 * Function that takes an array of parsers as argument and try to execute them. 
 * Return the parsed tag or NULL if no parser worked
 * 
 * \param cursor cursor used to read the file
 * \param parsers array of parsers
 * \param nbParsers number of parsers in the array
 */
a_tag ou(reader cursor, t_parser *parsers, int nbParsers);

/**
 * Compare 2 char* char by char. If they are the same return 1 els, return 0
 * \param str1 first char* to compare
 * \param str2 second char* to compare
 */ 
int compareStr(const char* str1, const char* str2);


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




/**
 * Read a tag. If the tag is not valid throw an error and exit the process. If the second character of the tag is a '/' 
 * this is a closing tag also we are returning -1 and we d not read the rest of the tag. If the tag is valid, its 
 * text content is moved to cursor->currentTag.
 * 
 * Exemples :
 * 
 * * "<hello>" => return 1, cursor->currentTag = 'hello'
 * * "</hello>" => return -1, cursor->currentTag keeps its previous value
 * * "<hello $" => exit the process with error code 3.
 * 
 * :param cursor The cursor used to read the file. 
 * 
 */
int readOpeningTag(reader cursor);

/**
 * Read a closing tag. If the tag is not valid throw an error and exit the process with status 2
 */
void readClosingTag(reader cursor);

#endif
