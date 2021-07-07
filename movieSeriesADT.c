#include <stdio.h>
#include <string.h>
#include "movieSeriesADT.h"

typedef struct content {            //Lista para los contenidos. Se consideran por igual series y peliculas.
    char * title;                   //Solo vamos a almacenar los datos del CSV que nos sirven para nuestros queries
    float rating;                   //Todos los otros datos seran ignorados.
    unsigned int numVotes;          //En caso de necesitar otros datos se modificaria el add y la estructura.
    struct content * tail;
} tContent;

typedef struct genre{              //Lista de los generos
    char * genre;                  //Se van a guardar en orden alfabetico
    unsigned int count;
    tGenre * tail;
}tGenre;

typedef struct year {               //Lista de los anios de mayor a menor
    int year;
    tContent * firstMovie;          //Puntero al primer nodo de la lista de movies.
    tContent * firstSeries;         //Puntero al primer nodo de la lista series.
    unsigned int movieCount;
    unsigned int seriesCount;
    tGenre * firstGenre;
    tGenre * currGenre;
    struct year * tail;
} tYear;

typedef struct movieSeriesCDT {
    tYear * firstYear;              //Puntero al primer nodo de la lista year
    tYear * currYear;               //Puntero al nodo actual de trabajo (iterador)
} movieSeriesCDT;



//De aca para abajo falta rehacerlo con la nueva estructura.

void maxType (movieSeriesADT movieSeries, char * tipo, char * nombre, int * votes, float * rating) {
    tYear * year = movieSeries->currYear;
    tContent * aux = maxVotes(year->firstContent,tipo);
    nombre = malloc(strlen(aux->title)+1);
    strcpy(nombre,aux->title);
    *votes = aux->numVotes;
    *rating = aux->rating;
}

tContent * maxVotes (tContent * list, char * tipo) {

    tContent * ans, * aux = list;
    int max = 0;
    aux = list;

    while (aux != NULL) {
        if (strcmp(tipo, aux->type) == 0)
            if (aux->numVotes > max) {
                max = aux->numVotes;
                ans = aux;
            }

        aux = aux->tail;
    }
    
    return ans;

}

void freeRecContent(tContent * list){
    if(list == NULL)
        return;
    freeRecContent(list->tail);
    free(list->title);
    free(list->type);
    for(int i = 0 ; list->genres[i] != NULL ; i++)
        free(list->genres[i]);
    free(list->genres);
    free(list);
}

void freeYearsRec(tYear * first){
    if(first == NULL)
        return;
    freeYearsRec(first->tail);
    freeRecContent(first->firstContent);
    free(first);
}

void free(movieSeriesADT movieSeries){
    freeYearsRec(movieSeries->vecYears);
    free(movieSeries);
}

void toBeginYear(movieSeriesADT movieSeries){
    movieSeries->currYear =movieSeries->vecYears;
}

int hasNextYear(movieSeriesADT movieSeries){
    return movieSeries->currYear != NULL;
}

void nextYear(movieSeriesADT movieSeries){
    movieSeries->currYear = movieSeries->currYear->tail;
}
