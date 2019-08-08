#include <stdio.h>

#include "graph.h"

int main() {
    printf("Hello, World!\n");
/*
    Graph* G1 = createGraph();
    insertNode(G1, 0, 0, 0);
    insertNode(G1, 1, 0, 0);
    insertNode(G1, 2, 0, 0);
    insertNode(G1, 3, 0, 0);


    createMatrix(G1);

    insertEdge(G1, 0, 1, 10);
    insertEdge(G1, 1, 2, 8);
    insertEdge(G1, 1, 3, 3);
    insertEdge(G1, 3, 2, 4);

    printMatrix(G1);
    printf("\n");
    FloydWarshall(G1);

    printGraph(G1);
    printf("\n");
*/

    /*********************************************/
    Graph *G2 = createGraph();
    insertNode(G2, 0, 0, 0);
    insertNode(G2, 1, 0, 0);
    insertNode(G2, 2, 0, 0);
    insertNode(G2, 3, 0, 0);
    insertNode(G2, 4, 0, 0);


    createMatrix(G2);

    insertEdge(G2, 0, 2, 6);
    insertEdge(G2, 0, 3, 3);
    insertEdge(G2, 1, 0, 3);
    insertEdge(G2, 2, 3, 2);
    insertEdge(G2, 3, 1, 1);
    insertEdge(G2, 3, 2, 1);
    insertEdge(G2, 4, 1, 4);
    insertEdge(G2, 4, 3, 2);

    printMatrix(G2); printf("\n");
    getPaths(G2);
    printMatrix(G2); printf("\n");




    return 0;
}