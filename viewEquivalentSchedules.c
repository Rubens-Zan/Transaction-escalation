#include "transaction.h"
#include "auxiliar.h"
#include "viewEquivalentSchedules.h"
#include <stdbool.h>
#include <stdlib.h>

bool isScheduleEquivalent(escalationT *escalation)
{
    int commandsQt = getCommandQt(escalation); 

    tCommand *allCommands =malloc(sizeof(tCommand)* commandsQt);
    getAllCommands(escalation,allCommands);
    tCommand **allPermutations = alocateMat(fact(commandsQt)+1, commandsQt+1);
    int idx =0;
    permute(allCommands,0,commandsQt-1,allPermutations, &idx);

    printAllPermutations(allPermutations,fact(commandsQt), commandsQt);
    // printf("[%d,%d]",commandsQt, fact(commandsQt)); 
    // printAllPermutations(allPermutations,fact(commandsQt), commandsQt); 
    // return false;
    return true;
}

int getCommandQt (escalationT *escalation){
    int commandsQt = 0;
    
    for (int i = 0;i< escalation->transactionsQt;i++){
        // printf("i tem %d %d\n",i, escalation->transactions[i].commandsQt);
        commandsQt+=escalation->transactions[i].commandsQt; 
    }
    return commandsQt; 
}
/* -------------------------------------------------------------------------- */

void freeArray(tCommand **array)
{
    free(array[0]);
    free(array);
}

/* -------------------------------------------------------------------------- */

void getAllCommands(escalationT *escalation, tCommand *allCommands)
{
    int curCommand = 0;

    for (int i = 0; i < escalation->transactionsQt; i++)
    {
        for (int j = 0; j < escalation->transactions[i].commandsQt; j++)
        {
            allCommands[curCommand] = escalation->transactions[i].commands[j];
            curCommand++;
        }
    }
}
/* -------------------------------------------------------------------------- */
