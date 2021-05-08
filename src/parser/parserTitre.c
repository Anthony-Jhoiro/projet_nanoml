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

    char closingTag[BUFFER_SIZE];
    if ((!readClosingTag(cursor, closingTag)) || !verifyTitre(closingTag))
    {
        fprintf(stderr, "Error : expected </titre>\n");
        exit(1);
    }

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