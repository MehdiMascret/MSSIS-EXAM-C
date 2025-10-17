#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

char* HASH_H256(char* text_clair) {
    return text_clair;
}

HashAlgorithm hashAlgorithmSingleton = {
    H256: HASH_H256
};

Hash* Hash_getHash(char *name) {
    Hash* hash = hashAlgorithmSingleton.H256;
    return hash;
}