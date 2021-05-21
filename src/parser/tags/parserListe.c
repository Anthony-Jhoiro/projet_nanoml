#include "../parser.h"

int verifyListe(char* tagName) {
    // Tag name must be null or important
    char listTag[] = "liste";
    return compareStr(tagName, listTag);
}

a_tag  parseListe(reader cursor) {

    t_parser p_item = createItemParser();

    tagList children = zeroOuPlus(p_item, cursor);


    readClosingTag(cursor);
    assertCurrentTag(cursor, "liste");

    a_tag  liste = createTagWithChildren(e_liste, children);

    return liste;
}

t_parser createListeParser() {
    t_parser parser;
    parser.execute = parseListe;
    parser.verify = verifyListe;

    return parser;
}