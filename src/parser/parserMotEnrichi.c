#include "parser.h"

int verifyMotEnrichi(char* tagName) {
    // Tag name must be null or important
    return verifyMotSimple(tagName) || verifyImportant(tagName) || verifyRetourLigne(tagName);
}

a_tag  parseMotEnrichi(reader cursor) {
    t_parser parsers[3] = {createMotSimpleParser(), createImportantParser(), createRetourLigneParser()};
    int nbParser = 3;

    a_tag  motEnrichi = createTag(e_mot_enrichi);

    addChild(motEnrichi, ou(cursor, parsers, nbParser));

    return motEnrichi;
}

t_parser createMotEnrichiParser() {
    t_parser parser;
    parser.execute = parseMotEnrichi;
    parser.verify = verifyMotEnrichi;

    return parser;
}