#include "parser.h"

int verifyTitre(char *tagName)
{
    char titleTag[] = "titre";
    return compareStr(tagName, titleTag);
}

tag *parseTitre(reader cursor)
{
    // On passe les espaces
    readSpaces(cursor);

    t_parser parserTexte = createTexteParser();

    tag* texte = parserTexte.execute(cursor);

    readClosingTag(cursor);
    assertCurrentTag(cursor, "titre");

    tag* titre = createTag(t_titre);
    
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
