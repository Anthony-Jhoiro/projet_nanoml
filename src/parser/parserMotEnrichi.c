#include "parser.h"

int verifyMotEnrichi(char* tagName) {
    // Tag name must be null or important
    return verifyMotSimple(tagName) || verifyImportant(tagName) || verifyRetourLigne(tagName);
}

tag* parseMotEnrichi(reader cursor) {
    t_parser parsers[3] = {createMotSimpleParser(), createImportantParser(), createRetourLigneParser()};
    int nbParser = 3;

    tag* motEnrichi = createTag(t_mot_enrichi);

    addChild(motEnrichi, ou(cursor, parsers, nbParser));

    return motEnrichi;
}

t_parser createMotEnrichiParser() {
    t_parser parser;
    parser.execute = parseMotEnrichi;
    parser.verify = verifyMotEnrichi;

    return parser;
}