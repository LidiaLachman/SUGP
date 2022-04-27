#include "stdio.h"
#include <time.h>
#include "node.h"
#include "queue.h"

struct Graph {                         //struktura przechowująca graf
    int numVertices;                   //liczba wierczołków
    int *visited;                      //tablica odwiedzonych wierzchołków
    int numEdges;                      //liczba krawędzi
    int rows;                          //liczba wierszy
    int columns;                       //liczba kolumn
    struct Node **adjLists;            //lista sąsiedctwa
};

struct Graph *createGraph(int vertices, int edges, int rows, int columns);

void addEdge(struct Graph *graph, int src, int dest, double weight);

int conectivityCheck(struct Graph *graph);

void bfs(struct Graph *graph, int startVertex);

struct Graph* generateGraph(int rows, int columns, double minValue, double maxValue);

double generateWeight(double minValue, double maxValue);

double dijkstra(struct Graph *graph, int start, int finish);

double findDistanseBetweenVertices(struct Graph *graph, int startVertex, int destinationVertex);

