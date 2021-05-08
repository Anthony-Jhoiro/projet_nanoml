#include "parser.h"

int verifyListe(char* tagName) {
    // Tag name must be null or important
    char listTag[] = "liste";
    return compareStr(tagName, listTag);
}

tag* parseListe(reader cursor) {

    t_parser p_item = createItemParser();

    tagList children = unOuPlus(p_item, cursor);


    if ((!readClosingTag(cursor)) || !verifyListe(currentTag))
    {
        fprintf(stderr, "Error : expected </liste>");
        exit(1);
    }

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