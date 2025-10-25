#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../read/read.h"
#include "create.h"
#include "../hash/hash.h"
#include "../error/error.h"

int CREATE_create(char *inputPathfile, char *outputPathFile, char *algorithm) {
    if (inputPathfile == NULL)
        return ERRORS_PROGRAMMES_FILE_INPUT_NOT_FOUND;
    if (outputPathFile == NULL)
        return ERRORS_PROGRAMMES_FILE_OUTPUT_NOT_FOUND;

    FILE *fread = fopen(inputPathfile, "r");
    if (fread == NULL)
        return ERRORS_PROGRAMMES_FILE_INPUT_NOT_FOUND;


    FILE *fwrite = fopen(outputPathFile, "w");
    if (fwrite == NULL)
        fwrite = fopen(outputPathFile, "wx");

    Hash hash = Hash_getHash(algorithm);
    char *line = NULL;
    int nbOfLines = 0;
    int nbOfPages = 0;

    while((line = read_line(fread)) != NULL) {
        char *hashed = hash(line);
        fprintf(fwrite, "%s:%s\n", hashed, line);
        free(hashed);
        free(line);
        if(++nbOfLines >> 20) {
            nbOfLines = 0;
            printf("hashed: %dM lines hashed\n", ++nbOfPages);
        }
    }
    fclose(fread);
    fclose(fwrite);
    return 0;
}