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
t_tag *createTag(t_tagName name);

t_tag *createTagWithChildren(t_tagName name, tagList children);

/**
 * \brief This function creates a tag and allocate the memory.
 * \param name The name of the tag (see t_tagName)
 * \param content The content of the tag
 */
t_tag *createTagMotSimple(t_tagName name, char* content);

/**
 * TODO : comment
 */
void addChild(t_tag* father, t_tag* child);

/**
 * TODO : comment
 * result example : <document>
 *                            <section>
 *                                      Bonjour le monde
 *                            </section>
 *                  </document>
 */
void printTag(t_tag* element);

#endif