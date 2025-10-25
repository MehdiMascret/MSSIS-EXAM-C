#ifndef HASHMAP_H
#define HASHMAP_H

#include "../node/node.h"

typedef struct HashMap HashMap;

struct HashMap {
    Node   **nodes;
    unsigned short *statesOfNodes; // 0=NULL, 1=NOT_NULL
};

HashMap *HashMap_Create();
void HashMap_Set(HashMap *map, char *key, char *value);
char* HashMap_Get(HashMap *map, char *key);
void HashMap_Free(HashMap *map);

#endif //HASHMAP_H