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
#define BUFFER_SIZE 64

// --- structures --- //

/**
 * TODO : comment
 */
typedef enum E_tags
{ 
    e_texte_enrichi,
    e_document,
    e_annexe,
    e_annexes,
    e_contenu,
    e_section,
    e_titre,
    e_liste,
    e_item,
    e_liste_texte,
    e_texte_liste,
    e_texte,
    e_contenu_texte,
    e_mot_enrichi,
    e_mot_important,
    e_mot_simple,
    e_retour_ligne,

} t_tagName;

/**
 * TODO : comment
 */
typedef struct s_item
{
    struct s_tag *element;
    struct s_item *next;
} t_item;

typedef t_item *t_tagList;
typedef t_item *a_item;

/**
 * TODO : comment
 */
typedef struct s_tag
{
    t_tagName tagName;
    t_tagList children;
    char *content;
} t_tag;

typedef t_tag* a_tag;
typedef a_tag root;

#endif
