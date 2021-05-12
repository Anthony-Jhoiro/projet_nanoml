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
    tagList children = zeroOuPlus(motSimple, cursor);

    // If the closing tag do not match throw an error
    readClosingTag(cursor);
    assertCurrentTag(cursor, "important");

    // Create tag
    tag *importantTag = createTagWithChildren(t_mot_important, children);

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
