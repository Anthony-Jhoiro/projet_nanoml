#include "parser.h"

int verifyTexteListe(char* tagName) {
    // Tag name must be null or important
    return 1;
}

tag* parseTexteListe(reader cursor) {
    
    t_parser p_texte = createTexteParser();
    t_parser p_listeTexte = createListeTexteParser();

    tag* texte = p_texte.execute(cursor);

    if (texte == TAG_NULL) {
        return TAG_NULL;
    }

    tag* texteListe = createTag(t_texte_liste);
    addChild(texteListe, texte);

    // Read Liste-texte
    if (p_listeTexte.verify(currentTag)) {
        tag* listeTexte = p_listeTexte.execute(cursor);
        if (listeTexte != TAG_NULL) {
            addChild(texteListe, listeTexte);
        }

    }


    return texteListe;
}

t_parser createTexteListeParser() {
    t_parser parser;
    parser.execute = parseTexteListe;
    parser.verify = verifyTexteListe;

    return parser;
}