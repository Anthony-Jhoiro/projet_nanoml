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

    // tag *child;

    // child = p_listeTexte.execute(cursor);

    // if (child == TAG_NULL)
    // {
    //     printf("Parse texte");
    //     t_parser p_texteListe = createTexteListeParser();
    //     child = p_texteListe.execute(cursor);
    // }

    if (child == TAG_NULL)
    {
        fprintf(stderr, "Error, expected liste or texte.");
        exit(4);
    }

    if ((!readClosingTag(cursor)) || !verifyItem(currentTag))
    {
        fprintf(stderr, "Error : expected </item>");
        exit(1);
    }

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