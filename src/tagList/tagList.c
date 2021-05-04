#include "tagList.h"

/**
 * \brief Create an empty list
 */
tagList createList(tag* element) {
    tagList liste = malloc(sizeof(item));
    liste->element = element;
    liste->next = END_TAG_LIST;

    return liste;
}

/**
 * \brief Add a tag to a list
 * \param tagList the list to update
 * \param element the tag to add
 */
void appendToList(tagList list, tag* element) {
    if (list == EMPTY_LIST) {
        list = createList(element);
    } else if (list->next == END_TAG_LIST) {
        list->next = createList(element);
    } else {
        appendToList(list->next, element);
    }
}