#ifndef MALLOC_STRING_H
#define MALLOC_STRING_H

/**
* Permet d'allouer de la mémoire pour une chaine de carractère
* @param str <char*> Chaine de carractère disponible uniquement dans la pile
* @return <char*> Chaine de carractère disponible dans le tas
*/

char *MALLOC_STRING(const char *str);

#endif