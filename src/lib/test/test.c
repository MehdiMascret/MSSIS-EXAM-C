#include "test.h"
#include <stdlib.h>

typedef struct TestAnalyseError TestAnalyseError;
struct TestAnalyseError {
    char* message;
    TestAnalyseError* next;
};

TestAnalyseError* create_TestAnalyseError(char *message) {
    TestAnalyseError* error = (TestAnalyseError*) malloc(sizeof(TestAnalyseError));

    error->message = message;
    error->next = NULL;

    return error;
}
void Test_analyse (Test* this) {
    int success = 0;
    TestAnalyseError* first = NULL;
    TestAnalyseError* last = NULL;

    for (int index = 0; index <= this->length; index++) {
        char *message = this->tests();
        if (*message == NULL) {
            success++;
        };
        else if (first == NULL) {
            first = last = create_TestAnalyseError(message);
        } else {
            last->next = create_TestAnalyseError(message);
            last = last->next;
        }
    }
     
    if (success == this->length) {
        printf("✅: %s (%d/%d)", this->label, success, this->length);
    } else {
        perror("❌: %s (%d/%d)", this->label, success, this->length);
    }

    TestAnalyseError* current = first;
    TestAnalyseError* toFree;
    while (current) {
        perror("%s\n", current->message);
        toFree = current;
        current = current->next;
        free(toFree);
    }
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

Test *create_Test(TestElement_Lambda* (*tests), int length, char* label) {
    Test *test = (Test *) malloc(sizeof (Test));

    this->length = length;
    test->tests = tests;
    test->free = free;
    test->analyse = analyse;
    test->label = label;
    return test;
}