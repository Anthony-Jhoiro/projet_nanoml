#include "parser.h"

int verifyRetourLigne(char* tagName) {
    // Tag name must be null or important
    // ? WARNING : pas d'espaces entre "br" et "/"
    char retourLigneTag[] = "br/";
    return compareStr(tagName, retourLigneTag);
}

tag* parseRetourLigne(reader cursor) {

    tag* retourLigne = createTag(t_retour_ligne);

    return retourLigne;
}

t_parser createRetourLigneParser() {
    t_parser parser;
    parser.execute = parseRetourLigne;
    parser.verify = verifyRetourLigne;

    return parser;
}