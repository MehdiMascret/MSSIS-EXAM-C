#ifndef NODE_H
#define NODE_H

#include <stdbool.h>

/**
 * Structure permettant de gérer les noeuds d'un arbre binaire pour une HashMap
 * key <char*> Clé de la node
 * Value <char*> Valeur stocké
 * Left <NodeChild> noeud gauche
 * Right <NodeChild> noeud droite
*/
typedef struct NodeChild NodeChild;
struct NodeChild {
    char *key;
    char *value;
    NodeChild *left;
    NodeChild *right;
};

/**
 * Structure permettant de stoker le noeud head gérant les noeuds d'un arbre binaire pour une HashMap
 * head <NodeChild> noeud principal
*/
typedef struct Node Node;
struct Node {
    NodeChild *head;
};

/**
 * Permet de créer un gestionnaire d'arbre binaire.
 * Il permet de gérer :
 * - L'allocation de chaque noeud
 * - L'ajout d'élément
 * - La recherche de la valeur par sa clé
 * - Sa dés-allocation mémoire.
 * @return Un gestionnaire d'arbre binaire
 */
Node* Node_Create();

/**
 * Désalloué un arbre binaire.
 * @param node <Node*> L'arbre binaire a désalloué.
 */
void Node_Free(Node *node);

/**
 * Ajouter un element (clé / valeur) à l'arbre binaire.
 * @param node <Node*> L'arbre binaire qui contiendra la nouvelle valeur.
 * @param key <char*> La clé de la valeur dans une HashMap.
 * @param value <char*> La valeur dans une HashMap.
 */
void Node_Add(Node *node, char* key, char* value);

/**
 * Rechercher une valeur via une clé et un arbre binaire.
 * @param node <Node*> L'arbre binaire qui contient la valeur.
 * @param key <char*> La clé de la valeur dans une HashMap.
 * @return La valeur associée à la clé dans une HashMap.
 */
char* Node_Get(Node *node, char* key);

#endif //NODE_H