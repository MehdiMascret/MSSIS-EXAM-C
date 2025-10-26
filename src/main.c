#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "create/create.h"
#include "search/search.h"
#include "error/error.h"
#include "hashmap/hashmap.h"

/**
* Permet de définir le mode (Load ou Generate)
* Retourne une erreur si le mode a déja été définit.
* On ne peut pas avoir deux mode en même temps pour cette version de code !
*/
int MAIN_mode(char* arg, char** mode, char* option) {
    if (!strcmp(option, arg)) {
        if (*mode != NULL) {
            return ERRORS_PROGRAMMES_ONLY_ONE_MODE;
        }
        *mode = arg;
    }
    return 0;
}

/**
* Comme le design pattern Strategy : Prend des paramètre puis donne le rôle à quelqu'un d'autre de plus confirmé
*
* Pour ce faire il lit les chaines de carractère une à la suite des autres.
** BOUCLE :
** S'il tombe sur une chaine qui commance par "-" :
** - "-G" alors il définit que le mode à activer est Generate
** - "-L" alors il définit que le mode à activer est Load
** - "-Algo" alors la prochaine chaine sera le type d'algo
**
** Si la chaine ne commence pas par "-" alors c'est soit l'inputFile soit l'outputFile.
** Si l'inputFile n'a pas encore été définit alors il définit l'inputFile.
** Si l'outputFile n'a pas encore été définit alors il définit l'outputFile
** Sinon il y a trop d'argument et c'est une erreur.
*
* Une fois fini il donne en argument les elements nécessaire au mode qu'il convient.
* Si aucun mode n'a été définit alors il retourne une erreur.
*/
int mainStrategy(const int argc, char* argv[]) {
    char* algo = NULL;
    char* mode = NULL;
    char* inputFile = NULL;
    char* outputFileOrToSearch = NULL;
    int hasError = 0;

    /**
    * On commande à 1 car 0 est le fichier appellé
    * Boucle permet de définit les quatre variables plus haute :
    * - alog
    * - mode
    * - inputFIle
    * - outputFileOrToSearch
    */
    for (int index = 1; index < argc && hasError == 0; index++) {
        char* arg = argv[index];
        if (arg[0]=='-') {
            hasError = MAIN_mode(arg, &mode, "-G") | MAIN_mode(arg, &mode, "-L");
            if (!strcmp("-Algo", arg)) {
                // Si on dit qu'on veut préciser un algo alors on doit le fournir en en argument après
                if (++index >= argc)
                    hasError = ERRORS_PROGRAMMES_PRECISE_ALGORITHM;
                algo = argv[index];
            }
        } else if (inputFile == NULL) {
            inputFile = arg;
        } else if (outputFileOrToSearch == NULL) {
            outputFileOrToSearch = arg;
        } else
            return ERRORS_PROGRAMMES_TOO_MUCH_ARGS;
    }
    /**
    * - S'il y a une erreur alors on retourne cette erreur
    */
    if (hasError)
        return hasError;

    /**
    *  On donne au mode spécifié ou on retourne une erreur celon si :
    * - aucun mode n'a été donnée
    * - cas ou trop de mode à été gérer dans la boucle for directement
    */
    if (mode == NULL)
        return ERRORS_PROGRAMMES_NEED_MODE;
    else if (!strcmp(mode, "-G"))
        return CREATE_create(inputFile, outputFileOrToSearch, algo);
    else if (!strcmp(mode, "-L"))
      return SEARCH_search(inputFile);

    return ERRORS_PROGRAMMES_NEED_MODE;
}
/**
 * Permet de lancer le processus.
 * Ne s'occupe que de :
 *  - Lancer le programme
 *  - Recupérer le code d'erreur s'il yen a un
 *  - Afficher un message d'erreur liée à l'erreur si elle existe
 * @param argc <int> : Nombre d'element dans le tableaux argv
 * @param argv <char**> : Tableau de chaine de carractère
 * @return Si autre que 0 le programme à rencontré des erreurs
 */
int main(const int argc, char* argv[]) {
    int result = mainStrategy(argc, argv);
    Errors_printf(result);
    return result;

    return 0;
}