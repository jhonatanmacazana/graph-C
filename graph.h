#ifndef GRAPH_H
#define GRAPH_H


#include <inttypes.h>
#include <stdbool.h>

#define Node struct node
#define Edge struct edge
#define Graph struct graph
#define List struct pila


Node{
    uint8_t val;
    uint8_t xpos;
    uint8_t ypos;
    Node* next;
    Edge* edges;
};

Edge{
    uint8_t peso;
    Node* dest;
    Edge* next;
};

Graph
{
    Node* head;
    uint8_t size;
    uint8_t **FWweight;
    uint8_t **FWroutes;
};

List{
    Node* data;
    List* siguiente;
};


#define INFINITY 255

/* Prototypes */


Graph* createGraph();

Node* createNode(uint8_t val, uint8_t x, uint8_t y);

Edge* createEdge(Graph* graph, uint8_t src, uint8_t dest, uint8_t val);

Node* getNode(Graph* graph, uint8_t val);

bool insertNode(Graph* graph, uint8_t val, uint8_t x, uint8_t y);

bool insertEdge(Graph* graph, uint8_t src, uint8_t dest, uint8_t val);

bool printGraph(Graph* graph);

void createMatrix(Graph *graph);
void printMatrix(Graph *graph);

bool copyNodesGraph(Graph* source, Graph* destination);
bool FloydWarshall(Graph *graph);
Graph** getPaths(Graph *graph);
Graph** createGraphArray(uint8_t size);


#endif //GRAPH_H
