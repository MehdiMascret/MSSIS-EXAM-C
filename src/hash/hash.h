#ifndef HASH_H
#define HASH_H

/**
 * Définit de la fonction lambda Hash
 * Transforme une chaine de carractère en une autre
 * @param text_clair <char*> le texte en clair
 * @return <char*> le message hasher
 */
typedef char* (*Hash) (char* text_clair);

/**
 * Les différents algorithme existant:
 * - SHA256
 * - SHA512
 */
typedef struct HashAlgorithm HashAlgorithm;
struct HashAlgorithm {
    Hash H256;
    Hash H512;
};

/**
 * @param name nom de l'algorithme de hash
 * @return Fonction lambda Hash permet d'hasher
 */
Hash Hash_getHash(char *name);

#endif