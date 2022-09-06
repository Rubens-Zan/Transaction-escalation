#include "transaction.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* -------------------------------------------------------------------------- */

/**
 * @brief Function to load the schedule received from stdin
 * @param fp {FILE *} - File pointer to read the schedule
 * @return tSchedule* - Schedule received
 */
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
            schedule->transactionsQt++;
            curEscalation->transactions[curEscalation->transactionsQt] = (*createTransaction(schedule->transactionsQt));
            curEscalation->openedTransactions++;
            curEscalation->transactionsQt++;
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

/**
 * @brief Get the new command by reading new line
 * @param line {char *} - Line of the new command
 * @return tCommand* - Return the new command
 */
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
void freeSchedule(tSchedule *schedule)
{
    for (int i = 0; i < schedule->escalationsQt; i++)
    {
        for (int j = 0; j < schedule->escalations[i].transactionsQt; j++)
            free(&schedule->escalations[i].transactions[j]);
    }
}
/* -------------------------------------------------------------------------- */

/**
 * @brief Function to add the received command to the transaction indexed by commandId
 * @param transactions {tTransaction *} - Array with the all the transactions in the escalation
 * @param transactionsQt {int} - Transactions quantity in the escalation
 * @param command {tCommand *} - Command to be added to the transaction that it belongs
 */
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

/**
 * @brief Get if is there any next command by type searched and same atribute
 * @param commands {tCommand *} Commands array 
 * @param commandSearchedType {typesE} The command type searched
 * @param idx {int} Index of the current command 
 * @param commandsQt {int} Quantity of commands on the escalation
 * @return true 
 * @return false
 */
bool checkIfIsThereNextCommandByType(tCommand *commands, typesE commandSearchedType, int idx, int commandsQt)
{
    for (int i = 0; i < commandsQt; i++)
    {
        if (commands[i].transactionId != commands[idx].transactionId && commands[i].type == commandSearchedType && (strcmp(commands[i].atribute, commands[idx].atribute) == 0))
        {
            return false;
        }
    }
}