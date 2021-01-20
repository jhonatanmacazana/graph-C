#include "graph.h"

#include <stdio.h>
#include <stdlib.h>

Graph* createGraph() {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->size  = 0;
    graph->head  = NULL;

    return graph;
}

Node* createNode(uint8_t val, uint8_t x, uint8_t y) {
    Node* newNode  = (Node*)malloc(sizeof(Node));
    newNode->val   = val;
    newNode->xpos  = x;
    newNode->ypos  = y;
    newNode->next  = NULL;
    newNode->edges = NULL;
    return newNode;
}

Edge* createEdge(Graph* graph, uint8_t src, uint8_t dest, uint8_t val) {
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->peso = val;
    newEdge->dest = getNode(graph, dest);
    newEdge->next = NULL;

    return newEdge;
}

bool insertNode(Graph* graph, uint8_t val, uint8_t x, uint8_t y) {
    if (getNode(graph, val) != NULL) return false;
    Node* newNode  = createNode(val, x, y);
    Node* tempNode = NULL;

    if (graph->head == NULL) {
        graph->head = newNode;
    } else {
        tempNode = graph->head;
        while (tempNode->next != NULL)
            tempNode = tempNode->next;
        tempNode->next = newNode;
    }
    graph->size++;
    return true;
}

bool insertEdge(Graph* graph, uint8_t src, uint8_t dest, uint8_t val) {
    Node* origNode = getNode(graph, src);
    Node* destNode = getNode(graph, dest);
    if (origNode == NULL || destNode == NULL) return false;

    Edge* newEdge  = createEdge(graph, src, dest, val);
    Edge* tempEdge = NULL;

    if (origNode->edges == NULL) {
        origNode->edges = newEdge;
    } else {
        tempEdge = origNode->edges;
        while (tempEdge->next != NULL) tempEdge = tempEdge->next;
        tempEdge->next = newEdge;
    }
    graph->FWweight[src][dest] = val;
    return true;
}

Node* getNode(Graph* graph, uint8_t val) {
    Node* tempNode = graph->head;
    while (tempNode != NULL) {
        if (tempNode->val == val) return tempNode;
        tempNode = tempNode->next;
    }
    return NULL;
}

bool printGraph(Graph* graph) {
    Node* tempNode = graph->head;
    Edge* tempEdge = NULL;

    while (tempNode != NULL) {
        printf("\nNodo %d: ", tempNode->val);
        tempEdge = tempNode->edges;
        while (tempEdge) {
            printf("[%2d -> %d]", tempEdge->peso, tempEdge->dest->val);
            tempEdge = tempEdge->next;
        }
        tempNode = tempNode->next;
    }
}

void createMatrix(Graph* graph) {
    graph->FWweight = (uint8_t**)malloc(graph->size * sizeof(uint8_t*));

    for (uint8_t i = 0; i < graph->size; i++) {
        graph->FWweight[i] = (uint8_t*)malloc(graph->size * sizeof(uint8_t));
        for (uint8_t j = 0; j < graph->size; j++) {
            if (i == j)
                graph->FWweight[i][j] = 0;
            else
                graph->FWweight[i][j] = INFINITY;
        }
    }

    graph->FWroutes = (uint8_t**)malloc(graph->size * sizeof(uint8_t*));
    for (uint8_t i = 0; i < graph->size; i++) {
        graph->FWroutes[i] = (uint8_t*)malloc(graph->size * sizeof(uint8_t));
        for (uint8_t j = 0; j < graph->size; j++) {
            if (i == j)
                graph->FWroutes[i][j] = 0;
            else
                graph->FWroutes[i][j] = j;
        }
    }
}

void printMatrix(Graph* graph) {
    uint8_t** matrix01 = graph->FWweight;
    uint8_t** matrix02 = graph->FWroutes;

    printf("-----------------------------\n");
    printf("------ Floyd Warshall -------\n");
    printf("-----------------------------\n");

    printf("------ Tabla de pesos -------\n");
    for (int i = 0; i < graph->size; i++) {
        for (int j = 0; j < graph->size; j++) {
            if (matrix01[i][j] == INFINITY)
                printf("INF ");
            else
                printf("%3d ", matrix01[i][j]);
        }
        printf("\n");
    }

    printf("------- Tabla de caminos-------\n");
    for (int i = 0; i < graph->size; i++) {
        for (int j = 0; j < graph->size; j++)
            printf("%3d ", matrix02[i][j]);
        printf("\n");
    }
}

bool FloydWarshall(Graph* graph) {
    uint8_t** fw01 = graph->FWweight;
    uint8_t** fw02 = graph->FWroutes;

    for (uint8_t i = 0; i < graph->size; i++) {
        for (uint8_t j = 0; j < graph->size; j++) {
            for (uint8_t k = 0; k < graph->size; k++) {
                if (fw01[j][i] == INFINITY || fw01[i][k] == INFINITY)
                    continue;
                else {
                    if (fw01[j][k] > (fw01[j][i] + fw01[i][k])) {
                        fw01[j][k] = fw01[j][i] + fw01[i][k];
                        fw02[j][k] = i;
                    }
                }
            }
        }
    }
    return true;
}

Graph** getPaths(Graph* graph) {
    Graph** GraphArray = createGraphArray(graph->size);

    for (uint8_t i = 0; i < graph->size; i++) {
        GraphArray[i] = createGraph();
        copyNodesGraph(graph, GraphArray[i]);
    }

    FloydWarshall(graph);

    return GraphArray;
}

bool copyNodesGraph(Graph* source, Graph* destination) {
    Node* tempNode = NULL;
    tempNode       = source->head;

    while (tempNode != NULL) {
        insertNode(destination,
                   tempNode->val,
                   tempNode->xpos,
                   tempNode->ypos);
        tempNode = tempNode->next;
    }
    return true;
}

Graph** createGraphArray(uint8_t size) {
    Graph** newArr = (Graph**)malloc(size * sizeof(Graph*));

    for (uint8_t i = 0; i < size; i++)
        newArr[i] = createGraph();
    return newArr;
}