#include "buffer.h"

void saveGraphToFile(struct Graph *graph) {                   //funcjka zapisująca graf do pliku
    FILE *file = fopen("graph.txt", "w"); 
    fprintf(file, "%d %d\n", graph->columns, graph->rows);    //zapisujemy do niego ilośc kolumn i wierszy
    for (int v = 0; v < graph->numVertices; v++) {            //dla wszystkich wierzchołków grafu
        struct Node *temp = graph->adjLists[v];               //tworzymy element przechowujący pierwszy wierzchołek, do którego można przejść z wierzchołku v
        while (temp) {                                        // dopóki ten element nie jest NULL
            fprintf(file, "%d :%lf ", temp->vertex, temp->weight);     //zapisujemy ten wierczhołek i wagę z separatorem ;
            temp = temp->next;                                        //przechodzimy do kolejnego wierzchołka
        }
        fprintf(file, "\n"); 
    }
    fclose(file); 
}

struct Graph *readGraphFromFile(FILE *file) {                //funkcja odczytująca graf z pliku
    fseek(file, 0, SEEK_END);                                //pobieramy rozmiar pliku
    int size = ftell(file);                                  //zapisujemy go w zmienną size
    fseek(file, 0, SEEK_SET);                                //wracamy na początek pliku

    char *s = (char *) malloc(size * sizeof(char));          //tworzymy ciąg znaków, do którego będziemy po wierszach wpisywać dane z pliku 
    int rows = -1, columns = -1, val = -1;                   // tworzymy zmienne, przechowujące liczbę wierszy i kolumn oraz zmienną, gdzie będziemy zapisywać bieżące wartości
    fgets(s, size - 1, file);                                //odczytujemy pierwszy wiersz z pliku, w którym powinny być zawarte wartości reprezentujące liczbę wierszy i kolumn 
    for (int i = 0; s[i] != '\n' && s[i] != '\0'; i++) {     //sprawdzamy cały ten wiersz
        if (s[i] != ' ' && (s[i] < '0' || s[i] > '9')) {     //jeżeli wystepuję symbol, który nie jest spacją albo cyfrą, to wyświetlamy komunikat z błędem
            printf("Wrong data format in file");
            exit(-1);
        }
        if (s[i] == ' ') {                                  //jeżeli napotkamy spację
            if (columns == -1) {                            //jeżeli jeszcze nie zostały przypisane warości do kolumn (pierwsza wartość z pliku)
                columns = val;                              //to przypisujemy ze zmiennej val
                val = -1;                                   //zerujemy val 
            } else {                                        //jeżeli trafią się zbędne spacje wyświetlamy komunikat z błędem
                printf("Wrong data format in file");
                exit(-1);
            }
        } else {                                            //jeżeli napotkany symbol nie jest spacją
            if (val == -1) {                                //jeżeli to jest pierwsza cyfra to zapisujemy ją do zmiennej val
                val = (int) s[i] - (int) ('0');             //przepisujemy 
            } else {                                        //w przeciwnym razie zwiękaszamy tę wartość dziesięciokrotnie i przepisujemy nową liczbą. 
                                                            //Np. była wartość 1 a napotkalismy jeszcze 5, wtedy nowa liczba wynosi 1 * 10 = 10 + 5 = 15
                val = val * 10 + (int) s[i] - (int) ('0');  //nowa liczba
            }
        }
    }
    rows = val;                                                       //liczba wierszy równa się val
    if (rows < 0 || rows > 10000 || columns < 0 || columns > 10000) { //jeżeli liczba kolumn lub wierszy nie spełnia wymagań lub częśc danych nie została podana - wyświetlamy komunikat z błedem
        printf("Wrong data format in file");
        exit(-1);
    }

    int numVertices = rows * columns;                                            //odczytujemy liczbę węzłów
    int numEdges = (4 * rows * columns) - rows - columns;                        //odczytujemy liczbę krawędzi
    struct Graph *graph = createGraph(numVertices, numEdges, rows, columns);     // tworzymy graf o zadanych parametrach
    int from = 0;                                                                //tworzymy wierzchołek przechowujące bieżącą pozycję(wiersz), nr wiersza jest nr wierzchołka, z którego wychodzi krawędź
    int div = 1, isDot = 0, isColon = 0;                                         //zmienna div, isDot i isColon - flagi wskazujące czy spotkaliśmy . lub : , 0 - nie  , 1 - tak.
    val = -1;                                                                   
    while (fgets(s, size - 1, file) != NULL) {                                   //dopóki możemy odczytać dane z pliku
        int to = -1;                                                             //zmienna odpowiadająca wierzczhołkowi końcowemu krawędzi
        double weight = -1; //waga krawędzi
        for (int i = 0; s[i] != '\n' && s[i] != '\0'; i++) {                     //dla całego odczytanego wiersza
            if (s[i] != ' ' && s[i] != ':' && (s[i] > '9' || s[i] < '0') && s[i] != '.') {               //jeżeli aktualnie sprawdzany element nie jest cyfrą, kropką, spacją lub dwukropkiem wyświetlamy komunikat o blędzie
                printf("Wrong data format in file");
                exit(-1);
            }
            if (s[i] == ':') {                                                    //jeżeli aktualnie sprawdzany element jest dwukropkiem
                if (isColon == 1) {                                               // jeżeli już napotkaliśmy : ale po nim nie ma spacji, to wyświetlamy komunikat o blędzie
                    printf("Wrong data format in file");
                    exit(-1);
                } else {                                                          //jeżeli nie, to zapamiętujemy że napotkaliśmy :
                    isColon = 1;
                    continue;
                }
            }
            if (s[i] == '.') {                                                   //jeżeli aktualnie sprawdzany element jest .
                if (isDot == 1) {                                                //jeżeli już napotkaliśmy . ale po niej nie ma spacji, to wyświetlamy komunikat o blędzie
                    printf("Wrong data format in file");
                    exit(-1);
                } else {                                                         //jeżeli nie, to zapamiętujemy że napotkaliśmy .
                    isDot = 1;
                    continue;
                }
            }
            if (s[i] == ' ') {                                                  //jeżeli aktualnie sprawdzany element jest spacją
                if (val == -1) continue;                                        //jeżeli jescze nie napotkaliśmy cyfrę i to jest zbędna spacja to ją omijamy
                if (isColon == 1 && to == -1) {                                 // jeżeli już napotkalismy : ale nadal nie wczytano numer wierzchołku to wyswietlamy komunikat o błędzie
                    printf("Wrong data format in file");
                    exit(-1);
                }
                if (isColon == 0) {                                            //jeżeli nie napotkaliśmy : , to znaczt, że teraz oczytaliśmy numer wierzchołka końcowego krawędzi
                    to = val;                                                  //przypisujemy wartośc
                    val = -1; 
                } else {                                                       //jeżeli napotkaliśmy już :, to znaczy że teraz oczytujemy wagę krawędzi
                    isDot = 0;                                                 //zapominamy że napotkaliśmy .
                    weight = (double) val / (double) div;                      //przypisujemy wagę krawędzi
                    div = 1;                                                   //zerujemy dzielnik
                    val = -1;                                                 
                }
                if (to != -1 && weight != -1) {                                // jeżeli już odczytaliśmy numer wierczhołka końcowego krawędzi i jej wagę to dodajemy ją do grafu
                    if (to < 0 || to > rows * columns - 1 || weight < 0 || weight > 10000) { //sprawdzamy czy dane są poprawne, jeżeli nie to wyświetlamy komunikat o błędzie
                        printf("Wrong data format in file");
                        exit(-1);
                    }
                    addEdge(graph, from, to, weight); //dodajemy krawędź
                    to = -1;                          //inicjalizujemy wszystkie wykorzystane zmnienne tymczasowe
                    weight = -1;
                    isColon = 0;
                    isDot = 0;
                    val = -1;
                }
                continue;
            }                                        //jeżeli symbol nie jest spacją, : lub . , to musi być cyfrą
            if (isDot) div *= 10;                    // jeżeli napotkaliśmy ., to zwiększamy dzielnik dziesięciokrotnie
            if (val == -1) {                         // jeżeli to jest pierwsza napotkana cyfra , to przypisujemy ją do zmiennej
                val = (int) s[i] - (int) ('0');      //przypisujemy 
            } else {                                 //inaczej zwiększamy dziesieciokrotnie i dopisujemy tę cyfrę
                val = val * 10 + (int) s[i] - (int) ('0');
            }
        }
        if (val != -1) {                          //jeżeli po odczytaniu wiersza zostały danne(tam bedzie waga krawedzi)
            if (isColon == 1 && to != -1) {       //jeżeli napotkaliśmy :, ale nie znaleziono numeru wierzchołka  to wyświetlamy kominukat o błędzie
                printf("Wrong data format in file");
                exit(-1);
            }
            if (isColon == 1) {                          //jeżeli napotkaliśmy :
                to = val;                                //przypisujemy numer wierzchołka
            } else { 
                weight = (double) val / (double) div;    //inaczej przypisujemy wagę krawędzi
            }
        }
        if (to != -1 && weight != -1) {                  // jeżeli znaleziono numer wierchołla i wagę, to dodajemy krawędż do grafu
            if (to < 0 || to > rows * columns - 1 || weight < 0 || weight > 10000) {
                printf("Wrong data format in file");
                exit(-1);
            }
            addEdge(graph, from, to, weight);
        }
        from++;                                      //zwiększamy numer bieżącego wiersza
    }
    fclose(file);                                    //zamykamy plik 
    return graph;                                    //zwracamy wczytany graf
}