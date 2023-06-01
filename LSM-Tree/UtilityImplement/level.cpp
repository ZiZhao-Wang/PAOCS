#include "../UtilityDefine/level.h"
#include <cassert>
#include <unistd.h>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <fcntl.h>
#include <cstdlib>
#include <sys/mman.h>
#include <sys/types.h>
#include "../UtilityDefine/ResAllocate.h"

Level::Level(uint64_t buffersize)
{
    this->LevelNumber = LevelAlloctor();
	this->MaxRuns = 2;
	this->MaxRunSize = buffersize * pow(2,LevelNumber-1); //256*1024*2^(levelnumber-1)
    //printf("Run Maxsize:%lu in level %ld!\n",MaxRunSize,LevelNumber);
    for(int i=0;i<this->MaxRuns;i++)
    {
        Run run(MaxRunSize);
        Runs.emplace_back(run);
    }
}

void Level::PutValue(entry_t entry1)
{
    for(auto& run: Runs)
    {
        if(!run.Isfull())
        {
            run.PutValue(entry1);
            return ;
        }
    }
}

VAL_t* Level::GetValue(KEY_t key)
{
    VAL_t *val = new VAL_t;
    for(int i=0;i<Runs.size();i++)
    {  
       // printf("Search in Run %d, Run has %lu\n",i,Runs[i].GetNowSize());
        if(!Runs[i].IsEmpty())
        {
            val = Runs[i].GetValue(key);
            if(val != nullptr)
                return val;
        }
    }

    delete(val);
    return nullptr;
}

void Level::PutEntries(std::vector<entry_t> entry1)
{
    for(auto ent: entry1)
    {
        PutValue(ent);
    }
}

bool Level::IsEmpty(void)  
{
    for(auto& run:Runs)
    {
        if(run.GetNowSize()!= 0 && run.GetNowSize() == MaxRunSize)
        {
            return false;
        }
    }
    return true;
}

bool Level::IsFull(void)  
{
    for(auto& run:Runs)
    {
        if(run.GetNowSize()!= MaxRunSize && run.GetNowSize() == 0)
        {
            return false;
        }
    }
    return true;
}

long Level::GetMRunSize(void) const
{
    return MaxRunSize;
}

long Level::GetLevelNumber(void) const
{
    return LevelNumber;
}