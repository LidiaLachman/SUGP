#include "queue.h"

struct queue *createQueue(int numEdges) {               //tworzymy strukturę kolejki (dla bfs)
    struct queue *q = malloc(sizeof(struct queue));     //przydzielamy dla niej pamięć
    q->max = numEdges;                                  //zapisujemy ilość krawędzi
    q->items = (int *) malloc(numEdges * sizeof(int));  //przydzielamy pamięć dla przechowywania tych krawędzi
    q->front = -1;                                      //wskaźnik na pierwszy element kolejki
    q->last = -1;                                       //wskaźnik na ostatni element kolejki
    return q;                                           //zwracamy kolejkę
}

int isEmpty(struct queue *q) {                          //sprawdzenie czy kolejka jest pusta
    if (q->last == -1)                                  //jeżeli wskaźnik na ostatni element jest -1, to znaczy że kolejka jest pusta
        return 1;
    else
        return 0;
}

void enqueue(struct queue *q, int value) {              //dodajemy element do kolejki
    if (q->front == -1)                                 //jeżeli pierwszego elementu nie było, zerujemy
        q->front = 0;
    q->last++;                                          //zwiększamy indeks ostatniego elementu
    q->items[q->last] = value;                          //dodajemy element do kolejki

}

int dequeue(struct queue *q) {                         //usunięcie elementu z kolejki
    int item;                                          //zmienna, do której zapisujemy usuwany element
    if (isEmpty(q)) {                                  //jeżeli kolejka jest pusta, zwracamy -1
        item = -1;
    } else {
        item = q->items[q->front];                     //wyjmujemy pierwszy element z kolejki
        q->front++;                                    //zwiększamy wskaźnik na pierwszy element
        if (q->front > q->last) {                      //jeżeli cała kolejka stała sie pusta, zerujemy wskaźniki
            q->front = q->last = -1;
        }
    }
    return item;                                       //zwracamy usunięty element
}