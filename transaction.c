#include "transaction.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* -------------------------------------------------------------------------- */

tSchedule *loadSchedule(FILE *fp)
{
    char *line = NULL;
    size_t len = 0;
    size_t read;
    tCommand *command = NULL;
    tSchedule *schedule = createSchedule();

    while ((read = getline(&line, &len, fp)) != -1)
    {
        escalationT *curEscalation = &schedule->escalations[schedule->escalationsQt];

        command = getCommand(line);
        
        if (isNewTransaction(schedule, command->transactionId))
        {
            curEscalation->transactions[curEscalation->transactionsQt] = (*createTransaction(schedule->transactionsQt));
            curEscalation->openedTransactions++;
            curEscalation->transactionsQt++;
            schedule->transactionsQt++;
        }

        if (command->type == COMMIT)
        {
            curEscalation->openedTransactions--;

            if (curEscalation->openedTransactions == 0)
            {
                schedule->escalationsQt++;
            }
        }

        addCommand(curEscalation->transactions, curEscalation->transactionsQt, command);
        free(command);
    }

    fclose(fp);

    return schedule;
}

/* -------------------------------------------------------------------------- */

escalationT *createNewEscalation()
{
    escalationT *newEscalation = malloc(sizeof(escalationT));

    newEscalation->openedTransactions = 0;
    return newEscalation;
}

/* -------------------------------------------------------------------------- */

bool isNewTransaction(tSchedule *schedule, int transactionId)
{
    return (transactionId > schedule->transactionsQt); 
}

/* -------------------------------------------------------------------------- */

tCommand *getCommand(char *line)
{
    line[strlen(line) - 1] = '\0';
    char delim[] = " ";
    static char commandType[20];
    static char atribute[20];
    int time;
    int transactionId;

    time = atoi(strtok(line, delim));
    transactionId = atoi(strtok(NULL, delim));
    strcpy(commandType, strtok(NULL, delim));
    strcpy(atribute, strtok(NULL, delim));

    commandType[strlen(commandType)] = '\0';
    atribute[strlen(atribute)] = '\0';

    return createCommand(commandType, atribute, transactionId, time);
}

/* -------------------------------------------------------------------------- */

tCommand *createCommand(char *commandType, char *atribute, int transactionId, int time)
{
    tCommand *command = malloc(sizeof(tCommand));

    strcpy(command->atribute, atribute);
    command->transactionId = transactionId;
    switch ((*commandType))
    {
    case 'R':
        command->type = READ;
        break;
    case 'W':
        command->type = WRITE;
        break;
    case 'C':
        command->type = COMMIT;
        break;
    default:
        break;
    }
    command->time = time;
    return command;
}

/* -------------------------------------------------------------------------- */

tSchedule *createSchedule()
{
    tSchedule *schedule = malloc(sizeof(tSchedule));
    schedule->escalationsQt = 0;
    schedule->transactionsQt = 0;
    return schedule;
}

/* -------------------------------------------------------------------------- */

tTransaction *createTransaction(int id)
{
    tTransaction *transaction = malloc(sizeof(tTransaction));
    transaction->id = id;
    transaction->commandsQt = 0;

    return transaction;
}

/* -------------------------------------------------------------------------- */

void addCommand(tTransaction *transactions, int transactionsQt, tCommand *command)
{
    for (int i = 0; i < transactionsQt; i++)
    {
        if (transactions[i].id == command->transactionId)
        {
            transactions[i].commands[transactions[i].commandsQt] = (*command);
            transactions[i].commandsQt++;
            break;
        }
    }
}

/* -------------------------------------------------------------------------- */
