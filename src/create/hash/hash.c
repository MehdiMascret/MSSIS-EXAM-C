#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

char* Hash_defaultHash(char* text_clair) {
    return text_clair;
}

HashAlgorithm hashAlgorithmSingleton = {
    defaultHash: Hash_defaultHash
};

Hash* Hash_getHash(char *name) {
    return hashAlgorithmSingleton.defaultHash;
}