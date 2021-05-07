#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdlib.h>
#include <stdio.h>

// --- constants --- //

/**
 * TODO : comment
 */
#define EMPTY_LIST NULL

/**
 * TODO : comment
 */
#define BUFFER_SIZE 255

// --- structures --- //

/**
 * TODO : comment
 */
typedef enum e_tags
{ // TODO : do something
    t_texte_enrichi,
    t_document,
    t_annexes,
    t_contenu,
    t_section,
    t_titre,
    t_liste,
    t_item,
    t_liste_texte,
    t_texte_liste,
    t_texte,
    t_contenu_texte,
    t_mot_enrichi,
    t_mot_important,
    t_mot_simple,
    t_retour_ligne,

} tagsNames;

/**
 * TODO : comment
 */
typedef struct s_item
{
    struct s_tag *element;
    struct s_item *next;
} item;

typedef item *tag_list;

/**
 * TODO : comment
 */
typedef struct s_tag
{
    tagsNames tagName;
    tag_list children;
    char *content;
} tag;

typedef tag *root;

#endif
