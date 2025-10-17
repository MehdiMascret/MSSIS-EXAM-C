#include <stdio.h>
#include <stdlib.h>
#include "hash/hash.c"

void main(char *pathfile, char *algorithm) {
    if (pathfile == NULL)
        pathfile = "files/dictionnaire.txt";
    
    FILE *fp = fopen(pathfile, "r"); 

    Hash* hashAlgorithm = Hash_getHash(algorithm);

    char* text_clair;
    while (fscanf(fp, "%s", text_clair) != EOF) {
        printf("%s", hashAlgorithm(text_clair));
    }
}