typedef char* Hash (char* text_clair);

typedef struct HashAlgorithm HashAlgorithm;

struct HashAlgorithm {
    Hash* defaultHash;
};

Hash* Hash_getHash(char *name);