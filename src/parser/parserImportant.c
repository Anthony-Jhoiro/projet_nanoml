#include "parser.h"

int verifyImportant(char *tagName)
{
    char importantTag[] = "important";
    return compareStr(tagName, importantTag);
}



tag *parseImportant(reader cursor)
{
    // Create Mot simple parser structure
    t_parser motSimple = createMotSimpleParser();

    // Read words
    tagList children = unOuPlus(motSimple, cursor);

    // If the closing tag do not match throw an error
    if ((!readClosingTag(cursor)) || !verifyImportant(cursor->currentTag))
    {
        fprintf(stderr, "Error : expected </important>");
        exit(1);
    }

    // Create tag
    tag *importantTag = createTag(t_mot_important);

    importantTag->children = children;

    // return the tag
    return importantTag;
}

t_parser createImportantParser()
{
    t_parser parser;
    parser.execute = parseImportant;
    parser.verify = verifyImportant;

    return parser;
}
