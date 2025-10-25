#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "create/create.h"
#include "search/search.h"
#include "error/error.h"
#include "hashmap/hashmap.h"

int MAIN_mode(char* arg, char** mode, char* option) {
    if (!strcmp(option, arg)) {
        if (*mode != NULL) {
            return ERRORS_PROGRAMMES_ONLY_ONE_MODE;
        }
        *mode = arg;
    }
    return 0;
}

int launch(const int argc, char* argv[]) {
    char* algo = NULL;
    char* mode = NULL;
    char* inputFile = NULL;
    char* outputFileOrToSearch = NULL;

    for (int index = 1; index < argc; index++) {
        char* arg = argv[index];

        if (arg[0]=='-') {
            int modeG = MAIN_mode(arg, &mode, "-G");
            if (modeG != 0) return modeG;
            int modeL = MAIN_mode(arg, &mode, "-L");
            if (modeL != 0) return modeL;

            if (!strcmp("-Algo", arg)) {
                // Si on dit qu'on veut préciser un algo alors on doit le fournir en en argument après
                if (++index >= argc)
                    return ERRORS_PROGRAMMES_PRECISE_ALGORITHM;
                algo = argv[index];
            }
        } else if (inputFile == NULL) {
            inputFile = arg;
        } else if (outputFileOrToSearch == NULL) {
            outputFileOrToSearch = arg;
        } else
            return ERRORS_PROGRAMMES_TOO_MUCH_ARGS;
    }
    if (mode == NULL)
        return ERRORS_PROGRAMMES_NEED_MODE;
    else if (!strcmp(mode, "-G"))
        return CREATE_create(inputFile, outputFileOrToSearch, algo);
    else if (!strcmp(mode, "-L"))
      return SEARCH_search(inputFile, outputFileOrToSearch, algo);

    return ERRORS_PROGRAMMES_NEED_MODE;
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
int main(const int argc, char* argv[]) {
    int result = launch(argc, argv);
    Errors_printf(result);
    return result;

    return 0;
}