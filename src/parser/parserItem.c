#include "parser.h"

int verifyItem(char *tagName)
{
    // Tag name must be null or important
    char itemTag[] = "item";
    return compareStr(tagName, itemTag);
}

tag *parseItem(reader cursor)
{
    t_parser p_listeTexte = createListeTexteParser();
    t_parser p_texteListe = createTexteListeParser();

    t_parser parsers[2] = {p_listeTexte, p_texteListe};
    int nbParsers = 2;

    tag *child = ou(cursor, parsers, nbParsers);

    if (child == TAG_NULL)
    {
        fprintf(stderr, "\e[0;35mError: expected liste or texte.\e[0;37m");
        exit(4);
    }

    readClosingTag(cursor);
    assertCurrentTag(cursor, "item");

    tag *item = createTag(t_item);
    addChild(item, child);
    return item;
}

t_parser createItemParser()
{
    t_parser parser;
    parser.execute = parseItem;
    parser.verify = verifyItem;

    return parser;
}