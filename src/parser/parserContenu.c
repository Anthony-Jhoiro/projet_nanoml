#include "parser.h"

int verifyContenu(char *tagName)
{
    // Tag name must be null or important
    return verifyContenuUnique(tagName);
}


a_tag parseContenu(reader cursor)
{ 
    t_parser p_contenuUnique = createContenuUniqueParser();

    tagList children = zeroOuPlus(p_contenuUnique, cursor);

    a_tag contenuTag = createTagWithChildren(e_contenu, children);

    return contenuTag;
}

t_parser createContenuParser()
{
    t_parser parser;
    parser.execute = parseContenu;
    parser.verify = verifyContenu;

    return parser;
}