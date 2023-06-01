/**
 * @date:   7/9/2022
 * @author: zz.wang
 * @email:  zz.wang@siat.ac.cn
 * @details:
 *          This file shows how to construct a disk-based LSM-Tree.
 *
 * IDENTIFICATION:
 *          src/LSM-Tree/LSMTree.h
 **/

#ifndef EXPERIMENT1_LSMTREE_H
#define EXPERIMENT1_LSMTREE_H

#include <vector>
#include "UtilityDefine/buffer.h"
#include "UtilityDefine/level.h"
#include "UtilityDefine/spin_lock.h"
#include "UtilityDefine/worker_pool.h"
#include "../Auxizilary/pre_definition.h"
#include "UtilityDefine/level.h"
#include "../Auxizilary/SysOutput.h"
#include "UtilityDefine/merge.h"
#include "UtilityDefine/run.h"


#define DEFAULT_TREE_DEPTH 5
#define DEFAULT_TREE_FANOUT 10
#define DEFAULT_BUFFER_NUM_PAGES 64     // 64 pages = 1MBytes
#define DEFAULT_THREAD_COUNT 1          // Single thread query
#define DEFAULT_BF_BITS_PER_ENTRY 0.5   // bloom filter bits


extern uint32_t LSMTreeReadPhysicalPage;
extern uint32_t LSMTreeWritePhysicalPage;
extern uint32_t LSMTreeErasehysicalPage;


class LSMTree 
{

private:
    //float bf_bits_per_entry;
    // 7-levels 
    vector<Level> Levels;
    Buffer buffer;

public:
    LSMTree(size_t ,int );
    int PutValue(KEY_t, VAL_t);
    VAL_t* GetValue(KEY_t);
    void GetRange(KEY_t, KEY_t);
    void UpdateValue(KEY_t, VAL_t);
    void DeleteValue(KEY_t);
    void load(std::string);
    void display();
    int FlushInto(vector<Level>::iterator);
    Run * get_run(int);
};


void LSMtreeInit(void);

/* Portable function declaration */
void LSMTreePort();

#endif //EXPERIMENT1_LSMTREE_H