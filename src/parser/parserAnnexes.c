#include "parser.h"

int verifyAnnexes(char* tagName) {
    return 1;
}

t_tag* parseAnnexes(reader cursor) {
    t_parser p_annexe = createAnnexeUnitaireParser();

    tagList children = zeroOuPlus(p_annexe, cursor);

    if (children == EMPTY_LIST) {
        return TAG_NULL;
    }

    // Creation du tag
    t_tag* annexes = createTagWithChildren(e_annexes, children);

    return annexes;
}

t_parser createAnnexesParser() {
    t_parser parser;
    parser.execute = parseAnnexes;
    parser.verify = verifyAnnexes;

    return parser;
}