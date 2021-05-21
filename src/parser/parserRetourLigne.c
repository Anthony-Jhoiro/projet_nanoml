#include "parser.h"

int verifyRetourLigne(char* tagName) {
    // Tag name must be null or important
    // ? WARNING : pas d'espaces entre "br" et "/"
    char retourLigneTag[] = "br/";
    return compareStr(tagName, retourLigneTag);
}

t_tag* parseRetourLigne(reader cursor) {

    t_tag* retourLigne = createTag(e_retour_ligne);

    return retourLigne;
}

t_parser createRetourLigneParser() {
    t_parser parser;
    parser.execute = parseRetourLigne;
    parser.verify = verifyRetourLigne;

    return parser;
}