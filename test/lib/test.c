#include "../../src/lib/test/test.h"
#include <stdio.h>
#include <string.h>

char* createList() {
    return NULL;
}

void analyser(int success, int length, char **messages) {
    printf("[sucess: %d, length: %d]\n");
    int waitingSuccess = 1;
    int waitingLength  = 1;
    printf("%s / [success;length] / waiting: [%d;%d] / got: [%d; %d]", 
        success == waitingSuccess && length == waitingLength ? "✅" : "❌",
        waitingSuccess, waitingLength,
        success, length
    );
    char* waittingMessage = {
        NULL,
    };
    int minLenght = min(length, waitingLength);
    for (int index = 0; index < minLenght; index++) {
        if (strcmp(waittingMessage[index], messages[index])) {
            printf("❌: waitingMessage <> message / %s <> %s", waittingMessage[index], messages[index]);
        }
    }
}

int main() {
    TestElement_Lambda* tests = {
        createList
    };
    Test* test = create_Test(tests, 2, "Testing the lib Test");

    test->analyse(test, analyser);
    test->free(test);

    return 0;
}