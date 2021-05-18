#ifndef WRITER_H
#define WRITER_H

#include "../tag/tag.h"

#define LINE_SIZE 50
#define MIDDLE_LINE_SIZE 25

typedef struct s_document
{
    char prefix[MIDDLE_LINE_SIZE];
    char suffix[MIDDLE_LINE_SIZE];
    FILE* flux;
    int prefixLength;
    int suffixLength;
    int contentLength;
} document;

typedef document *a_document;

// --- State --- //

typedef struct s_state
{
    int prefixLength;
    int suffixLength;
} t_state;

typedef t_state *a_state;

a_state saveState(a_document doc);
void freeState(a_state state);
void loadStatePrefix(a_state state, a_document doc);
void loadStateSuffix(a_state state, a_document doc);
void loadState(a_state state, a_document doc);

// --- Document --- //
int getMaxContentLength(a_document doc);
a_document initDoc();
void printPrefix(a_document doc);
void printSuffix(a_document doc);
void fillRow(a_document doc);
void fillRowNoPrefix(a_document doc);
void appendPrefix(a_document doc, char *newPrefix);
void appendSuffix(a_document doc, char *newSuffix);

// --- Utils --- //
void printUpperCase(a_document doc, char *word);
int strLength(char *word);
void printRow(a_document doc);
void printSpaces(a_document doc, int length);

// --- Elements --- //

void writeTexteEnrichi(a_document doc, tag *t);

void writeContenu(a_document doc, tag *t);
void writeSection(a_document doc, tag *t);

void writeListeTexte(a_document doc, tag *t);
void writeTexteListe(a_document doc, tag *t);
void writeListe(a_document doc, tag *t);

a_document initDoc();

#endif