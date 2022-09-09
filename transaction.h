#ifndef _TRANSACTION_H_
#define _TRANSACTION_H_

#include <stdio.h>
#include <stdbool.h>

typedef enum {
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

/**
 * @struct TTransaction
 * @brief Struct to represent a transaction
 * @field id {int} Transaction id
 * @field operation {typesE *} Array of commands
 * @field attributes {char *} Array of attributes
 */
typedef struct transaction{
    long id;
    typesE operation;
    char attribute[20];
}TTransaction;

typedef struct tTransaction
{
    int id;
    tCommand commands[50];
    int commandsQt;
    bool isOpened;
} tTransaction;

/**
 * @struct TSchedule
 * @brief Stores all transactions read
 * @field transactionList {tTransaction *} list of transactions
 * @field transactionsListSize {long} quantity of transactions
 * @field transactionQty {int} quantity of unique transactions ids
 */
typedef struct schedule {
    TTransaction *transactionList;
    long transactionListSize;
    long transactionQty;
} TSchedule;

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
/**
 * @brief map the struct tSchedule to TSchedule
 * @param currSchedule {escalationT} current schedule
 * @param newSchedule {TSchedule *} new schedule
 * @return {TSchedule} a new schedule type
 */
void mapTo(escalationT currSchedule, TSchedule *newSchedule);

tSchedule *getConcurrentTransactions(tSchedule *mySchedule);
tCommand *createCommand(char *commandType, char *atribute, int transactionId, int time);
void addCommand(tTransaction *transactions, int transactionsQt, tCommand *command);
tCommand *getCommand(char *line);
tTransaction *createTransaction(int id);
tSchedule *loadSchedule(FILE *fp);
tTransaction *beginTransaction(int id);
bool isNewTransaction(tSchedule *schedule, int transactionId);
bool checkIfIsThereNextCommandByType(tCommand *commands, typesE commandSearchedType, int idx, int commandsQt);

#endif