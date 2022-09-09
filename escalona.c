#include <stdio.h>
#include <stdlib.h>
#include "transaction.h"
#include "viewEquivalentSchedules.h"
#include "graphlib.h"

/**
 * @brief Function to loop through schedule, print the escalations and print if is view equivalent and if is serializable
 * @param schedule {tSchedule *} - Schedule received
 */
void loopThroughSchedule(tSchedule *schedule){
    Graph graph[schedule->escalationsQt];
    TSchedule graphSchedule;

    for (int i=0;i < schedule->escalationsQt;i++){
        escalationT *curEscalation = &schedule->escalations[i];

        mapTo(schedule->escalations[i],&graphSchedule);

        createGraph(&graph[i], &graphSchedule);

        printf("%d ",i+1);
        for (int j=0;j < curEscalation->transactionsQt-1;j++){
            printf("%d,",curEscalation->transactions[j].id+1);
        }
        printf("%d ",curEscalation->transactions[curEscalation->transactionsQt-1].id + 1);

        if (!isDirectedAcyclicGraph(&graph[i])){
            printf("SS\n");
        }else{
            printf("SN\n");
        }
    }

    for (int i=0;i < schedule->escalationsQt;i++){
        escalationT *curEscalation = &schedule->escalations[i];
        printf("%d ",i+1);
        for (int j=0;j < curEscalation->transactionsQt-1;j++){
            printf("%d,",curEscalation->transactions[j].id+1);   
        }
        printf("%d ",curEscalation->transactions[curEscalation->transactionsQt-1].id + 1);

        if (isScheduleEquivalent(curEscalation)){
            printf("SV\n");
        }else{
            printf("NV\n");
        }
    }
}

int main(int argc, char **argv)
{
    tSchedule *mySchedule = loadSchedule(stdin); 

    loopThroughSchedule(mySchedule); 

    free(mySchedule); 
    return 0;
};