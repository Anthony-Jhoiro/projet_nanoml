# Nanoml

- **Anthony Quéré**
- **Kilian Debraux**

## Le parseur

Le role du parseur est de construire une structure de tag à partir d'un fichier donné. Pour fonctionner, nous avons défini une structure parser :

```c
typedef struct s_parser
{
    int (*verify)(char*);
    a_tag  (*execute)(reader);
} t_parser;
```

Cette structure est constituée de deux fonction. La première (**verify**) prend un nom de balise en paramètre sous forme de `char*`et vérifie si il correspond au nom de la balise recherchée. Par exemple pour une liste, nous allons regarder si le nom de la balise est *"liste"* ou pour un mot simple que le nom de la balise soit une chaine vide. Dans plusieurs cas (ex: *annexes*) cette fonction retournera toujours 1. C'est au moment de parser l'élémentque l'on controllera la balise. La deuxième fonction (**execute**) prend en paramètre un *reader* et lit le fichier charactère par caractère en formant un tag. Dans chacun de nos fichiers commençant par "parser", la structure est la même, on a tout d'abord la fonction verify puis la fonction execute et enfin une fonction permettant de créer un objet t_parser à partir des deux fonctions précédentes.

## Le writer

Pour écrire la structure de tag de façon formatée, nous avons deux structures :

```c

typedef struct s_document
{
    char prefix[MIDDLE_LINE_SIZE];
    char suffix[MIDDLE_LINE_SIZE];
    FILE* flux;
    int prefixLength;
    int suffixLength;
    int contentLength;
    char uppercase;
    int titleIndex;

} document;

typedef struct s_state
{
    int prefixLength;
    int suffixLength;
} t_state;
```

La première structure représente le document de destination du fichier. Nous avons dans l'ordre :
- Le préfixe : Début de la ligne
- Le suffixe : Fin de la ligne, le suffixe est lu à l'envers pour simplifier le développement
- flux : flux dans lequel écrire (un fichier ou directement le stdout)
- prefixLength : nombre de caractères du prefixe à écrire
- suffixLength : nombre de caractères du suffixe à écrire
- contentLength : nombre de caractères écrits sur la ligne courante (sans compter la taille du préfixe)
- uppercase : 1 si il faut écrire le texte en majuscule, 0 sinon.
- titleIndex : index pour énumérer les titres

### Exemples :
**Un titre :**
La ligne `||II GRAMMAIRE||`

Est composée de la sorte : 
1. Préfixe : `||`
2. Contenu (écrit directement dans le flux) : `II GRAMMAIRE`
3. Suffixe : `||`

La seconde structure sert à garder en mémoire les informations uties du document, nous l'utilisons quand nous avons besoin de changer le prefix pendant un bloc. Ainsi, quand le bloc est terminé, nous pouvons repartir de notre état initial.


