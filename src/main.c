#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "create/create.h"
#include "search/search.h"

int MAIN_mode(char* arg, char** mode, char* option) {
    if (!strcmp(option, arg)) {
        if (*mode != NULL) {
            printf("On ne peut pas avoir deux mode en même temps\n");
            return -1;
        }
        *mode = arg;
    }
    return 0;
}

/**
 * 
 * Example: 
 * - make run -G -Algo Sha256 filePath outputFilePath  
 * - make run -G filePath
 * - make run -G filePath outputFilePath  
 * - make run -G filePath -Algo Sha256 outputFilePath  
 * - make run -G filePath outputFilePath -Algo Sha256
 * 
 */
int main(int argc, char* argv[]) {
    char* algo = NULL;
    char* mode = NULL;
    char* inputFile = NULL;
    char* outputFileOrToSearch = NULL;

    printf("size: %d %s", argc, argv[1]);

    for (int index = 1; index < argc; index++) {
        char* arg = argv[index];

        printf("here ! %s", arg);
        if (arg[0]=='-') {
            int modeG = MAIN_mode(arg, &mode, "-G");
            if (modeG != 0) return modeG;
            int modeL = MAIN_mode(arg, &mode, "-L");
            if (modeL != 0) return modeL;

            if (!strcmp("-Algo", arg)) {
                // Si on dit qu'on veut préciser un algo alors on doit le fournir en en argument après
                if (++index >= argc) {
                    printf("Vous devez préciser l'algo !\n");
                    return -2;
                }
                algo = argv[index];
            }
        } else if (inputFile == NULL) {
            inputFile = arg;
        } else if (outputFileOrToSearch == NULL) {
            outputFileOrToSearch = arg;
        } else {
            printf("Argument en trop !\n");
            return -3;
        }
    }
    if (!strcmp(mode, "-G")) {
        CREATE_create(inputFile, outputFileOrToSearch, algo);
    } else if (!strcmp(mode, "-L")) {
        SEARCH_search(inputFile, outputFileOrToSearch, algo);
    } else {
        printf("Veuillez préciser le mode !\n");
        return -4;
    }
    return 0;
}