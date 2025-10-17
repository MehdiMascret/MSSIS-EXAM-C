#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "create.h"
#include "../hash/hash.h"
#include "../error/error.h"

int CREATE_create(char *inputPathfile, char *outputPathFile, char *algorithm) {
    char *startWith = "../../";
    char* input = (char *) malloc(strlen(inputPathfile) + strlen(startWith) + 1);
    strcat(input, startWith);
    strcat(input, inputPathfile);
    FILE *fread = fopen(input, "r");
    if (fread == NULL) {
        return ERRORS_PROGRAMMES_FILE_INPUT_NOT_FOUND;
    }
    Hash* hash = Hash_getHash(algorithm);

    char line[100];
    while(fscanf(fread, "%s\n", line)!=EOF) {
        char *hashed = hash(line);
        printf("%s => %s\n", line, hashed);
        free(hashed);
    }
    fclose(fread);
    return 0;
}
