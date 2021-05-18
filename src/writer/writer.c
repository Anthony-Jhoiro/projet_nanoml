#include "writer.h"

void writeMotSimple(a_document doc, tag *t, int upperCase)
{
    char *word = t->content;

    int maxLength = getMaxContentLength(doc);

    int wordLength = strLength(word);

    if (wordLength > maxLength)
    {
        fillRow(doc);
        int maxLength = getMaxContentLength(doc);
        if (wordLength > maxLength)
        {
            fprintf(stderr, "Error: Can not write word [%s]", word);
            exit(11);
        }
    }
    if (upperCase)
    {
        printUpperCase(doc, word);
    }
    else
    {
        fprintf(doc->flux, "%s", word);
    }
    doc->contentLength += wordLength;
    if (wordLength != maxLength)
    {
        fprintf(doc->flux, " ");
        doc->contentLength++;
    }
}

void writeMotImportant(a_document doc, tag *t, int upperCase)
{
    char *word = t->children->element->content;

    int maxLength = getMaxContentLength(doc);

    int wordLength = strLength(word) + 2;

    if (wordLength > maxLength)
    {
        fillRow(doc);
        int maxLength = getMaxContentLength(doc);
        if (wordLength > maxLength)
        {
            fprintf(stderr, "Error: Can not write word [\"%s\"]", word);
            exit(11);
        }
    }
    fprintf(doc->flux, "\"");
    if (upperCase)
    {
        printUpperCase(doc, word);
    }
    else
    {
        fprintf(doc->flux, "%s", word);
    }
    fprintf(doc->flux, "\"");

    doc->contentLength += wordLength;
    if (wordLength != maxLength)
    {
        fprintf(doc->flux, " ");
        doc->contentLength++;
    }
}

void writeMotEnrichi(a_document doc, tag *t, int upperCase)
{
    tag *child = t->children->element;

    tagsNames tagName = child->tagName;

    switch (tagName)
    {
    case t_mot_simple:
        writeMotSimple(doc, child, upperCase);
        break;

    case t_mot_important:
        writeMotImportant(doc, child, upperCase);
        break;

    case t_retour_ligne:
        fillRowNoPrefix(doc);
        break;

    default:
        break;
    }
}

void writeTexte(a_document doc, tag *t, int upperCase)
{
    item *child = t->children;

    while (child != EMPTY_LIST)
    {
        writeMotEnrichi(doc, child->element, upperCase);
        child = child->next;
    }
}

void writeTitre(a_document doc, tag *t)
{
    item *child = t->children;
    printPrefix(doc);

    if (child != EMPTY_LIST)
    {
        writeTexte(doc, child->element, 1);
    }

    fillRowNoPrefix(doc);
}

void writeListeTexte(a_document doc, tag *t)
{
    item *childTexte = t->children;

    writeListe(doc, childTexte->element);

    if (childTexte->next != EMPTY_LIST)
    {
        writeTexteListe(doc, childTexte->next->element);
    }
}

void writeTexteListe(a_document doc, tag *t)
{
    item *childTexte = t->children;

    writeTexte(doc, childTexte->element, 0);
    fillRowNoPrefix(doc);

    if (childTexte->next != EMPTY_LIST)
    {
        writeListeTexte(doc, childTexte->next->element);
    }
}

void writeItem(a_document doc, tag *t)
{
    tag *child = t->children->element;
    a_state previousState = saveState(doc);

    // TODO : check length
    printPrefix(doc);

    fprintf(doc->flux, "  #  ");
    doc->contentLength += 3;
    appendPrefix(doc, "  ");

    if (child->tagName == t_texte_liste)
    {
        writeTexteListe(doc, child);
    }
    else
    {
        writeListeTexte(doc, child);
    }
    loadState(previousState, doc);
}

void writeListe(a_document doc, tag *t)
{
    item *child = t->children;

    while (child != EMPTY_LIST)
    {
        if (child->element->tagName == t_item)
        {
            writeItem(doc, child->element);
        }
        child = child->next;
    }
}

void writeContenu(a_document doc, tag *t)
{
    item *child = t->children;
    while (child != EMPTY_LIST)
    {
        tagsNames name = child->element->tagName;
        if (name == t_mot_enrichi)
        {
            if (doc->contentLength == 0)
            {
                printPrefix(doc);
            }
            writeMotEnrichi(doc, child->element, 0);
        }
        else
        {
            if (doc->contentLength != 0)
            {
                fillRowNoPrefix(doc);
            }

            if (name == t_section)
            {
                writeSection(doc, child->element);
            }
            else if (name == t_titre)
            {
                writeTitre(doc, child->element);
            }
            else if (name == t_liste)
            {
                writeListe(doc, child->element);
            }
        }

        child = child->next;
    }

    if (doc->contentLength != 0)
    {
        fillRowNoPrefix(doc);
    }
}

void writeBox(a_document doc, tag *t)
{
    a_state previousState = saveState(doc);

    printRow(doc);
    appendPrefix(doc, "|");
    appendSuffix(doc, "|");

    tag *childContenu = t->children->element;

    writeContenu(doc, childContenu);

    loadState(previousState, doc);
    printRow(doc);
}

void writeSection(a_document doc, tag *t)
{
    writeBox(doc, t);
}

void writeDocument(a_document doc, tag *t)
{
    writeBox(doc, t);
}

void writeAnnexe(a_document doc, tag *t)
{
    writeBox(doc, t);
}

void writeAnnexes(a_document doc, tag *t)
{

    for (item *annexeItem = t->children; annexeItem != EMPTY_LIST; annexeItem = annexeItem->next)
    {

        tag *annexe = annexeItem->element;
        writeAnnexe(doc, annexe);
    }
}

void writeTexteEnrichi(a_document doc, tag *t)
{
    tag *childDocument = t->children->element;

    writeDocument(doc, childDocument);

    item *annexes = t->children->next;

    if (annexes != EMPTY_LIST)
    {
        writeAnnexes(doc, t->children->next->element);
    }
}