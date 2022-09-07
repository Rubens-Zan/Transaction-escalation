/** @file graphlib.c
 * @author Julio L. Martins & Rubens Zandomenighi
 * @brief Implementação das funções de manipulação de grafos
 * @version 1.0
 * @date 2022-09-6
 */

#include <stlib.h>
#include <string.h>
#include "graphlib.h"

/**
 * @brief adiciona uma aresta conforme as dependências entre as transações
 * @param graph {Graph *} - um grafo
 * @param schedule {TSchedule *} - um agendamento
 */
static void addDependencyEdge(Graph *graph, TSchedule *schedule) {
    long i, j, k, id;
    TTransaction scheduleTransaction;

    for (k = 1, i = 0; i < schedule->transactionListSize; i++) {
        scheduleTransaction = schedule->transactionList[i];
        id = resolveId(scheduleTransaction.id);

        if (graph->vertexList[id].adjacentList == NULL) {
            graph->vertexList[id].adjacentList = (TVertex *) malloc(sizeof(TVertex) * DEFAULT_SIZE * k++);
        }

        for (j = i + 1; j < schedule->transactionListSize; j++) {
            if ((scheduleTransaction.id != schedule->transactionList[j].id) &&
                (strcmp(scheduleTransaction.atribute, schedule->transactionList[j].atribute) == 0)) {

                if ((scheduleTransaction.operation == WRITE) &&
                    (schedule->transactionList[j].operation == READ)) {
                    graph->vertexList[id].adjacentList[graph->vertexList[id].adjacentListSize++] =
                            &graph->vertexList[resolveId(schedule->transactionList[j].id)];
                }

                if ((scheduleTransaction.operation == READ) &&
                    (schedule->transactionList[j].operation == WRITE)) {
                    graph->vertexList[id].adjacentList[graph->vertexList[id].adjacentListSize++] =
                            &graph->vertexList[resolveId(schedule->transactionList[j].id)];
                }

                if ((scheduleTransaction.operation == WRITE) &&
                    (schedule->transactionList[j].operation == WRITE)) {
                    graph->vertexList[id].adjacentList[graph->vertexList[id].adjacentListSize++] =
                            &graph->vertexList[resolveId(schedule->transactionList[j].id)];
                }
            }
            if (graph->vertexList[id].adjacentListSize == DEFAULT_SIZE) {
                graph->vertexList[id].adjacentList = (TVertex *) realloc(graph->vertexList[id].adjacentList,
                                                                        sizeof(TVertex) * DEFAULT_SIZE * k++);
            }
        }
    }
}

/**
 * @brief Cria um grafo a partir de um agendamento de transações
 *
 * @param graph {TGraph *} - um grafo
 * @param schedule {TSchedule *} - um agendamento
 */
void createGraph(Graph *graph, TSchedule *schedule) {
    long i, j;
    graph->vertexListSize = schedule->transactionQty;
    graph->vertexList = (TVertex *) malloc(sizeof(TVertex) * graph->vertexListSize);

    for (i = 0; i < graph->vertexListSize; i++) {
        graph->vertexList[i].id = i+1;
        graph->vertexList[i].state = GREEN;
        graph->vertexList[i].adjacentList = NULL;
        graph->vertexList[i].adjacentListSize = 0;
        graph->vertexList[i].transaction = NULL;
    }
    addDependencyEdge(graph, schedule);
}

/**
 * @brief percorre o grafo assinalando os vértices visitados
 * @param vertex {TVertex} - um vértice
 * @param vertexId  {long} - o id do vértice
 */
static void visit(TVertex *vertex, long vertexId) {
    long i;

    if (vertex[vertexId].state == RED) {
        return;
    }
    if (vertex[vertexId].state == GREEN) {
        vertex[vertexId].state = YELLOW;
        for (i = 0; i < vertex[vertexId].adjacentListSize; i++) {
            if (vertex[vertexId].adjacentList[i].state == GREEN) {
                visit(vertex, vertex[vertexId].adjacentList[i]->id);
            }
        }
        vertex[vertexId].state = RED;
    }
}

bool isDirectedAcyclicGraph(Graph *graph) {
    long countAnyYellow, vertexId;

    for (vertexId = 0, countAnyYellow = 0; vertexId < graph->vertexListSize; vertexId++) {
        visit(graph->vertexList, vertexId);
        if (graph->vertexList[vertexId].state == YELLOW) {
            countAnyYellow++;
        }
    }

    if (countAnyYellow > 0) {
        return true;
    }
    return false;
}