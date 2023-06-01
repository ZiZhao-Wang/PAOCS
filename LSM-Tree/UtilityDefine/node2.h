 

#ifndef EXPERIMENT1_NODE2_H
#define EXPERIMENT1_NODE2_H

#include <iostream>
const int MAX_LEVEL = 32;
const int P_FACTOR = RAND_MAX >> 2;

typedef struct LSMEntry
{
    uint64_t key;
    uint64_t val;
    int maxlevel;
    struct LSMEntry **next;

}LSMEntry;

typedef struct HeadNode
{

    int    CurrentLevel;
    int    Nodenumber;
    LSMEntry * Node;

}HeadNode;


typedef struct SkiplistNode 
{
    uint64_t key;
    uint64_t value;
    int maxLevel;
    struct SkiplistNode **forward;
} SkiplistNode;


typedef struct 
{
    SkiplistNode *head;
    int level;
} Skiplist;


SkiplistNode *skiplistNodeCreat(uint64_t key,uint64_t val, int maxLevel);

Skiplist* skiplistCreate();

void skiplistNodeFree(SkiplistNode* obj);

LSMEntry * NILInit();

LSMEntry * Init();

LSMEntry * Initialize(uint64_t hashkey, uint64_t val1,int maxlevel);

#endif