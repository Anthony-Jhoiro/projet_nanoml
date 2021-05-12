#include "parser.h"

int verifyTexte(char* _) {
    // Tag name must be null or importants
    return 1;
}

tag* parseTexte(reader cursor) {
    t_parser p_motEnrichi = createMotEnrichiParser();

    tagList children = zeroOuPlus(p_motEnrichi, cursor);

    if (children == EMPTY_LIST) {
        return TAG_NULL;
    }

    tag* texte = createTagWithChildren(t_texte, children);

    return texte;
}

t_parser createTexteParser() {
    t_parser parser;
    parser.execute = parseTexte;
    parser.verify = verifyTexte;

    return parser;
}