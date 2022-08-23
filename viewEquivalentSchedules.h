#include "transaction.h"
#ifndef _VIEWEQUIVALENTSCHEDULES_H_
#define _VIEWEQUIVALENTSCHEDULES_H_

bool isScheduleEquivalent (tSchedule *schedule); 
tCommand ** alocateMat(int lin,int col); 
void getAllCommands(tSchedule *schedules,tCommand *allCommands);
void buildPossibleSerialized(tSchedule *schedule);

#endif