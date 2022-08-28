#ifndef _TRANSACTION_H_
#define _TRANSACTION_H_

#include <stdio.h>
#include <stdbool.h>

typedef enum
{
    READ,
    WRITE,
    COMMIT
} typesE;

typedef struct tCommand
{
    typesE type;
    char atribute[20];
    int transactionId;
    int time;
} tCommand;

typedef struct tTransaction
{
    int id;
    tCommand commands[50];
    int commandsQt;
    bool isOpened;
} tTransaction;

typedef struct escalationT
{
    tTransaction transactions[50];
    int openedTransactions;
    int transactionsQt;
} escalationT;

typedef struct tSchedule
{
    escalationT escalations[50];
    int escalationsQt;
    int transactionsQt;

} tSchedule;

tSchedule *createSchedule();
tSchedule *getConcurrentTransactions(tSchedule *mySchedule);
tCommand *createCommand(char *commandType, char *atribute, int transactionId, int time);
void addCommand(tTransaction *transactions, int transactionsQt, tCommand *command);
tCommand *getCommand(char *line);
tTransaction *createTransaction(int id);
tSchedule *loadSchedule(FILE *fp);
tTransaction *beginTransaction(int id);
bool isNewTransaction(tSchedule *schedule, int transactionId);

#endif