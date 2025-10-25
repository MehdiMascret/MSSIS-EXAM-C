#include "node.h"
#include "../malloc_string/malloc_string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Node* Node_Create() {
    Node *node = malloc(sizeof(Node));
    node->head = NULL;
    return node;
}
void NodeChild_Free(NodeChild *child) {
    if (child == NULL)
        return;
    NodeChild_Free(child->left);
    NodeChild_Free(child->right);
    free(child->key);
    free(child->value);
    free(child);
}
void Node_Free(Node *node) {
    NodeChild_Free(node->head);
    free(node);
}
NodeChild* NodeChild_Create(char *key, char *value) {
    NodeChild *child = malloc(sizeof(NodeChild));
    child->key = MALLOC_STRING(key);
    child->value = MALLOC_STRING(value);
    return child;
}
void NodeChild_Add(NodeChild *head, NodeChild *child) {
    int cmp = strcmp(head->key, child->key);
    if (cmp < 0) {
        if (head->left == NULL)
            head->left = child;
        else
            NodeChild_Add(head->left, child);
    } else if (cmp > 0) {
        if (head->right == NULL)
            head->right = child;
        else
            NodeChild_Add(head->right, child);
    } else {
        head->value = MALLOC_STRING(child->value);
        NodeChild_Free(child);
    }
}
void Node_Add(Node *node, char *key, char *value) {
    NodeChild *created = NodeChild_Create(key, value);
    if (node->head == NULL)
        node->head = created;
    else
        NodeChild_Add(node->head, created);
}
char* NodeChild_Get(NodeChild *head, char *key) {
    if(head == NULL)
        return NULL;
    int cmp = strcmp(head->key, key);
    if (cmp == 0)
        return head->value;
    else if (cmp < 0) {
        return NodeChild_Get(head->left, key);
    } else {
        return NodeChild_Get(head->right, key);
    }
}
char* Node_Get(Node *node, char *key) {
    if (node == NULL || key == NULL)
        return NULL;
    return NodeChild_Get(node->head, key);
}