#ifndef HASH_H
#define HASH_H

typedef char* (*Hash) (char* text_clair);

typedef struct HashAlgorithm HashAlgorithm;

struct HashAlgorithm {
    Hash H256;
    Hash H512;
};

Hash Hash_getHash(char *name);

#endif