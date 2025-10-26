#ifndef ERROR_H
#define ERROR_H

/**
 * Enumeration des erreurs possibles
 * - ERRORS_PROGRAMMES_ONLY_ONE_MODE: On ne peut avoir qu'un seul mode (pas de L et G en meme temps)
 * - ERRORS_PROGRAMMES_PRECISE_ALGORITHM: Dans les paramètre, le mot après -Algo doit être un algorithme est pas une chaine inexistance
 * - ERRORS_PROGRAMMES_TOO_MUCH_ARGS: Trop d'argument donnée au programme
 * - ERRORS_PROGRAMMES_NEED_MODE: Merci de préciser un mode (L ou G)
 * - ERRORS_PROGRAMMES_FILE_INPUT_NOT_FOUND: Le fichier input n'a pas été trouvé ou impossible de le lire
 * - ERRORS_PROGRAMMES_FILE_OUTPUT_NOT_FOUND: Le fichier output n'a pas été trouvé ou on ne peut pas écrire dedans
 * - ERRORS_PROGRAMMES_HASH_NOT_INITIALIZED: L'algorithme préciser en argument n'éxiste pas
*/
enum ERRORS_PROGRAMMES {
    ERRORS_PROGRAMMES_ONLY_ONE_MODE = -1,
    ERRORS_PROGRAMMES_PRECISE_ALGORITHM = -2,
    ERRORS_PROGRAMMES_TOO_MUCH_ARGS = -3,
    ERRORS_PROGRAMMES_NEED_MODE = -4,
    ERRORS_PROGRAMMES_FILE_INPUT_NOT_FOUND = -5,
    ERRORS_PROGRAMMES_FILE_OUTPUT_NOT_FOUND = -6,
    ERRORS_PROGRAMMES_HASH_NOT_INITIALIZED = -7
};

/**
* Transforme l'erreur en message comprehensible par l'utilisateur
* @param error <enum ERRORS_PROGRAMMES> message d'erreur
*/
void Errors_printf(enum ERRORS_PROGRAMMES);

#endif //ERROR_H