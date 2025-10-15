#ifndef LIB_TEST_H
#define LIB_TEST_H

/**
 * Permet de définir les tests automatique
 * Doit retourner un null s'il n'y a pas d'erreur
 * Sinon retourner le message d'erreur
 * 
 * @Return {char *} - Message d'erreur
 */
typedef char* TestElement_Lambda();

/**
 * Permet de créer des teste automatique
 * @Method free {void}: Permet de liberer l'allocation de la mémoire
 * @Method analyse {void}: Permet de lancer l'analyse
 * @Lambda tests {TestElement_Lambda[]}: Tableaux de tests
 * @Field length {int} - Nombre d'elements du tableaux de tests
 * @Field label {char*} - Label du tests
 * 
 */
typedef struct Test Test;
struct Test {
    TestElement_Lambda* (*tests);
    void (*analyse)(Test* this);
    void (*free)(Test* this);
    int length;
    char* label;
};

Test *create_Test(TestElement_Lambda* (*tests), int length, char* label);

#endif
