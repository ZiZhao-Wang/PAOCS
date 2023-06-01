/**
 * @date     18/9/2022
 * @author   zz.wang
 * @details: This code is used to merge 
 *
 * IDENTIFICATION:
 *          src/LSM-Tree/UtilityDefine/merge.h
 **/

#include "../UtilityDefine/merge.h" // Related header file
#include <iostream>


void MergeContext::Insert(entry_t *entries, size_t EntryNum) 
{
    MergeEntry MergeItem;
    size_t index = 0;
    while(index < EntryNum) 
    {
        MergeItem.SingleEntry = entries[index];
        queue.push(MergeItem);
        index++;
    }
    free(entries);
}

void MergeContext::Insert(std::vector<entry_t> entries) 
{
    
    MergeEntry MergeItem;
    size_t index = 0;
    while(index < entries.size()) 
    {
        MergeItem.SingleEntry = entries[index];
        queue.push(MergeItem);
        index++;
    }
    //printf("priority_queue size: %lu \n",queue.size());

}

entry_t MergeContext::Contextpop(void) 
{
    // printf("priority_queue.top():%lu",queue.top().SingleEntry.key);
    // exit(0);
    MergeEntry current, next;
    entry_t entry;

    current = queue.top();
    next = current;
    int i = 0;

    while (next.SingleEntry.key == current.SingleEntry.key && !queue.empty())  // Only release the most recent value for a given key
    {
        queue.pop();
        next = queue.top();
    }

    return current.SingleEntry;
}

entry_t MergeContext::Contextpop1() 
{
    // printf("priority_queue.top():%lu",queue.top().SingleEntry.key);
    // exit(0);
    MergeEntry current;

    current = queue.top();

    if(!queue.empty())  // Only release the most recent value for a given key
    {
        queue.pop();
    }

    return current.SingleEntry;
}


bool MergeContext::IsEmpty(void) const 
{
    return queue.empty();
}
