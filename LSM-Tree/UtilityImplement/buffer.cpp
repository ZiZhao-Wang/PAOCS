#include <iostream>
#include "../UtilityDefine/buffer.h"
#include "../LsmTree.h"

#define N2 9999


Buffer::Buffer(size_t maxpage)
{
    // 1024 * 256 = 262144 
    uint64_t capacity =  CalculatePageCapacity(sizeof(entry_t));
    this->MaxSize = capacity*maxpage;
    size = 0;
    Head = skiplistCreate();
    //printf("key:%lu \n\n",Head->head->key);
    //printf("Test successful! Size of entry:%lu, Page capacity: %lu, Buffer size:%u\n",sizeof(entry_t),capacity,MaxSize);
}

int Buffer::RandomLevel()
{

    int v = 1;
    while (rand() < P_FACTOR && v < MAX_LEVEL) {
        v++;
    }
#ifdef DEBUG

#endif
    return v;

}

void Buffer::display()
{
    SkiplistNode * first = Head->head;

    while (first->forward[0]!=NULL)
    {
        printf("%lu\n",first->key);
        first = first->forward[0];        /* code */  
    }  
    return ;
}

bool Buffer::PutValue(KEY_t key1, VAL_t val1) 
{
#ifdef SET
    SkiplistNode * update[MAX_LEVEL];
    SkiplistNode * curr = Head->head;
    if (size >= MaxSize) 
    {
        return false;
    } 
    else 
    {
        for(int i=Head->level-1; i>=0; i--)
        {
            while(curr->forward[i] && curr->forward[i]->key < key1)
            {
                curr = curr->forward[i];
            }
            update[i] = curr;
        }
        if(curr->key == key1)
        {
        
            curr->key = key1;
            curr->value = val1;
            return true;
        }
        else
        {
            int v=RandomLevel();
            if(v > Head->level)
            {
                for(int i=Head->level; i<v; ++i )
                {
                    update[i] = Head->head;
                }
                Head->level = v;
            }

            SkiplistNode * lst = skiplistNodeCreat(key1,val1,v);
            for(int i=0;i<v;i++)
            {
                lst->forward[i] = update[i]->forward[i];
                update[i]->forward[i] = lst;
            }
            size++;
        }
        return true;
    }
#endif

    if (size >= MaxSize) 
    {
        return false;
    }

    entry_t SingleEntry;
    std::pair<std::set<entry_t>::iterator,bool> Tempair;
    SingleEntry.key = key1;
    SingleEntry.val = val1;
    size++;
    Tempair = Entries.insert(SingleEntry);
    if (Tempair.second == false)  // Update the entry if it already exists
    {
        Entries.erase(Tempair.first);
        Entries.insert(SingleEntry);
        size--;
    }

    return true;  
    
}

VAL_t * Buffer::GetValue(KEY_t key1)
{
#ifdef SKIPLIST
    SkiplistNode *curr = Head->head;
    for (int i = Head->level - 1; i >= 0; i--) 
    {
        while (curr->forward[i] && curr->forward[i]->key < key1) 
        {
            curr = curr->forward[i];
        }
    }
    curr = curr->forward[0];
    if (curr && curr->key ==key1 ) 
    {
        VAL_t * value = new VAL_t;
        *value = curr->value;
        return value;
    } 
    return nullptr;
#endif
    entry_t search_entry;
    set<entry_t>::iterator entry;
    VAL_t *val;

    search_entry.key = key1;
    entry = Entries.find(search_entry);

    if (entry == Entries.end()) 
    {
        return nullptr;
    }  
    
    val = new VAL_t;
    *val = entry->val;
    return val;

}

std::vector<entry_t> * Buffer::GetRange(KEY_t start, KEY_t end) const 
{
    entry_t SearchEntry;
    std::set<entry_t>::iterator SubRangeStart, SubRangeEnd;

    SearchEntry.key = start;
    SubRangeStart = Entries.lower_bound(SearchEntry);

    SearchEntry.key = end;
    SubRangeEnd = Entries.upper_bound(SearchEntry);

    return new std::vector<entry_t>(SubRangeStart, SubRangeEnd);
}


void Buffer::AllClear(void) 
{
#ifdef SKIPlist
    for (SkiplistNode * curr = Head->head; curr; ) 
    {
        SkiplistNode *prev = curr;
        curr = curr->forward[0];
        skiplistNodeFree(prev);
    }
    Head = skiplistCreate();
#endif

    Entries.clear();
    size = 0;

}

uint64_t Buffer::GetMaxSize()
{
    return MaxSize;
}

std::vector<entry_t> Buffer::GetEntries()
{
#ifdef sk
    std::vector<entry_t> values;
     SkiplistNode * first = Head->head;

    while (first->forward[0]!=NULL)
    {
        if(first->key !=0)
        {
            entry_t en;
            en.key = first->key;
            en.val = first->value;
            values.emplace_back(en);
        }
        first = first->forward[0];        /* code */
    }
    entry_t en;
    en.key = first->key;
    en.val = first->value;
    values.emplace_back(en);

    return values;
#endif
    std::vector<entry_t> valus;
    std::set<entry_t>::iterator it;
    for(it = Entries.begin();it != Entries.end(); it++)
    {
        valus.emplace_back(*it);
    }
    return valus;
}
