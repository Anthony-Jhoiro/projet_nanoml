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
typedef enum e_tags {
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
    t_mot_simple

} tagsNames;

/**
 * TODO : comment
 */
typedef struct s_tag {
    tagsNames name;
    struct s_tag* children;
    int nbChildren;
    char* content;
} tag ;

typedef tag* root;

/**
 * TODO : comment
 */
typedef struct s_item {
    tag* element;
    struct s_item* next;
} item;

#endif
