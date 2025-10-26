#ifndef HASHMAP_H
#define HASHMAP_H

#include "../node/node.h"


/**
 * Une hashmap presque comme Java, qui possède une capacité max (ici statique),
 * ayant pour chaque element du bucket un arbre binaire "Node".
 * Si cette position n'a pas été encore été utilisé alors sa valeur à l'index de position est à statesOfNodes = 0.
 * Node <Node**> Tableau de pointeur
 * statesOfNodes <unsigned short*> Tableau d'état de chaque element du tableau de pointer
*/
typedef struct HashMap HashMap;
struct HashMap {
    Node   **nodes;
    unsigned short *statesOfNodes; // 0=NOT_USED, 1=USED
};

/**
 * Permet de créer une Hashmap presque comme Java
 * @return une HashMap
 */
HashMap *HashMap_Create();
/**
 * Permet d'ajouter un element à la map
 * @param map <HashMap*> element à rajouter dans cette map
 * @param key <char*> clé de l' element
 * @param value <char*> valeur de l' element
 */
void HashMap_Set(HashMap *map, char *key, char *value);
/**
 * Permet d'obtenir la valeur associée à la clé
 * @param map <HashMap*> la map qui contient la clé
 * @param key <char*> la clé associée à la valeur
 * @return La valeur associée à la clé
 */
char* HashMap_Get(HashMap *map, char *key);

/**
 * Permet de désalloué une HashMap
 * @param map <HashMap> La map a désalloué
 */
void HashMap_Free(HashMap *map);

#endif //HASHMAP_H