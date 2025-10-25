#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "search.h"
#include "../hash/hash.h"
#include "../error/error.h"

/**


    HashMap *map = HashMap_Create();
<<<<<<< HEAD
=======
    char **line = NULL;

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

int SEARCH_search(char *inputPathfile) {
    if (inputPathfile == NULL)
        return ERRORS_PROGRAMMES_FILE_INPUT_NOT_FOUND;

    FILE *fread = fopen(inputPathfile, "r");
    if (fread == NULL)
        return ERRORS_PROGRAMMES_FILE_INPUT_NOT_FOUND;

    HashMap *map = SEARCH_generateMap(fread);

    fclose(fread);
>>>>>>> 1d278b8 (FINISHED !)

    char *line = NULL;
    bool isAlive = true;

<<<<<<< HEAD
    char *str = HashMap_Get(map, "a");
    if (str != NULL)
        printf("a = %s\n", str);
    else
        printf("a introuvable\n");

    str = HashMap_Get(map, "mehdi");
    if (str != NULL)
        printf("mehdi = %s\n", str);
    else
        printf("mehdi introuvable\n");

    HashMap_Free(map);
*/

int SEARCH_search(char *inputPathfile, char *toSearch, char *algorithm) {
    Hash hash = Hash_getHash(algorithm);
    printf("%s\n", hash("Hellworld"));
=======
    do {
        line = scanfline();
        isAlive = line != NULL && strcmp(line, "exit");
        if (isAlive) {
            char *value = HashMap_Get(map, line);
            printf("%s\n", value);
            free(line);
        }
    } while (isAlive);

    free(line);
    printf("Free map activé\n");
    HashMap_Free(map);

>>>>>>> 1d278b8 (FINISHED !)
    return 0;
}