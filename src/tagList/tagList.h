#ifndef LIST_TOOLS_H
#define LIST_TOOLS_H

#include "../global.h"

#define END_TAG_LIST NULL

typedef t_item* tagList;

/**
 * \brief Create an empty list
 * \param element first element of the list
 */
tagList createList(a_tag  element);

/**
 * \brief Add a tag to a list
 * \param tagList the list to update
 * \param element the tag to add
 */
tagList appendToList(tagList tagList, a_tag  element);

/**
 * TODO : comment
 */
void freeList(tagList tagList);

/**
 * TODO : comment
 * Result example : <document>
 */
void printList(tagList list);

#endif