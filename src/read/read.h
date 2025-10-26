#ifndef READ_H
#define READ_H
#include <stdio.h>

/**
 * Parcours toute la ligne puis la renvoie
 * @param file <File*> fichier à lire jusqu'à la fin de la ligne
 * @return Ligne entière lue
 */
char *read_line(FILE *file);

/**
 * Lit l'élément envoye en console puis la renvoie
 * @return Ligne lue par la console
 */
char *scanfline ();

/**
 * Lit une ligne du fichier puis la sépare en deux par rapport à la première apparition du séparateur.
 * Le premier element du tableau retourné est avant la première apparition du séparateur.
 * Le deuxieme element du tableau retourné est après la première apparition du séparateur.
 * @param file <File*> Le fichier lûe
 * @param separator <char> le caractère de séparateur
 * @return Un tableau de taille 2, qui represente un split lors de la première apparition du séparateur
 */
char **read_line_split_into_two_when_first_appear_separator(FILE *file, char separator);

#endif //READ_H