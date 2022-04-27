#include "node.h"

struct Node *createNode(int v, double weight) { //tworzymy element, jednostkę grafu
    struct Node *newNode = malloc(sizeof(struct Node)); // tworzymy jednostkę, przedzielamy dla niej pamięć
    newNode->vertex = v; // ta jednostka przechowuje w sobie wierzchołek v
    newNode->next = NULL; //wskażnik na następny wierczhołek, na razie zerujemy
    newNode->weight = weight; //waga
    return newNode;
}

