#include "parser.h"

int verifyListe(char* tagName) {
    // Tag name must be null or important
    char listTag[] = "liste";
    return compareStr(tagName, listTag);
}

tag* parseListe(reader cursor) {

    t_parser p_item = createItemParser();

    tagList children = zeroOuPlus(p_item, cursor);


    readClosingTag(cursor);
    assertCurrentTag(cursor, "liste");

    tag* liste = createTag(t_liste);

    liste->children = children;

    return liste;
}

t_parser createListeParser() {
    t_parser parser;
    parser.execute = parseListe;
    parser.verify = verifyListe;

    return parser;
}