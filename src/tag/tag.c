#include "tag.h"

/**
 * \brief This function creates a tag and allocate the memory.
 * \param name The name of the tag (see tagsNames)
 * \param content The content of the tag
 * TODO : finish
 */
tag* createTag(tagsNames name, char* content) {
    tag* t = malloc(sizeof (tag));

    t->name = name;
    t->children = createList();
}