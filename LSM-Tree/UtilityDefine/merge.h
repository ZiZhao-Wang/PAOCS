/**
 * @date     18/9/2022
 * @author   zz.wang
 * @details 
 *           This code is used to merge 
 *
 * IDENTIFICATION:
 *          src/LSM-Tree/UtilityDefine/merge.h
 **/
#ifndef EXPERIMENT1_MERGE_H
#define EXPERIMENT1_MERGE_H

#include <cassert>  //C library file
#include <functional> // C++
#include <vector>
#include <queue>      // Library file
#include "../../Auxizilary/pre_definition.h" //header files in this project

 
typedef struct MergeEntry
{

    entry_t SingleEntry;

    bool operator < (const MergeEntry& other) const 
    {
        // Order first by keys, then by precedence
        if (SingleEntry.key == other.SingleEntry.key) 
        {
            return  SingleEntry.val < other.SingleEntry.val;
        } 
        else 
        {
            return SingleEntry.key > other.SingleEntry.key;
        }
    }

}MergeEntry;

class MergeContext 
{
private:

    std::priority_queue<MergeEntry, std::vector<MergeEntry>, std::less<MergeEntry> > queue;

public:
    void Insert(entry_t *, size_t);
    void Insert(std::vector<entry_t> entries); 
    entry_t Contextpop(void);
    entry_t Contextpop1(); 
    bool IsEmpty(void) const;
    
};

#endif