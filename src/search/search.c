#include <stdio.h>
#include <stdlib.h>
#include "search.h"
#include "../hash/hash.h"
#include "../error/error.h"

int SEARCH_search(char *inputPathfile, char *toSearch, char *algorithm) {
    Hash* hash = Hash_getHash(algorithm);
    printf("%s\n", hash("Hellworld"));
    return 0;
}