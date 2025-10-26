#include "read.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/**
 * Parcours toute la ligne puis la renvoie
 * @param file <File*> fichier à lire jusqu'à la fin de la ligne
 * @return Ligne entière lue
 */
char *read_line(FILE *file) {
    int length = 0;
    const int maxReader = 1024;
    char *buffer = malloc(maxReader);

    bool continueLoop = true;
    // Tant que je n'ai pas atteind un EOF ou un "\n" je continue de lire
    while (continueLoop) {
        // Si j'ai atteind un EOF j'arrete
        if (fgets(buffer + length, maxReader, file) == NULL)
            continueLoop = false;

        // Si je n'ai pas atteind un "\n" ou un EOF, je traite
        if (continueLoop) {
            // Si mon derniere element de ma liste de chaine de carractère est un '\n'
            // alors j'enleve le surplus (\n et \r) puis j'arrete la
            length = strlen(buffer);
            if (buffer[length - 1] == '\n') {
                length = buffer[length - 2] == '\r' ? length -2 : length - 1;
                buffer[length] = '\0';
                continueLoop = false;
            // Sinon j'ai peut etre dépasser ma taille alors au cas ou je tente de réalloué
            } else {
                void* tmp = realloc(buffer, length + maxReader);
                // S'il y a eu une réallocation alors je redéfinit ou est mon nouveau pointeur
                if (tmp != NULL)
                    buffer = tmp;
            }
        }
    }
    // Pas de nouvelle ligne à lire
    if (length == 0) {
        free(buffer);
        return NULL;
    }

    return buffer;
}

/**
 * Lit une ligne du fichier puis la sépare en deux par rapport à la première apparition du séparateur.
 * Le premier element du tableau retourné est avant la première apparition du séparateur.
 * Le deuxieme element du tableau retourné est après la première apparition du séparateur.
 * @param file <File*> Le fichier lûe
 * @param separator <char> le caractère de séparateur
 * @return Un tableau de taille 2, qui represente un split lors de la première apparition du séparateur
 */
char **read_line_split_into_two_when_first_appear_separator(FILE *file, char separator) {
    const int maxReader = 1024;
    int length = 1024;
    char *buffer = malloc(maxReader);

    char **line = malloc(2 * sizeof(char *));
    int positionInLine = 0;
    line[0] = buffer;
    line[1] = NULL;

    char carractere;
    unsigned long index = 0;

    // Je lis carractère par carractère
    // Tant que je n'ai pas atteind la fin de la ligne ou je n'ai pas atteind la fin du fichier :
    do {
        carractere = fgetc(file);
        // Si j'ai dépasser la taille de l'allocation alors je realloue la mémoire
        if (index >= length) {
            length += maxReader;
            void* tmp = realloc(buffer, length);
            // Si on me donne un nouvelle position dans la mémoire alors je dois modifié buffer et informé two
            if (tmp != NULL) {
                buffer = tmp;
                line[positionInLine] = buffer;
            }
        }
        // Si j'ai atteinds la premiere fois le séparateur
        // alors définit la taille max du premier tableau
        // puis je repar pour la lecture de la deuxieme position
        if (carractere == separator && positionInLine == 0) {
            length = maxReader;
            buffer[index] = '\0';
            index = 0;
            buffer = malloc(maxReader);
            positionInLine = 1;
            line[positionInLine] = buffer;
        // Sinon si ce n'est pas un EOF ou un \n alors je le rajoute au buffer
        } else if (carractere != EOF && carractere != '\n')
            buffer[index++] = carractere;
    } while (carractere != EOF && carractere != '\n');

    // ERREUR : Je n'ai jamais trouvé le splitterator !
    if (positionInLine != 1) {
        free(buffer);
        free(line);
        return NULL;
    }

    // Au cas ou la deuxieme position n'aurait plus de place pour un \0
    if (index >= length) {
        void* tmp = realloc(buffer, index+1);
        // Si on me donne un nouvelle position dans la mémoire alors je dois modifié buffer et informé two
        if (tmp != NULL) {
            buffer = tmp;
            line[positionInLine] = buffer;
        }
    }
    buffer[index] = '\0';

    return line;
}

/**
 * Lit l'élément envoye en console puis la renvoie
 * @return Ligne lue par la console
 */
char *scanfline () {
    int length = 0;
    const int maxReader = 1024;
    char *buffer = malloc(maxReader);

    bool continueLoop = true;

    // Je lis ligne par ligne de la console
    while (continueLoop) {
        // Si la console retourne un NULL alors j'arrete la
        if (fgets(buffer + length, maxReader, stdin) == NULL)
            continueLoop = false;

        // Si je continue de lire car pas de stop console alors je traite
        if (continueLoop) {
            // Si mon derniere element de ma liste de chaine de carractère est un '\n'
            // alors j'enleve le surplus (\n et \r) puis j'arrete la
            length = strlen(buffer);
            if (buffer[length - 1] == '\n') {
                length = buffer[length - 2] == '\r' ? length -2 : length - 1;
                buffer[length] = '\0';
                continueLoop = false;
            // Sinon j'ai peut etre dépasser ma taille alors au cas ou je tente de réalloué
            } else {
                void* tmp = realloc(buffer, length + maxReader);
                // S'il y a eu une réallocation alors je redéfinit ou est mon nouveau pointeur
                if (tmp != NULL)
                    buffer = tmp;
            }
        }
    }
    length = strlen(buffer);
    if (length == 0) {
        free(buffer);
        return NULL;
    }
    return buffer;
}
