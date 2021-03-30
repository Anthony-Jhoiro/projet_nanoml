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
void appendToList(tagList tagList, tag* element) {

}