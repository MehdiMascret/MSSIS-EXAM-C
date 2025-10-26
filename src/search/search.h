#ifndef SEARCH_H
#define SEARCH_H

/**
 * Utiliser pour l'option Load (-L)
 * Permet de chercher des mots de passes par rapport à leurs Hash.
 * Ce finit si on tape exit lors de l'utilisation de la console
 *
 * @param inputPathfile inputPathfile <char*> : Emplacement du fichier input, comportant les hash et les mots de passe
 * @return <int> : 0 = PAS D'ERREUR / AUTRE = ERREUR
 */
int SEARCH_search(char *inputPathfile);

#endif