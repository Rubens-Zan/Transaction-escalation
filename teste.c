#include <stdio.h>
#include <stdlib.h>
#include "transaction.h"
#include "viewEquivalentSchedules.h"

void loopThroughSchedule(tSchedule *schedule){
    for (int i=0;i < schedule->escalationsQt;i++){
        escalationT *curEscalation = &schedule->escalations[i];
        printf("%d ",i);
        for (int j=0;j < curEscalation->transactionsQt-1;j++){
            printf("%d,",curEscalation->transactions[j].id);
        }
        printf("%d \n",curEscalation->transactions[curEscalation->transactionsQt-1].id);
    }
}

int main(int argc, char **argv)
{
    tSchedule *mySchedule = loadSchedule(stdin); 

    loopThroughSchedule(mySchedule); 

    // if (isScheduleEquivalent(mySchedule)){
    //     printf("sim");
    // }

    return 0;
};