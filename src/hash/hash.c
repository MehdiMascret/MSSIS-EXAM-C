#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include "hash.h"

/**
*    On Transforme un hexa comprehensible machine à un hexa compréhensible homme
*    @Param hex {char}  - L'hexa compréhensible machine, donc l'hexadecimal à transformer en lettre hexa compréhensible
*    @Return {char}     - L'hexa compréhensible homme, donc l'hexa transformer
*/
char HASH_hexLetter(unsigned char hex) {
    // Si hex inférieur à 10 alors on fait: hex + '0' <=> hex + 48
    if (hex < 10)
        return hex + 48;
    // Sinon Comme hex sera supérieur à 10 alors on fait: hex - 10 + 'A' <=> hex + 65 - 10 <=> hex + 55
    return hex + 55;
}

/**
*    On Transforme une chaine d'hexa comprehensible machine à une chaine d'hexa compréhensible homme
*
*    Si hex inférieur à 10 alors on fait: hex + '0' <=> hex + 48
*    Sinon Comme hex sera supérieur à 10 alors on fait: hex - 10 + 'A' <=> hex + 65 - 10 <=> hex + 55
*
*    @Param hex {char}  - L'hexa compréhensible machine, donc l'hexadecimal à transformer en lettre hexa compréhensible
*    @Return {char}     - L'hexa compréhensible homme, donc l'hexa transformer
*/
char* HASH_CharArrayToOctetArray(char *charArray, int charArrayLength) {
    /**
    * Taille du hash compréhensible homme
    * 2* car chaque octet machine doit etre transformer en deux hexa comprehensible homme.
    * - example : 255 (machine) = FF (homme)
    * +3 pour "0x" au début et '\0' à la fin
    */
    int length = 2*charArrayLength + 3;

    char* octetArray = malloc(length);
    octetArray[0] = '0';
    octetArray[1] = 'x';
    octetArray[length-1] = '\0';

    // Pour chaque octet, les transformer en hexa comprehensible homme
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
// Algo de hash sha 256
char *HASH_H256(char *text_clair) {
    unsigned char digest[SHA256_DIGEST_LENGTH + 1];
    digest[SHA256_DIGEST_LENGTH] = '\0';
    SHA256((unsigned char*)text_clair, strlen(text_clair), digest);
    return HASH_CharArrayToOctetArray(digest, SHA256_DIGEST_LENGTH);
}

// Algo de hash sha 512
char *HASH_H512(char *text_clair) {
    unsigned char digest[SHA512_DIGEST_LENGTH + 1];
    digest[SHA512_DIGEST_LENGTH] = '\0';
    SHA512((unsigned char*)text_clair, strlen(text_clair), digest);
    return HASH_CharArrayToOctetArray(digest, SHA512_DIGEST_LENGTH);
}

// Singleton définisant tout les algo
HashAlgorithm hashAlgorithmSingleton = {
    .H256 = HASH_H256,
    .H512 = HASH_H512,
};

/**
* Si aucun algo n'a été preciser alors je donne un algo de base
* Sinon s'il existante dans ma base alors je lui donne
* Sinon c'est une erreur car aucun algo n'existe pour ce nom
*
* @param name <char*> nom de la fonction lambda
* @return <Hash> fonction lambda Hash permettant de hasher un message clair
*/
Hash Hash_getHash(char *name) {
    if (name == NULL) return hashAlgorithmSingleton.H512;

    if (!strcmp(name, "SHA256"))
        return hashAlgorithmSingleton.H256;

    if (!strcmp(name, "SHA512"))
        return hashAlgorithmSingleton.H512;

    return NULL;
}
