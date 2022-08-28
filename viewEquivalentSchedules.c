#include "transaction.h"
#include "viewEquivalentSchedules.h"
#include <stdbool.h>
#include <stdlib.h>

bool isScheduleEquivalent(tSchedule *schedule)
{
    // tCommand **possibleSerialized = buildPossibleSerialized(schedule);
    // return false;
    return true;
}
// /* -------------------------------------------------------------------------- */

// tCommand **buildPossibleSerialized(tSchedule *schedule)
// {
//     int commandsQt = 0;
//     // tCommand **commandsArray = alocateMat(schedule->commandQt * schedule->commandQt, schedule->commandQt + 1);
//     // tCommand allCommands[schedule->commandQt + 100];

//     getAllCommands(schedule, allCommands);

//     tCommand curCombination[100];

//     for (int i = 0; i < commandsQt; i++)
//     {
//         for (int j = 0; j < commandsQt - 1; j++)
//         {
//             commandsArray[i][j] = allCommands[j + 1];
//             commandsArray[i][j + 1] = allCommands[j];
//         }
//     }

//     return commandsArray;
// }
// /* -------------------------------------------------------------------------- */

// tCommand **alocateMat(int lin, int col)
// {
//     tCommand **mat;
//     mat = malloc(lin * sizeof(tCommand *));
//     mat[0] = malloc(lin * col * sizeof(tCommand));

//     for (int i = 1; i < lin; i++)
//         mat[i] = mat[0] + i * col;

//     return mat;
// }
// /* -------------------------------------------------------------------------- */

// void freeArray(tCommand **array)
// {
//     free(array[0]);
//     free(array);
// }

// /* -------------------------------------------------------------------------- */

// void getAllCommands(tSchedule *schedules, tCommand *allCommands)
// {
//     int curCommand = 0;

//     for (int i = 0; i < schedules->transactionQt; i++)
//     {
//         for (int j = 0; j < schedules->transactions[i].commandQt; j++)
//         {
//             allCommands[curCommand] = schedules->transactions[i].commands[j];
//             curCommand++;
//         }
//     }
// }
// /* -------------------------------------------------------------------------- */
