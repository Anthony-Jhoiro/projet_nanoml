#include "parser.h"

int verifyTitre(char *tagName)
{
    char titleTag[] = "titre";
    return compareStr(tagName, titleTag);
}

a_tag parseTitre(reader cursor)
{
    // On passe les espaces
    readSpaces(cursor);

    t_parser parserTexte = createTexteParser();

    a_tag  texte = parserTexte.execute(cursor);

    readClosingTag(cursor);
    assertCurrentTag(cursor, "titre");

    a_tag  titre = createTag(e_titre);
    
    addChild(titre, texte);

    return titre;
}

t_parser createTitreParser()
{
    t_parser parser;
    parser.execute = parseTitre;
    parser.verify = verifyTitre;

    return parser;
}
