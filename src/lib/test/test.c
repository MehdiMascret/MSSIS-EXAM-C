#include "test.h"
#include <stdlib.h>

void analyse (Test* this) {

}

void free(Test *this) {

}

Test *create_Test(TestElement_Lambda* (*tests)) {
    Test *test = (Test *) malloc(sizeof (Test));

    test->tests = tests;
    test->free = free;
    test->analyse = analyse;

    return test;
}