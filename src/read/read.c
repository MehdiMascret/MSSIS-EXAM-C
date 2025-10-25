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
<<<<<<< HEAD
=======
char **read_line_split_into_two_when_first_appear_separator(FILE *file, char separator) {
    const int maxReader = 1024;
    int length = 1024;
    char *buffer = malloc(maxReader);

    char **line = malloc(2 * sizeof(char *));
    int positionInLine = 0;
    line[0] = buffer;
    line[1] = NULL;


    char carractere;
    unsigned long index = 0;

    // Tant que je n'ai pas atteind la fin de la ligne ou je n'ai pas atteind la fin du fichier :
    do {
        carractere = fgetc(file);
        // Si j'ai dépasser la taille de l'allocation alors je realloue la mémoire
        if (index >= length) {
            length += maxReader;
            void* tmp = realloc(buffer, length);
            // Si on me donne un nouvelle position dans la mémoire alors je dois modifié buffer et informé two
            if (tmp != NULL) {
                buffer = tmp;
                line[positionInLine] = buffer;
            }
        }
        if (carractere == separator && positionInLine == 0) {
            length = maxReader;
            buffer[index] = '\0';
            index = 0;
            buffer = malloc(maxReader);
            positionInLine = 1;
            line[positionInLine] = buffer;
        } else if (carractere != EOF && carractere != '\n')
            buffer[index++] = carractere;
    } while (carractere != EOF && carractere != '\n');

    // ERREUR : Je n'ai jamais trouvé le splitterator !
    if (positionInLine != 1) {
        free(buffer);
        free(line);
        return NULL;
    }
    // Au cas ou la deuxieme position n'aurait plus de place pour un \0
    if (index >= length) {
        void* tmp = realloc(buffer, index+1);
        // Si on me donne un nouvelle position dans la mémoire alors je dois modifié buffer et informé two
        if (tmp != NULL) {
            buffer = tmp;
            line[positionInLine] = buffer;
        }
    }
    buffer[index] = '\0';

    return line;
}
char *scanfline () {
    int length = 0;
    const int maxReader = 1024;
    char *buffer = malloc(maxReader);

    bool continueLoop = true;

    while (continueLoop) {
        if (fgets(buffer + length, maxReader, stdin) == NULL)
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
    length = strlen(buffer);
    if (length == 0) {
        free(buffer);
        return NULL;
    }
    return buffer;
}
>>>>>>> 1d278b8 (FINISHED !)
