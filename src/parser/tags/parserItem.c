#include "../parser.h"

int verifyItem(char *tagName)
{
    // Tag name must be null or important
    char itemTag[] = "item";
    return compareStr(tagName, itemTag);
}

a_tag parseItem(reader cursor)
{
    t_parser p_listeTexte = createListeTexteParser();
    t_parser p_texteListe = createTexteListeParser();

    t_parser parsers[2] = {p_listeTexte, p_texteListe};
    int nbParsers = 2;

    a_tag child = ou(cursor, parsers, nbParsers);

    a_tag item = createTag(e_item);

    addChild(item, child);

    if (child != TAG_NULL)
    {
        readClosingTag(cursor);
        assertCurrentTag(cursor, "item");
    }
    return item;
}

t_parser createItemParser()
{
    t_parser parser;
    parser.execute = parseItem;
    parser.verify = verifyItem;

    return parser;
}