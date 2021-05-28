#include "writer.h"

/**
 * \brief Ecrit un mot simple. Un mot simple est une succession de caractère. 
 * Si le document demande d'écrire en majuscule, le texte sera écrit en majuscule 
 */
void writeMotSimple(a_document doc, a_tag t)
{
    char *word = t->content;

    if (doc->uppercase) {
        writeInDocUppercase(doc, "%s", word);
        return;
    }

    writeInDoc(doc, "%s", word);
}

/**
 * \brief Ecrit un mot important un mot important contient un ou plusieurs mot simple, le tout entourré de `"`. 
 * Nous avons __ABSOLUMENT__ tenu à ce que les `"` ne soient pas détachés des mots adjacents sans saut de ligne entre.
 */
void writeMotImportant(a_document doc, a_tag t)
{
    t_item *child = t->children;

    if (child == EMPTY_LIST){
        writeInDoc(doc, "\"\"");
        return;
    }

    if (child->next == EMPTY_LIST){
        if(doc->uppercase){
            writeInDocUppercase(doc, "\"%s\"", child->element->content);
            return;
        }
        writeInDoc(doc, "\"%s\"", child->element->content);
        return;
    }

    if(doc->uppercase){
        writeInDocUppercase(doc, "\"%s", child->element->content);
        child = child->next;
        while (child->next != EMPTY_LIST){
            writeInDocUppercase(doc, "%s", child->element->content);
            child = child->next;
        }

        writeInDocUppercase(doc, "%s\"", child->element->content);
        return;
    }

    writeInDoc(doc, "\"%s", child->element->content);
    child = child->next;
    while (child->next != EMPTY_LIST){
        writeInDoc(doc, "%s", child->element->content);
        child = child->next;
    }
    writeInDoc(doc, "%s\"", child->element->content);
    
}

/**
 * \brief Ecrit un mot enrichi. Un mot enrichi est soit un mot simple ou un mot important ou un saut de ligne.
 */
void writeMotEnrichi(a_document doc, a_tag t)
{
    a_tag child = t->children->element;

    t_tagName tagName = child->tagName;

    switch (tagName)
    {
    case e_mot_simple:
        writeMotSimple(doc, child);
        break;

    case e_mot_important:
        writeMotImportant(doc, child);
        break;

    case e_retour_ligne:
        fillRowNoPrefix(doc);
        break;

    default:
        break;
    }
}

/**
 * \brief Ecrit un texte.texte contient zero ou plusieurs mot enrichi
 */
void writeTexte(a_document doc, a_tag t)
{
    t_item *child = t->children;

    while (child != EMPTY_LIST)
    {
        writeMotEnrichi(doc, child->element);
        child = child->next;
    }
}

/**
 * \brief Ecrit un titre. Un titre contient un prefix avec l'index du titre suivi d'un texte écrit en majuscule
 */
void writeTitre(a_document doc, a_tag t)
{
    t_item *child = t->children;
    printPrefix(doc);
    int maxContent = getMaxContentLength(doc);

    char buff[maxContent];

    int size = toRomanNumber(doc->titleIndex, buff, maxContent);

    writeInDoc(doc, "%s", buff);

    doc->titleIndex++;


    if (child != EMPTY_LIST)
    {
        doc->uppercase = 1;
        writeTexte(doc, child->element);
        doc->uppercase = 0;
    }

    fillRowNoPrefix(doc);
}


/**
 * \brief Ecrit une liste texte. une liste texte contient une liste suivie d'éventuellement un texte.
 */
void writeListeTexte(a_document doc, a_tag t)
{
    t_item *childTexte = t->children;

    writeListe(doc, childTexte->element);

    if (childTexte->next != EMPTY_LIST)
    {
        writeTexteListe(doc, childTexte->next->element);
    }
}

/**
 * \brief Ecrit une texte liste. une texte liste contient un texte suivi d'éventuellement une liste.
 */
void writeTexteListe(a_document doc, a_tag t)
{
    t_item *childTexte = t->children;

    writeTexte(doc, childTexte->element);
    fillRowNoPrefix(doc);

    if (childTexte->next != EMPTY_LIST)
    {
        writeListeTexte(doc, childTexte->next->element);
    }
}

/**
 * \brief Ecrit un item. un item est une suite de texte et de listes. Le préfixe 
 * est modifié pendant l'éxecution avec l'ajout de 2 espaces
 */
void writeItem(a_document doc, a_tag t)
{
    a_tag child = t->children->element;
    a_state previousState = saveState(doc);

    // TODO : check length
    printPrefix(doc);

    fprintf(doc->flux, "  #  ");
    doc->contentLength += 3;
    appendPrefix(doc, "  ");

    if (child->tagName == e_texte_liste)
    {
        writeTexteListe(doc, child);
    }
    else
    {
        writeListeTexte(doc, child);
    }
    loadState(previousState, doc);
}

/**
 * \brief Ecrit une liste. Contient zero ou plusieurs item
 */
void writeListe(a_document doc, a_tag t)
{
    t_item *child = t->children;

    while (child != EMPTY_LIST)
    {
        if (child->element->tagName == e_item)
        {
            writeItem(doc, child->element);
        }
        child = child->next;
    }
}

/**
 * \brief Ecrit un contenu. Contient zero ou plusieurs mot enrichi | section | titre | liste
 */
void writeContenu(a_document doc, a_tag t)
{
    t_item *child = t->children;
    while (child != EMPTY_LIST)
    {
        t_tagName name = child->element->tagName;
        if (name == e_mot_enrichi)
        {
            if (doc->contentLength == 0)
            {
                printPrefix(doc);
            }
            writeMotEnrichi(doc, child->element);
        }
        else
        {
            if (doc->contentLength != 0)
            {
                fillRowNoPrefix(doc);
            }

            if (name == e_section)
            {
                writeSection(doc, child->element);
            }
            else if (name == e_titre)
            {
                writeTitre(doc, child->element);
            }
            else if (name == e_liste)
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

/**
 * \brief Ecrit une boite, une boite est contituée d'une ligne de --- entourée de +, 
 * on ajoute également des `|` comme préfixe et suffixe. Contient un contenu
 */
void writeBox(a_document doc, a_tag t)
{
    a_state previousState = saveState(doc);

    printRow(doc);
    appendPrefix(doc, "|");
    appendSuffix(doc, "|");

    a_tag childContenu = t->children->element;

    writeContenu(doc, childContenu);

    loadState(previousState, doc);
    printRow(doc);
}

/**
 * \brief Ecrit une section Unique. Voir `writeBox`
 */
void writeSection(a_document doc, a_tag t)
{
    writeBox(doc, t);
}

/**
 * \brief Ecrit un document Unique. Voir `writeBox`
 */
void writeDocument(a_document doc, a_tag t)
{
    writeBox(doc, t);
}

/**
 * \brief Ecrit une annexeUnique Unique. Voir `writeBox`
 */
void writeAnnexe(a_document doc, a_tag t)
{
    writeBox(doc, t);
}

/**
 * \brief Ecrit un annexes. Contient zero ou plusieurs annexeUniques
 */
void writeAnnexes(a_document doc, a_tag t)
{

    for (t_item *annexeItem = t->children; annexeItem != EMPTY_LIST; annexeItem = annexeItem->next)
    {

        a_tag annexe = annexeItem->element;
        writeAnnexe(doc, annexe);
    }
}

/**
 * \brief Ecrit un texte enrichi, un texte enrichi contient un document suivi d'annexes
 */
void writeTexteEnrichi(a_document doc, a_tag t)
{
    a_tag childDocument = t->children->element;

    writeDocument(doc, childDocument);

    t_item *annexes = t->children->next;

    if (annexes != EMPTY_LIST)
    {
        writeAnnexes(doc, t->children->next->element);
    }
}