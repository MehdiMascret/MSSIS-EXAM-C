#include "malloc_string.h"
#include <stdlib.h>
#include <string.h>

/**
* Permet d'allouer de la mémoire pour une chaine de carractère
* @param str <char*> Chaine de carractère disponible uniquement dans la pile
* @return <char*> Chaine de carractère disponible dans le tas
*/
char *MALLOC_STRING(const char *str) {
    unsigned long n = strlen(str) + 1;
    char *p = (char*)malloc(n);
    if (p) memcpy(p, str, n);
    return p;
}