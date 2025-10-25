#include "read.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char *read_line(FILE *file) {
    int length = 0;
    const int maxReader = 1024;
    char *buffer = malloc(maxReader);

    bool continueLoop = true;

    while (continueLoop) {
        if (fgets(buffer + length, maxReader, file) == NULL)
            continueLoop = false;

        if (continueLoop) {
            length = strlen(buffer);
            if (buffer[length - 1] == '\n') {
                length = buffer[length - 2] == '\r' ? length -2 : length - 1;
                buffer[length] = '\0';
                continueLoop = false;
            } else {
                void* tmp = realloc(buffer, length + maxReader);
                if (tmp != NULL)
                    buffer = tmp;
            }
        }
    }
    if (length == 0) {
        free(buffer);
        return NULL;
    }

    return buffer;
}
