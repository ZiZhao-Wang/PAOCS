#include "node2.h"
#include <iostream>
#include <stdlib.h>

SkiplistNode *skiplistNodeCreat(uint64_t key,uint64_t val, int maxLevel) 
{
    SkiplistNode *obj = (SkiplistNode *)malloc(sizeof(SkiplistNode));
    obj->value = val;
	obj->key = key;
    obj->maxLevel = maxLevel;
    obj->forward = (SkiplistNode **)malloc(sizeof(SkiplistNode *) * maxLevel);
    for (int i = 0; i < maxLevel; i++) {
        obj->forward[i] = NULL;
    }
    return obj;
}


Skiplist* skiplistCreate() 
{
    Skiplist *obj = (Skiplist *)malloc(sizeof(Skiplist));
    obj->head = skiplistNodeCreat(0,0, MAX_LEVEL);
    obj->level = 0;
    srand(time(NULL));
    return obj;
}

void skiplistNodeFree(SkiplistNode* obj) 
{
    if (obj->forward) 
    {
        free(obj->forward);
        obj->forward = NULL;
        obj->maxLevel = 0;
    }
    free(obj);
}
