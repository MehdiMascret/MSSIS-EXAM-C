#include "error.h"
#include <stdio.h>

void Errors_printf(enum ERRORS_PROGRAMMES error) {
    switch (error) {
        case ERRORS_PROGRAMMES_ONLY_ONE_MODE:
            printf("ERROR STARTING SERVICE: On ne peut pas utiliser deux mode en même temps\n");
            break;
        case ERRORS_PROGRAMMES_PRECISE_ALGORITHM:
            printf("ERROR STARTING SERVICE: Si vous voulez préciser un algo, merci de le renseigné !\n");
            break;
        case ERRORS_PROGRAMMES_TOO_MUCH_ARGS:
            printf("ERROR STARTING SERVICE: Argument en trop !\n");
            break;
        case ERRORS_PROGRAMMES_NEED_MODE:
            printf("ERROR STARTING SERVICE: ERROR STARTING SERVICE: Veuillez préciser un mode correcte (-L ou -G)\n");
            break;
        case ERRORS_PROGRAMMES_FILE_INPUT_NOT_FOUND:
            printf("ERROR STARTING SERVICE: Le fichier input doit exister\n");
            break;
        case ERRORS_PROGRAMMES_FILE_OUTPUT_NOT_FOUND:
            printf("ERROR STARTING SERVICE: Le fichier output doit etre renseigné\n");
            break;
    }
}