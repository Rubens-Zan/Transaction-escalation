#include <stdio.h>
#include <stdlib.h>
#include "transaction.h"
#include "viewEquivalentSchedules.h"


int main(int argc, char **argv)
{
    tSchedule *mySchedule = loadSchedule(stdin); 

    if (isScheduleEquivalent(mySchedule)){
        printf("sim");
    }

    return 0;
};