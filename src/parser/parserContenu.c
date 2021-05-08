#include "parser.h"

int verifyContenu(char *tagName)
{
    // Tag name must be null or important
    return verifyContenuUnique(tagName);
}


tag *parseContenu(reader cursor)
{ 
    t_parser p_contenuUnique = createContenuUniqueParser();

    tagList children = unOuPlus(p_contenuUnique, cursor);

    tag* contenuTag = createTag(t_contenu);
    contenuTag->children = children;

    return contenuTag;
}

t_parser createContenuParser()
{
    t_parser parser;
    parser.execute = parseContenu;
    parser.verify = verifyContenu;

    return parser;
}