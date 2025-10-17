#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include "hash.h"

/**
*    On Transforme un hexa comprehensible machine à un hexa compréhensible homme
*
*    Si hex inférieur à 10 alors on fait: hex + '0' <=> hex + 48
*    Sinon Comme hex sera supérieur à 10 alors on fait: hex - 10 + 'A' <=> hex + 65 - 10 <=> hex + 55
*
*    @Param hex {char}  - L'hexa compréhensible machine, donc l'hexadecimal à transformer en lettre hexa compréhensible
*    @Return {char}     - L'hexa compréhensible homme, donc l'hexa transformer
*/
char HASH_hexLetter(unsigned char hex) {
    if (hex < 10)
        return hex + 48;
    return hex + 55;
}

char* HASH_CharArrayToOctetArray(char *charArray, int charArrayLength) {
    int length = 2*SHA256_DIGEST_LENGTH + 3;
    char* octetArray = malloc(length);
    octetArray[0] = '0';
    octetArray[1] = 'x';
    octetArray[length-1] = '\0';

    for (int index = 0; index < charArrayLength; index++) {
        unsigned char c = charArray[index];
        char octet[3] = {
            HASH_hexLetter(c >> 4),
            HASH_hexLetter(c & 0xf),
            '\0'
        };
        octetArray[2*index+2] = octet[0];
        octetArray[2*index+3] = octet[1];
    }
    return octetArray;
}

/**
*    Parties des listes des HASH disponibles
*    Ils doivent tous passer par HASH_CharArrayToOctetArray(hash, sizeof(hash)) pour
*    transformer le hash an array d'hexadecimal compréhensible
*/

char* HASH_H256(char* text_clair) {
    unsigned char digest[SHA256_DIGEST_LENGTH + 1];
    digest[SHA256_DIGEST_LENGTH] = '\0';
    SHA256((unsigned char*)text_clair, strlen(text_clair), digest);
    return HASH_CharArrayToOctetArray(digest, SHA256_DIGEST_LENGTH);
}

char* HASH_H128(char* text_clair) {
    unsigned char digest[SHA128_DIGEST_LENGTH + 1];
    digest[SHA128_DIGEST_LENGTH] = '\0';
    SHA256((unsigned char*)text_clair, strlen(text_clair), digest);
    return HASH_CharArrayToOctetArray(digest, SHA128_DIGEST_LENGTH);
}


HashAlgorithm hashAlgorithmSingleton = {
    H256: HASH_H256,
    H128: HASH_H128
};

Hash* Hash_getHash(char *name) {
    if (name == NULL) return hashAlgorithmSingleton.H256;
    if (!strcmp(name, "HS256")) return hashAlgorithmSingleton.H256;
    return NULL;
}

