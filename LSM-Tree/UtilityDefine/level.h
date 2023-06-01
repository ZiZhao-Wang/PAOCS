/**
 * @date   7/9/2022
 * @author zz.wang
 * @details
 *          The following code define "Level" class and "Run" class. 
 *          The first class storing datum from "buffer" or last "Level", every "level" has 2 or 2^i(i=2,3,4...) 
 *          "Runs" where the size equals size of buffer.
 *          Every Level has three parameters:
 *          LevelNumber: Number of a se4pecific Level.
 *          MaxRus: Maximum of Runs in a specific Level, it equals "2^LevelNumber(LevelNumber= 1,2,3,4...)" 
 *          MaxRunSize: Size of Run, it equals buffer size(In this OC-SSD mode(FEMU), the default value is 64(that means every Run can store 1MB datum)). 
 * IDENTIFICATION:
 *          src/LSM-Tree/UtilityDefine/level.h
 **/

#ifndef EXPERIMENT1_LSMTREE_LEVEL_H
#define EXPERIMENT1_LSMTREE_LEVEL_H

#include <vector>
#include <queue>
#include "../../Auxizilary/pre_definition.h"
#include "../../Backend/IODisk/WriteDisk.h"
#include "../../Auxizilary/SysOutput.h"
#include "run.h"

class Level 
{
private:
    int  MaxRuns;
    long MaxRunSize;
    long LevelNumber;

public:
    std::vector<Run> Runs;
    Level(uint64_t);
    void PutValue(entry_t entry1);
    VAL_t* GetValue(KEY_t key);
    void PutEntries(std::vector<entry_t>);
    bool IsEmpty(void);
    bool IsFull (void);
    long GetMRunSize(void) const;
    long GetLevelNumber(void) const;

};


#endif   // EXPERIMENT1_LEVEL_H