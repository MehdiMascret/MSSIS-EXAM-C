#include <stdio.h>
#include <string.h>
#include "G/main.h"
#include "L/main.h"

void help (int argc, char **argv) {
    printf("Options attendu :\n");
    printf("  -G\n");
    printf("  -L\n");
}

int main(int argc, char **argv) {
    // Retourner le code d'erreur 1 si 
    if (argc < 2) {
        help();
        return 1;
    }

    char *option = argv[1];
    if (!strcmp(option, "-G"))
        mainG(argv);
    else if (!strcmp(option, "-L"))
        mainL(argv);
    else {
        help();
        return 1;
    }
    
    return 0;
}