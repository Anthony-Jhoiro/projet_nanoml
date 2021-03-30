#ifndef TAG_H
#define TAG_H

#include "../global.h"
#include "../listTools/listTools.h"
/**
 * \brief This function creates a tag and allocate the memory.
 * \param name The name of the tag (see tagsNames)
 * \param content The content of the tag
 */
tag createTag(tagsNames name, char* content);

/**
 * TODO : comment
 */
void addChild(tag father, tag child);

/**
 * TODO : comment
 * result example : <document>
 *                            <section>
 *                                      Bonjour le monde
 *                            </section>
 *                  </document>
 */
void printTag(tag element);

#endif