#ifndef WRITER_H
#define WRITER_H

#include "../tag/tag.h"

#define LINE_SIZE 50
#define MIDDLE_LINE_SIZE 25

typedef struct s_document
{
    char prefix[MIDDLE_LINE_SIZE];
    char suffix[MIDDLE_LINE_SIZE];
    int prefixLength;
    int suffixLength;
    int contentLength;
} document;

typedef document *a_document;

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

void writeTexteEnrichi(a_document doc, tag *t);

a_document initDoc();

#endif