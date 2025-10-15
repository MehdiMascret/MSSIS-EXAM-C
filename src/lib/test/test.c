#include "test.h"
#include <stdio.h>
#include <stdlib.h>


/**
 * Permet de lancer une analyse.
 * Si lambda est définit alors on envoye les infos aux lambda
 * Sinon on affiche une analyse en log.
 * 
 * @Param lambda {TestAnalyser_Lambda} - custom analyser
 */
void Test_analyse (Test* this, TestAnalyser_Lambda lambda) {
    int success = 0;

    // Compter le nombre de lambda en erreur et listes les messages
    char **messages = (char**) malloc(this->length * sizeof(char*));
    
    for (int index = 0; index <= this->length; index++) {
        char *message = messages[index];
        if (message == NULL) {
            success++;
        }
        messages[index] = message;
    }

    // Appeller la fonction lambda
    if (lambda != NULL)
        lambda(success, this->length, messages);
    else {
        // Afficher l'entete de l'analyse
        const char* checkOrFalse = success == this->length ? "✅" : "❌";     
        printf("%s: %s (%d/%d)", checkOrFalse, this->label, success, this->length);
        // Afficher tout les messages non null
        for (int index = 0; index <= this->length; index++) {
            if (messages[index] != NULL)
                printf("%s\n", messages[index]);
        }
    }

    // Libérer le pointeurs sur messages
    free(messages);
}

void Test_free(Test *this) {
    for (int index = 0; index <= this->length; index++) {
        free(this->tests[index]);
    }
    free(this->tests);
    free(this->analyse);
    free(this->free);
    free(this);
}

Test *create_Test(TestElement_Lambda* tests, int length, char* label) {
    Test *test = (Test *) malloc(sizeof (Test));

    test->length = length;
    test->tests = tests;
    test->free = Test_free;
    test->analyse = Test_analyse;
    test->label = label;
    return test;
}