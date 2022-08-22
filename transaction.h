#ifndef _TRANSACTION_H_
#define _TRANSACTION_H_

#include <stdio.h>
#include <stdbool.h>

typedef enum {
    READ,
    WRITE,
    COMMIT
} typesE;

typedef struct tCommand {
    typesE type;
    char atribute[20]; 
    int transactionId; 
} tCommand;

typedef struct tTransaction {
    int id; 
    tCommand commands[50];
    int commandQt; 
} tTransaction;

typedef struct tSchedule {
    tTransaction transactions[50];
    int transactionQt;
} tSchedule;

void addCommand(tSchedule *schedule, tCommand *command);
tCommand * getCommand(char *line);
tTransaction *createTransaction(int id); 
tCommand *createCommand(char *commandType, char *atribute, int transactionId);
tSchedule *loadSchedule(FILE *fp); 
tTransaction *beginTransaction (int id);
bool isNewTransaction(tSchedule *schedule, int transactionId); 

#endif