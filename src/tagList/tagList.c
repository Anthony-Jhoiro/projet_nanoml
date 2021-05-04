#include "tagList.h"

/**
 * \brief Create an empty list
 */
tagList createList(tag* element) {
    tagList liste = malloc(sizeof(item));
    liste->element = element;
    liste->next = END_TAG_LIST;

    printf("%p", liste);

    return liste;
}

/**
 * \brief Add a tag to a list
 * \param tagList the list to update
 * \param element the tag to add
 */
tagList appendToList(tagList list, tag* element) {
    if (list == EMPTY_LIST) {
        return createList(element);
    } else if (list->next == END_TAG_LIST) {
        list->next = createList(element);
        return list;
    } else {
        appendToList(list->next, element);
        return list;
    }
}