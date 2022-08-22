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
    tSchedule *schedule = malloc(sizeof(tSchedule));
    
    schedule->transactionQt = 0;
    while ((read = getline(&line, &len, fp)) != -1)
    {
        command = getCommand(line);
        if (isNewTransaction(schedule, command->transactionId)){
            schedule->transactions[schedule->transactionQt] = (*createTransaction(command->transactionId)); 
            schedule->transactionQt++;
        }

       addCommand(schedule, command); 
    }

    fclose(fp);
}
/* -------------------------------------------------------------------------- */
bool isNewTransaction(tSchedule *schedule, int transactionId){   
    for (int i = 0; i < schedule->transactionQt; i++){
        if (schedule->transactions[i].id == transactionId){
            return false;
        }
    }

    return true;
}

/* -------------------------------------------------------------------------- */
tCommand *getCommand(char *line)
{
    line[strlen(line) - 1] = '\0';
    char delim[] = " ";
    static char commandType[20];
    static char atribute[20];
    static char time[20];
    int transactionId;

    strcpy(time, strtok(line, delim));
    transactionId = atoi(strtok(NULL, delim));
    strcpy(commandType, strtok(NULL, delim));
    strcpy(atribute, strtok(NULL, delim));

    time[strlen(time)] = '\0';
    commandType[strlen(commandType)] = '\0';
    atribute[strlen(atribute)] = '\0';

    return createCommand(commandType, atribute, transactionId);
}

/* -------------------------------------------------------------------------- */

tCommand *createCommand(char *commandType, char *atribute, int transactionId)
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
    return command;
}

/* -------------------------------------------------------------------------- */
tTransaction *createTransaction(int id)
{
    tTransaction *transaction = malloc(sizeof(tTransaction));
    transaction->id = id;

    return transaction;
}

/* -------------------------------------------------------------------------- */
void addCommand(tSchedule *schedule, tCommand *command){
    for (int i = 0; i < schedule->transactionQt; i++){
        if (schedule->transactions[i].id == command->transactionId){
            schedule->transactions[i].commands[schedule->transactions[i].commandQt]= (*command);
            schedule->transactions[i].commandQt++;
            break;
        }
        
    }
}
/* -------------------------------------------------------------------------- */
