#include "parser.h"

int verifyListeTexte(char* tagName) {
    return verifyListe(tagName);
}

t_tag* parseListeTexte(reader cursor) {
    t_parser p_liste = createListeParser();
    t_parser p_texteListe = createTexteListeParser();

    t_tag* liste = p_liste.execute(cursor);

    if (liste == TAG_NULL) {
        return TAG_NULL;
    }

    // Creation du tag
    t_tag* listeText = createTag(e_liste_texte);

    // Ajout de la liste
    addChild(listeText, liste);

    // Search text
    t_tag* texteListe = p_texteListe.execute(cursor);

    if (texteListe != TAG_NULL) {
        addChild(listeText, texteListe);
    }    

    return listeText;
}

t_parser createListeTexteParser() {
    t_parser parser;
    parser.execute = parseListeTexte;
    parser.verify = verifyListeTexte;

    return parser;
}