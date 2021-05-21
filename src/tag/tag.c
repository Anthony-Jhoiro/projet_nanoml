#include "tag.h"

/**
 * \brief This function creates a tag and allocate the memory.
 * \param name The name of the tag (see t_tagName)
 */
t_tag *createTag(t_tagName name)
{
    return createTagMotSimple(name, NULL);
}

/**
 * TODO : comment
 */
t_tag *createTagWithChildren(t_tagName name, tagList children)
{
    t_tag* t = createTag(name);
    t->children = children;
    return t;
}

/**
 * \brief This function creates a tag and allocate the memory.
 * \param name The name of the tag (see t_tagName)
 * \param content The content of the tag
 */
t_tag *createTagMotSimple(t_tagName name, char *content)
{
    t_tag *t = malloc(sizeof(t_tag));

    t->tagName = name;
    t->content = content;
    t->children = EMPTY_LIST;

    return t;
}

void addChild(t_tag *father, t_tag *child)
{
    father->children = appendToList(father->children, child);
}

void printTagName(t_tagName name)
{
    if (name == e_document)
    {
        printf("document");
    }
    else if (name == e_section)
    {
        printf("section");
    }
    else if (name == e_titre)
    {
        printf("titre");
    }
    else if (name == e_liste)
    {
        printf("liste");
    }
    else if (name == e_item)
    {
        printf("item");
    }
    else if (name == e_mot_important)
    {
        printf("important");
    }
    else if (name == e_retour_ligne)
    {
        printf("br/");
    }
    else if (name == e_texte)
    {
        printf("texte");
    }
    else if (name == e_mot_enrichi)
    {
        printf("enrichi");
    }
    else if (name == e_texte_liste)
    {
        printf("texte_liste");
    }
    else if (name == e_liste_texte)
    {
        printf("liste_texte");
    }
    else if (name == e_document)
    {
        printf("document");
    }
    else if (name == e_annexes)
    {
        printf("annexes");
    }
    else if (name == e_annexe)
    {
        printf("annexe");
    }
}

void printTabs(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("\t");
    }
}

void printTagAux(t_tag *element, int decalage)
{
    if (element == NULL)
        return;

    printTabs(decalage);

    if (element->tagName == e_mot_simple)
    {
        printf("%s", element->content);
        printf("\n");
    }
    else if (element->tagName == e_retour_ligne)
    {
        printf("\e[0;33m<br/>\e[0;37m\n");
    }
    else
    {
        printf("<\e[1;35m");
        printTagName(element->tagName);
        printf("\e[0;37m>");
        printf("\n");

        if (element->children == EMPTY_LIST)
        {
            printf("No children\n");
        }
        t_item *child = element->children;
        while (child != NULL)
        {
            printTagAux(child->element, decalage + 1);
            child = child->next;
        }
        printTabs(decalage);

        printf("</\e[1;35m");
        printTagName(element->tagName);
        printf("\e[0;37m>");
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
void printTag(t_tag *element)
{
    printTagAux(element, 0);
}