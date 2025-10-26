#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "search.h"
#include "../error/error.h"
#include "../hashmap/hashmap.h"
#include "../read/read.h"

/**
* Permet de générer une HashMap a partir d'un fichier
* Tout les millions de lignes traité affiche un message permettant de savoir ou il en est
* @params fread <File*> Fichier à traiter
* @return <HashMap*> Une HashMap ayant pour clé les Hash des mots de passes et pour valeur les mots de passes
*/
HashMap* SEARCH_generateMap(FILE *fread) {
    int nbOfLines = 0;
    int nbOfPages = 0;
    char **line = NULL;

    HashMap *map = HashMap_Create();

    while((line = read_line_split_into_two_when_first_appear_separator(fread, ':')) != NULL) {
        HashMap_Set(map, line[0], line[1]);

        free(line[0]);
        free(line[1]);
        free(line);

        if(++nbOfLines >> 20) {
            nbOfLines = 0;
            printf("created: %dM lines lue\n", ++nbOfPages);
        }
    }

    printf("L'instanciation de la map est fini ! A VOUS DE JOUER !\n");

    return map;
}

/**
 * Utiliser pour l'option Load (-L)
 * Permet de chercher des mots de passes par rapport à leurs Hash.
 * Ce finit si on tape exit lors de l'utilisation de la console
 *
 * @param inputPathfile inputPathfile <char*> : Emplacement du fichier input, comportant les hash et les mots de passe
 * @return <int> : 0 = PAS D'ERREUR / AUTRE = ERREUR
 */
int SEARCH_search(char *inputPathfile) {
    // S'il n'y a aucun fichier input alors c'est une erreur
    if (inputPathfile == NULL)
        return ERRORS_PROGRAMMES_FILE_INPUT_NOT_FOUND;

    // S'il n'y a aucun fichier input ou inaxeccessible alors c'est une erreur
    FILE *fread = fopen(inputPathfile, "r");
    if (fread == NULL)
        return ERRORS_PROGRAMMES_FILE_INPUT_NOT_FOUND;

    // Genere une HashMap a partir du fichier inputPathFile
    HashMap *map = SEARCH_generateMap(fread);

    fclose(fread);

    char *line = NULL;
    bool isAlive = true;

    // Tant que l'on ne tape pas exit
    // On peut rentré un hash et cela nous retourne son mot de passe
    do {
        line = scanfline();
        isAlive = line != NULL && strcmp(line, "exit");
        if (isAlive) {
            char *value = HashMap_Get(map, line);
            if (value == NULL)
                printf("Pas de mot de passe trouvé pour la clé: %s\n", line);
            else printf("%s\n", value);
            free(line);
        }
    } while (isAlive);

    free(line);
    printf("Free map activé\n");
    HashMap_Free(map);

    return 0;
}