#include <stdio.h>
#include <stdlib.h>
#include "search.h"
#include "../hash/hash.h"
#include "../error/error.h"

/**


    HashMap *map = HashMap_Create();

    HashMap_Set(map, "a", "a l'aide pour l'aventure");
    HashMap_Set(map, "mehdi", "merde de mehdi !");
    HashMap_Set(map, "mehdi", "j'ai rien dit !");

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
    return 0;
}