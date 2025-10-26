#include "hashmap.h"
#include "../malloc_string/malloc_string.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/**
 * Pour éviter beaucoup de collision, il faut que capacity = nb_entrées_prévues / load_factor_cible
 * avec load_factor_cible égale à 0.75.
 * Puis avoir la puissance de 2 la plus haute de ce chiffre.
 *
 * capacity = 2^ceil(log_2(nb_entrées_prévues / load_factor_cible))
 * capacity = 2^ceil(log_2(16000000))
 * capacity = 2^24
 * capacity = 16777216
*/
#define HashMapCapacity 16777216
#define HashMapCapacityAndCalcul 16777215 // (HashMapCapacity - 1)

/**
* Fonction célèbre permettant de transformer une chaine de carractère en hash
* @parm str <char*> chaine de carractère à hasher
* @return un hash
*/
unsigned long djb2(const char *str) {
    unsigned long hash = 5381;
    unsigned char c;
    while (c = *str++)
        hash = (hash << 5) + hash + c;
    return hash;
}

/**
* Transforme un hash en index de tableau
*/
unsigned long HashMap_Index(unsigned long hash) {
    return hash & HashMapCapacityAndCalcul;
}

/**
 * Permet de créer une Hashmap presque comme Java
 * @return une HashMap
 */
HashMap *HashMap_Create() {
    HashMap *map = malloc(sizeof (HashMap));

    map->nodes = calloc(HashMapCapacity, sizeof (Node*));
    map->statesOfNodes = calloc(HashMapCapacity, sizeof (unsigned short));

    return map;
}

/**
 * Permet de désalloué une HashMap
 * @param map <HashMap> La map a désalloué
 */
void HashMap_Free(HashMap *map) {
    if (!map) return;
    for (unsigned long i = 0; i < HashMapCapacity; i++) {
        if (map->statesOfNodes[i] == 1) {
            Node_Free(map->nodes[i]);
        }
    }
    free(map->nodes);
    free(map->statesOfNodes);
    free(map);
}

/**
 * Permet d'ajouter un element à la map
 * @param map <HashMap*> element à rajouter dans cette map
 * @param key <char*> clé de l' element
 * @param value <char*> valeur de l' element
 */
void HashMap_Set(HashMap *map, char *key, char *val) {
    int index = HashMap_Index(djb2(key));
    if (map->statesOfNodes[index] == 0) {
        map->statesOfNodes[index] = 1;
        map->nodes[index] = Node_Create();
    }
    Node_Add(map->nodes[index], key, val);
}

/**
 * Permet d'obtenir la valeur associée à la clé
 * @param map <HashMap*> la map qui contient la clé
 * @param key <char*> la clé associée à la valeur
 * @return La valeur associée à la clé
 */
char* HashMap_Get(HashMap *map, char *key) {
    int index = HashMap_Index(djb2(key));
    if (map->statesOfNodes[index] == 0)
        return NULL;
    return Node_Get(map->nodes[index], key);
}