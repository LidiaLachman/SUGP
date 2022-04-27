#include <stdio.h>
#include <locale.h>
#include "buffer.h"

double getValue(char *arg) {         //fukcja przekształcająca ciąg znaków w liczbę
    char *p;                         //zmienna pomocnicza służąca do pobierania znaków
    double value = strtod(arg, &p);  //przekształcamy ciąg znaków w liczbę za pomocą funkcji string to double
    if (*p != '\0') {                //jeśli został pobrany jakiś inny znak niż cyfra to wyświetlamy komunikat o błędzie
        printf("Invalid program input arguments. Expected only numbers and dots, but founded - %s\n", arg);
        exit(-1); 
    }
    return value;                   
}

void print_help()
{
    printf("SUGP program - The Shortest Undirected Graph Path\n\n");
    printf("Input arguments:\n");
    printf("- (int columns,int rows), example execution: ./out 4 6\n");
    printf("columns - number of columns \n");
    printf("rows - number of rows\n\n");
    printf("- (int columns, int rows, int double minValue, double maxValue), example execution: ./out 4 6 0 3\n");
    printf("columns - number of columns \n");
    printf("rows - number of rows\n");
    printf("minValue - graph weight lower boundary\n");
    printf("maxValue - graph weight upper boundary\n\n");
    printf("- (char *file_name, int startVertex, int destinationVertex), example execution: ./out graph.txt 4 20\n");
    printf("file_name - name of file containing graph\n");
    printf("startVertex - graph starting vertex\n");
    printf("destinationVertex - graph destination vertex\n");
}

int main(int argc, char **argv) {         
    //if (argc > 5 || argc < 3) {           //jeżeli liczba argumentów jest różna od 2,3 lub 4 - program kończy działanie i wyświetla komunikat o błędzie
    //    printf("Invalid program input arguments. Expected 2,3 or 4 arguments, but found %d arguments.\n", argc - 1);
    //    return -1;
    //}
    if (argc == 3 || argc == 5) {               //jeśli wprowadzono 2 lub 4 argumenty, to generujemy graf
        int columns = getValue(argv[1]);        //odczytujemy liczbę kolumn
        int rows = getValue(argv[2]);           //odczytujemy liczbę wierszy
        double minValue = 0, maxValue = 1;      //ustawienie domyślnych wartości przedziału - <0,1>
        if (argc == 5) {                        //jeżeli wprowadzono 4 argumenty, to odczytujemy przedział podany przez użytkownika
            minValue = getValue(argv[3]);
            maxValue = getValue(argv[4]);
        }
        struct Graph *graph = generateGraph(rows, columns, minValue, maxValue);    //generujemy graf
        saveGraphToFile(graph);                                                    //zapisujemy graf do pliku
        printf("Input start and destinition vertices: ");      
        int startVertex, destinationVertex;      
        scanf("%d %d", &startVertex, &destinationVertex);       //odczytujemy w. początkowy i w.końcowy do wyznaczenia najkrótszej ścieżki
        double dist = findDistanseBetweenVertices(graph, startVertex, destinationVertex);     //wyznaczamy odległość między tymi wierczhołkami
        printf("The shortest path between vertices %d and %d is %lf\n", startVertex, destinationVertex, dist); 
        free(graph);                                                                         //zwalniamy pamięć przeznaczoną na graf
    }
    else if (argc == 4) {                             //jeżeli wprowadzono 3 argumenty, to odczytujemy graf z pliku i dwa wierzchołki
        FILE *file = fopen(argv[1], "r");        
        if (file == NULL) {                      //jeżeli plik nie otworzył się, to wyświetlamy błąd
            printf("Cannot open file\n");
            return -1;
        }
        int startVertex = getValue(argv[2]);                  //odczytujemy wierzchołek startowy 
        int destinationVertex = getValue(argv[3]);            //odczytujemy wierzchołek końcowy
        struct Graph *graph = readGraphFromFile(file);        //odczytujemy graf z pliku
        double dist = findDistanseBetweenVertices(graph, startVertex, destinationVertex);    //wyznaczamy odległość między dwoma wierzchołkami
        printf("The shortest path between vertices %d and %d is %lf\n", startVertex, destinationVertex, dist);        
        free(graph);                               
    }
    else
    {
        print_help();
    }

    return 0;
}