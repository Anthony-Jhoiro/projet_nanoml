#include "../parser.h"

int verifyContenuUnique(char *tagName)
{
    // Tag name must be null or important
    return verifySection(tagName) || verifyTitre(tagName) || verifyMotEnrichi(tagName) || verifyListe(tagName);
}

a_tag parseContenuUnique(reader cursor)
{
    int nbParsers = 4;

    t_parser parsers[4] = {
        createSectionParser(),
        createTitreParser(),
        createMotEnrichiParser(),
        createListeParser()
    }; 

    return ou(cursor, parsers, nbParsers);
}

t_parser createContenuUniqueParser()
{
    t_parser parser;
    parser.execute = parseContenuUnique;
    parser.verify = verifyContenuUnique;

    return parser;
}