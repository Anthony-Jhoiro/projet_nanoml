#include "tag.h"

/**
 * \brief This function creates a tag and allocate the memory.
 * \param name The name of the tag (see tagsNames)
 */
tag *createTag(tagsNames name)
{
    return createTagMotSimple(name, NULL);}

/**
 * \brief This function creates a tag and allocate the memory.
 * \param name The name of the tag (see tagsNames)
 * \param content The content of the tag
 */
tag *createTagMotSimple(tagsNames name, char* content) {
    tag *t = malloc(sizeof(tag));

    t->tagName = name;
    t->content = content;
    t->children = EMPTY_LIST;

    return t;
}

void addChild(tag *father, tag *child)
{
    father->children = appendToList(father->children, child);
}

void printTagName(tagsNames name)
{
    if (name == b_document)
    {
        printf("document>");
    }
    else if (name == b_annexe)
    {
        printf("annexe>");
    }
    else if (name == b_section)
    {
        printf("section>");
    }
    else if (name == b_titre)
    {
        printf("titre>");
    }
    else if (name == b_liste)
    {
        printf("liste>");
    }
    else if (name == b_item)
    {
        printf("item>");
    }
    else if (name == b_important)
    {
        printf("important>");
    }
    else if (name == b_br)
    {
        printf("br/>");
    }
    else if (name == t_texte)
    {
        printf("texte>");
    }
}

void printTabs(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("\t");
    }
}

void printTagAux(tag *element, int decalage)
{
    if (element == NULL)
        return;

    printTabs(decalage);

    if (element->tagName == t_mot_simple) {
        printf("%s", element->content);
        printf("\n");
    } else {
        printf("<");
        printTagName(element->tagName);
        printf("\n");

        if (element->children == EMPTY_LIST) {
            printf("No children\n");
        }
        item* child = element->children;
        while (child != NULL)
        {
            printTagAux(child->element, decalage + 1);
            child = child->next;
        }
        
        printf("</");
        printTagName(element->tagName);
        printf("\n");        
    }
}

/**
 * TODO : comment
 * result example : <document>
 *                            <section>
 *                                      Bonjour le monde
 *                            </section>
 *                  </document>
 */
void printTag(tag* element) {
    printTagAux(element, 0);
}