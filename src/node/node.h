#ifndef NODE_H
#define NODE_H

#include <stdbool.h>

typedef struct NodeChild NodeChild;
struct NodeChild {
    char *key;
    char *value;
    NodeChild *left;
    NodeChild *right;
};

typedef struct Node Node;
struct Node {
    NodeChild *head;
};

Node* Node_Create();
void Node_Free(Node *node);
void Node_Add(Node *node, char* key, char* value);
char* Node_Get(Node *node, char* key);

#endif //NODE_H