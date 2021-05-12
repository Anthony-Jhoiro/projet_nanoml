#include "parser.h"

int verifyAnnexes(char* tagName) {
    return 1;
}

tag* parseAnnexes(reader cursor) {
    t_parser p_annexe = createAnnexeUnitaireParser();

    tagList children = zeroOuPlus(p_annexe, cursor);

    if (children == EMPTY_LIST) {
        return TAG_NULL;
    }

    // Creation du tag
    tag* annexes = createTagWithChildren(t_annexe, children);

    return annexes;
}

t_parser createAnnexesParser() {
    t_parser parser;
    parser.execute = parseAnnexes;
    parser.verify = verifyAnnexes;

    return parser;
}