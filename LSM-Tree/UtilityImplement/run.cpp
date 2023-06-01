#include "../UtilityDefine/run.h"
#include <cassert>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <fcntl.h>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include "../../Backend/IODisk/WriteDisk.h"
#include "../../Backend/SSDWrite/writer.h"
#include "../../Backend/SSDRead/reader.h"

vector<int> a;

Run::Run(unsigned long maxsize)
{
    this->MaxSize = maxsize;
    for(int i=0;i<this->MaxSize/CalculatePageCapacity(sizeof(entry_t));i++) //Initialize all page pointers as UINT64_MAX
    {
        PagePointers.emplace_back(UINT64_MAX);
    }
    MaxKey = 0;
    MinKey = UINT64_MAX;
    Size = 0;
}

void Run::PointersDisplay()
{
    for(size_t i=0;i<PagePointers.size();i++)
    {
        printf("page pointer:%lu\n",PagePointers[i]);
    }
}

int Run::RunDataWrite(void)
{

    uint64_t pagesize = CalculatePageCapacity(sizeof(entry_t));
    PageType Pointer;
    
    if(Rundata.size() == pagesize)
    {
        Pointer = SinglePageWrite(Rundata,PagePointers[(Size/pagesize)-1]);
        // printf("The %lu Page: %lu, Size: %lu\n",(Size/pagesize)-1,Pointer,Size);
        // printf("Datum of Run in Level write succeed!\n");
        PagePointers[(Size/pagesize)-1] = Pointer;
        Rundata.clear();
        return 0;  
    }
    printf("Datum size of Run doesn't matching, check again!");
    return -1;
}

std::vector<entry_t> Run::SingleRunRead()
{
    std::vector<entry_t> entries1; 
    // size_t Pagecapacity = CalculatePageCapacity(sizeof(entry_t));

    // //printf("Test 1 : size of page pointers:%lu\n",PagePointers.size());
    // for(size_t i=0; i<PagePointers.size();i++)
    // {
    //     if(PagePointers[i]== UINT64_MAX)
    //         continue;
    //     std::vector<entry_t> temp;
    //     temp = RunReadFromPage(PagePointers[i]);
    //     entries1.insert(entries1.end(),temp.begin(),temp.end());
    //     GPT[PagePointers[i]/4096][(PagePointers[i]%4096)/4] = false;
    // }
    // if(Rundata.size()!=0)
    // {
    //     entries1.insert(entries1.end(),Rundata.begin(),Rundata.end());
    // }
    //printf("Read from start page pointer:%lu end:%lu. total: %lu\n",PagePointers[0],PagePointers[PagePointers.size()-1],PagePointers.size());
    //printf("Test 3");
    return entries1;

    /** entry_t * entries1 = nullptr; 
    entry_t * head = nullptr;
    size_t Pagecapacity = CalculatePageCapacity(sizeof(entry_t));
    size_t PageBytes = Pagecapacity * sizeof(entry_t);

    entries1 = RunReadFromPage(PagePointers[0],Pagecapacity);
    head = entries1;
    head += Pagecapacity;

    printf("Test 1");
    for(size_t i=1; i<PagePointers[i];i++)
    {
        head = RunReadFromPage(PagePointers[i],Pagecapacity);
        printf("Test 2");
        entries1  = (entry_t *)realloc(entries1, PageBytes+100);
        if(entries1 == NULL)
        {
            EMessageOutput("Memory allocating failure in SingleRunRead",578);
        }
        head = entries1 + Pagecapacity*(i+1);
    } **/
}

void Run::PutValue(entry_t entry) 
{
    assert(Size < MaxSize);
    Rundata.emplace_back(entry);
    MaxKey = max(entry.key,MaxKey);
    MinKey = min(entry.key,MinKey);
    Size++;
   
    //a.emplace_back(entry.key);
    
    if(Rundata.size() == CalculatePageCapacity(sizeof(entry_t)) && Size != 0)
    {
        //a.emplace_back(entry.key);
        FencePointers.emplace_back(entry.key);
        int err = 0;// = RunDataWrite();
        // if(err==0)
        // {
        //     assert(Rundata.size() == 0); 
        // }
        // else
        // {
        //     EMessageOutput("Run failed!",104);
        // }
    }
}

VAL_t * Run::GetValue(KEY_t key)  
{
    if(Size == 0)
        return nullptr;
    VAL_t * value = new VAL_t;
    std::vector<entry_t> reads;

    //printf("Run size:%lu\n min:%lu max:%lu\n",Size,MinKey,MaxKey);
    if(FencePointers.size()!=0)
    {
        if (key < MinKey || key > MaxKey) 
        {
            return nullptr;
        }
    }
    
    std::vector<uint64_t>::iterator it = lower_bound(FencePointers.begin(),FencePointers.end(),key);
    size_t PageIndex = it-FencePointers.begin();

    if(PageIndex < PagePointers.size() && PagePointers[PageIndex]!=UINT64_MAX)
    {
        reads = RunReadFromPage(PagePointers[PageIndex]);;
        std::vector<entry_t>::iterator get;
        get = find(reads.begin(),reads.end(),entry_t{key,0});
        if(get!=reads.end())
        {
            *value = (*get).val;
            return value; 
        }
    }
    else
    {
        std::vector<entry_t>::iterator get;
        get = find(Rundata.begin(),Rundata.end(),entry_t{key,0});
        if(get!=reads.end())
        {
            *value = (*get).val;
            return value; 
        }
    }
    delete(value);
    return nullptr;
}




// vector<entry_t> * Run::range(KEY_t start, KEY_t end) 
// {
//     vector<entry_t> *subrange;
//     vector<KEY_t>::iterator next_page;
//     long subrange_page_start, subrange_page_end, num_pages, num_entries, i;

//     subrange = new vector<entry_t>;

//     // If the ranges don't overlap, return an empty vector
//     if (start > max_key || fence_pointers[0] > end) {
//         return subrange;
//     }

//     if (start < fence_pointers[0]) {
//         subrange_page_start = 0;
//     } else {
//         next_page = upper_bound(fence_pointers.begin(), fence_pointers.end(), start);
//         subrange_page_start = (next_page - fence_pointers.begin()) - 1;
//     }

//     if (end > max_key) {
//         subrange_page_end = fence_pointers.size();
//     } else {
//         next_page = upper_bound(fence_pointers.begin(), fence_pointers.end(), end);
//         subrange_page_end = next_page - fence_pointers.begin();
//     }

//     assert(subrange_page_start < subrange_page_end);
//     num_pages = subrange_page_end - subrange_page_start;
//     map_read(num_pages * getpagesize(), subrange_page_start * getpagesize());

//     num_entries = num_pages * getpagesize() / sizeof(entry_t);
//     subrange->reserve(num_entries);

//     for (i = 0; i < num_entries; i++) {
//         if (start <= mapping[i].key && mapping[i].key <= end) {
//             subrange->push_back(mapping[i]);
//         }
//     }

//     unmap();

//     return subrange;
// }

std::vector<uint64_t> Run::GetPagePointers(void)
{
    return PagePointers;
}

std::vector<KEY_t> Run::GetFencePointers(void)
{
    return FencePointers;
}

uint64_t Run::GetMaxKey(void)
{
    return MaxKey;
}

uint64_t Run::GetMinKey(void)
{
    return MinKey;
}


int Run::SetPagePointers(std::vector<uint64_t> pointers)
{
    assert(PagePointers.size()==0);
    for(size_t i=0;i<pointers.size();++i)
    {
        assert(pointers[i] != UINT64_MAX);
        PagePointers.emplace_back(pointers[i]);
        Size += CalculatePageCapacity(sizeof(entry_t));
    }

    if(pointers.size()*CalculatePageCapacity(sizeof(entry_t)) != MaxSize/2 )
    {
        return -1;
    }

    return 0;
}

int Run::SetFencePointers(std::vector<uint64_t> pointers)
{

    for(size_t i=0;i<pointers.size();++i)
    {
        FencePointers.emplace_back(pointers[i]);
        MaxKey = max(MaxKey,pointers[i]);
    }

    if(pointers.size()*CalculatePageCapacity(sizeof(entry_t))!=MaxSize/2 )
    {
        return -1;
    }

    return 0;
}

void Run::Reset(bool flag)
{
    if(FencePointers.size()!=0)
        FencePointers.clear();
    Size = 0;
    if(Rundata.size()!=0)
        Rundata.clear();
    if(flag)
    {
        if(PagePointers.size()!=0)
            PagePointers.clear();
    }
    MaxKey = 0;
    MinKey = UINT64_MAX;
}

int Run::SetMaxkey(KEY_t key)
{
    MaxKey = max(MaxKey,key);
}

void Run::Reset()
{
    if(FencePointers.size()!=0)
        FencePointers.clear();
    Size = 0;
    if(Rundata.size()!=0)
        Rundata.clear();
    for(size_t i=0;i<PagePointers.size();i++) //Initialize all page pointers as UINT64_MAX
    {
        PagePointers[i]=UINT64_MAX;
    }
    MaxKey = 0;
    MinKey = UINT64_MAX;

}

void Run::Unbind()
{
    PagePointers.clear();
    Rundata.clear();
    FencePointers.clear();
    Size = 0;
    AssertCondition(PagePointers.size()==0);
}

int Run::DataClear(std::vector<entry_t> MergeEntries)
{
    if(MultiPageWrite(MergeEntries,PagePointers) == -1)
    {
        return -1;
    } 
    return 0;
}

unsigned long Run::GetNowSize()
{
    return Size;
}

bool Run::Isfull(void)
{
    return Size >= MaxSize;
}

bool Run::IsEmpty(void)
{
    return Size == 0;
}