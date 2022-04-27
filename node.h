#include "stdlib.h"

struct Node { //struktura do przechowywania elementu grafu
    int vertex; //wierzchołęk
    struct Node *next; // wskaźnik na nastepny wierzchołek
    double weight;//waga krawędzi
};

struct Node *createNode(int v, double weight);

