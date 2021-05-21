#ifndef TAG_H
#define TAG_H

#include "../global.h"
#include "../tagList/tagList.h"

#define TAG_NULL NULL

/**
 * \brief This function creates a tag and allocate the memory.
 * \param name The name of the tag (see t_tagName)
 * \param content The content of the tag
 */
a_tag createTag(t_tagName name);

a_tag createTagWithChildren(t_tagName name, tagList children);

/**
 * \brief This function creates a tag and allocate the memory.
 * \param name The name of the tag (see t_tagName)
 * \param content The content of the tag
 */
a_tag createTagMotSimple(t_tagName name, char* content);

/**
 * TODO : comment
 */
void addChild(a_tag  father, a_tag  child);

/**
 * TODO : comment
 * result example : <document>
 *                            <section>
 *                                      Bonjour le monde
 *                            </section>
 *                  </document>
 */
void printTag(a_tag  element);

#endif