#include "../parser.h"


/**
 * Always return true
 */
int verifyAnnexes(char* tagName) {
    return 1;
}

/**
 * Parse a file using the reader to get an annexe.
 * @param cursor cursor used to parse the file
 * @return the finded tag
 */
a_tag  parseAnnexes(reader cursor) {
    t_parser p_annexe = createAnnexeUnitaireParser();

    tagList children = zeroOuPlus(p_annexe, cursor);

    if (children == EMPTY_LIST) {
        return TAG_NULL;
    }

    // Creation du tag
    a_tag  annexes = createTagWithChildren(e_annexes, children);

    return annexes;
}

t_parser createAnnexesParser() {
    t_parser parser;
    parser.execute = parseAnnexes;
    parser.verify = verifyAnnexes;

    return parser;
}