#include "parser.h"

int verifyTexte(char* _) {
    // Tag name must be null or important
    return 1;
}

tag* parseTexte(reader cursor) {
    tag* texte = createTag(t_texte);

    t_parser p_motEnrichi = createMotEnrichiParser();

    tagList children = unOuPlus(p_motEnrichi, cursor);

    texte->children = children;

    return texte;
}

t_parser createTexteParser() {
    t_parser parser;
    parser.execute = parseTexte;
    parser.verify = verifyTexte;

    return parser;
}