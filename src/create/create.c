#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../read/read.h"
#include "create.h"
#include "../hash/hash.h"
#include "../error/error.h"

/**
* Utiliser pour l'option Generate (-G)
* Permet de générer un fichier outputPathFile.
* Les lignes d'inputPathFile sont transformé en hash lisible
* Puis le logiciel remplit la rainbow table outputPathFile sous ce format : "hash[lineInInputPathFile]:lineInInputPathFile".
* Une ligne peut avoir des espaces mais doit se terminer par un "\n" ou un EOF (end of file)
* @param inputPathfile <char*> : Emplacement du fichier input, chaque ligne de ce fichier va être hasher
* @param outputPathFile <char*> : Emplacement du fichier output, récupère le hash et le mot de passe clair du fichier inputFilePath
* @param algorithm <char*> : Algorithme à utiliser
* @return <int> : 0 = PAS D'ERREUR / AUTRE = ERREUR
*/
int CREATE_create(char *inputPathfile, char *outputPathFile, char *algorithm) {
    // S'il n'y a aucun fichier input alors c'est une erreur
    if (inputPathfile == NULL)
        return ERRORS_PROGRAMMES_FILE_INPUT_NOT_FOUND;
    // S'il n'y a aucun fichier output alors c'est une erreur
    if (outputPathFile == NULL)
        return ERRORS_PROGRAMMES_FILE_OUTPUT_NOT_FOUND;

    // Si le fichier input n'existe pas alors c'est une erreur
    FILE *fread = fopen(inputPathfile, "r");
    if (fread == NULL)
        return ERRORS_PROGRAMMES_FILE_INPUT_NOT_FOUND;


    // Si le fichier output n'existe pas alors on le créer et si c'est impossible alors c'est une erreur
    FILE *fwrite = fopen(outputPathFile, "w");
    if (fwrite == NULL)
        fwrite = fopen(outputPathFile, "wx");
    if (fwrite == NULL)
        return ERRORS_PROGRAMMES_FILE_OUTPUT_NOT_FOUND;

    // S'il n'y a aucun algo de hash alors c'est une erreur !
    Hash hash = Hash_getHash(algorithm);
    if (hash == NULL)
        return ERRORS_PROGRAMMES_HASH_NOT_INITIALIZED;

    char *line = NULL;
    int nbOfLines = 0;
    int nbOfPages = 0;

    // Pour chaque lignes dans input, hash puis mis dans output sous le format :"hash[lineInInputPathFile]:lineInInputPathFile".
    // Pour avoir un suivie, tout les millions de lignes lue tu me print un message pour savoir où tu en es.
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