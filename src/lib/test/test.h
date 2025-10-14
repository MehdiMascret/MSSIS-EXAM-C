#ifndef LIB_TEST_H
#define LIB_TEST_H

typedef int TestElement_Lambda();

typedef struct Test Test;
struct Test {
    TestElement_Lambda* (*tests);
    void (*analyse)(Test* this);
    void (*free)(Test* this);
};

Test *create_Test(TestElement_Lambda* (*tests));

#endif
