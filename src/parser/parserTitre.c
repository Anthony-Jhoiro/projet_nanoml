#include "parser.h"

int verifyTitre(char *tagName)
{
    char titleTag[] = "titre";
    return compareStr(tagName, titleTag);
}

t_tag *parseTitre(reader cursor)
{
    // On passe les espaces
    readSpaces(cursor);

    t_parser parserTexte = createTexteParser();

    t_tag* texte = parserTexte.execute(cursor);

    readClosingTag(cursor);
    assertCurrentTag(cursor, "titre");

    t_tag* titre = createTag(e_titre);
    
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
