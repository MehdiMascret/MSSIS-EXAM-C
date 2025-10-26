#include "node.h"
#include "../malloc_string/malloc_string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * Permet de créer un gestionnaire d'arbre binaire.
 * Il permet de gérer :
 * - L'allocation de chaque noeud
 * - L'ajout d'élément
 * - La recherche de la valeur par sa clé
 * - Sa dés-allocation mémoire.
 * @return Un gestionnaire d'arbre binaire
 */
Node* Node_Create() {
    Node *node = malloc(sizeof(Node));
    node->head = NULL;
    return node;
}

/**
 * Désalloué un noeud et ses enfant.
 * @param node <NodeChild*> Le noeud de l'arbre binaire a désalloué.
 */
void NodeChild_Free(NodeChild *child) {
    if (child == NULL)
        return;
    NodeChild_Free(child->left);
    NodeChild_Free(child->right);
    free(child->key);
    free(child->value);
    free(child);
}

/**
 * Désalloué un arbre binaire.
 * @param node <Node*> L'arbre binaire a désalloué.
 */
void Node_Free(Node *node) {
    NodeChild_Free(node->head);
    free(node);
}

/**
 * Permet de créer un noeud de l'arbre binaire.
 * @param key <char*> La clé du noeud
 * @param value <char*> La valeur associé à la clé
 * @return Noeud d'arbre binaire.
 */
NodeChild* NodeChild_Create(char *key, char *value) {
    NodeChild *child = malloc(sizeof(NodeChild));
    child->key = MALLOC_STRING(key);
    child->value = MALLOC_STRING(value);
    child->left = NULL;
    child->right = NULL;
    return child;
}

/**
* Si la clé existe déja dans le noeud alors il modifie la valeur
* Si la clé n'existe pas alors il rajoute un nouveau noeud
* @param node <NodeChild**> pointeur qui parcours tout l'arbre binaire pour déposer à une "feuille" le nouveau noeud
* @param child <NodeChild*> pointer qui represente l'enfant à déposer dans l'arbre
*/
void NodeChild_Add(NodeChild **node, NodeChild *child) {
    bool alreadyExist = false;
    while (*node && !alreadyExist) {
        NodeChild *n = *node;
        int cmp = strcmp(n->key, child->key);
        if (cmp < 0) {
            node = &n->left;
        } else if (cmp > 0) {
            node = &n->right;
        } else {
            alreadyExist = true;
            n->value = MALLOC_STRING(child->value);
            NodeChild_Free(child);
        }
    }
    if (!alreadyExist)
        *node = child;
}

/**
 * Ajouter un element (clé / valeur) à l'arbre binaire.
 * @param node <Node*> L'arbre binaire qui contiendra la nouvelle valeur.
 * @param key <char*> La clé de la valeur dans une HashMap.
 * @param value <char*> La valeur dans une HashMap.
 */
void Node_Add(Node *node, char *key, char *value) {
    NodeChild *created = NodeChild_Create(key, value);
    if (node->head == NULL)
        node->head = created;
    else
        NodeChild_Add(&node->head, created);
}

/**
* Recherche dan un arbre binaire de facon récursive où se trouve la clé.
* Quand il trouve la clé alors il retourne la valeur
* @param head <NodeChild*> pointe sur la racine de l'arbre binaire
* @param key <char*> Clé à rechercher dans l'arbre binaire
*/
char* NodeChild_Get(NodeChild *head, char *key) {
    if(head == NULL)
        return NULL;
    int cmp = strcmp(head->key, key);
    if (cmp == 0)
        return head->value;
    else if (cmp < 0) {
        return NodeChild_Get(head->left, key);
    } else {
        return NodeChild_Get(head->right, key);
    }
}

/**
 * Rechercher une valeur via une clé et un arbre binaire.
 * @param node <Node*> L'arbre binaire qui contient la valeur.
 * @param key <char*> La clé de la valeur dans une HashMap.
 * @return La valeur associée à la clé dans une HashMap.
 */
char* Node_Get(Node *node, char *key) {
    if (node == NULL || key == NULL)
        return NULL;
    return NodeChild_Get(node->head, key);
}