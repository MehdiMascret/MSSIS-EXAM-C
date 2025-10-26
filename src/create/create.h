#ifndef CREATE_H
#define CREATE_H

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
int CREATE_create(char *inputPathfile, char *outputPathFile, char *algorithm);

#endif