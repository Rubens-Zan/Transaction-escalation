#include "transaction.h"
#ifndef _VIEWEQUIVALENTSCHEDULES_H_
#define _VIEWEQUIVALENTSCHEDULES_H_

bool isScheduleEquivalent(escalationT *escalation);
void getAllCommands(escalationT *escalation, tCommand *allCommands);
tCommand **buildPossibleSerialized(escalationT *escalation);
int getCommandQt (escalationT *escalation); 

#endif