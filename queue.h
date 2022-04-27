#include <stdlib.h>

struct queue { //struktura kolejki
    int *items; //tablica z elementami kolejki
    int max;  //ilość krawędzi
    int front; //wskażnik na pierwszy element
    int last; //wskażnik na ostatni element
};

struct queue *createQueue(int numEdges);

int isEmpty(struct queue *q);

void enqueue(struct queue *q, int value);

int dequeue(struct queue *q);

