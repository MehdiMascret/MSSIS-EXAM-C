#include "malloc_string.h"
#include <stdlib.h>
#include <string.h>

char *MALLOC_STRING(const char *str) {
    unsigned long n = strlen(str) + 1;
    char *p = (char*)malloc(n);
    if (p) memcpy(p, str, n);
    return p;
}