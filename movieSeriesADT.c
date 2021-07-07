#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
    struct genre * tail;
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

//Funciones para query1
int currYear(movieSeriesADT movieSeries) {
    return movieSeries->currYear->year;
}

int currYearMovieCount(movieSeriesADT movieSeries) {
    return movieSeries->currYear->movieCount;
}

int currYearSeriesCount(movieSeriesADT movieSeries) {
    return movieSeries->currYear->seriesCount;
}

//Funciones para query2
char * currGenre(movieSeriesADT movieSeries) {
    char * ans = malloc(strlen(movieSeries->currYear->currGenre->genre) + 1);
    if (ans == NULL)
        exit(1);
    strcpy(ans,movieSeries->currYear->currGenre->genre);
    return ans;
}

int currGenreCount(movieSeriesADT movieSeries) {
    return movieSeries->currYear->currGenre->count;
}

//Funciones para query3
static tContent * findMostVotes(tContent * list) {
    int max = 0;
    tContent * ans, * curr = list;
    while (curr != NULL) {
        if (curr->numVotes > max) {
            max = curr->numVotes;
            ans = curr;
        }
        curr = curr->tail;
    }
    return ans;
}

void mostVotedMovie(movieSeriesADT movieSeries, char ** name, int * votes, float * rating) {
    tContent * aux = findMostVotes(movieSeries->currYear->firstMovie);
    char * title = malloc(strlen(aux->title)+1);
    if (title == NULL)
        exit(1);
    strcpy(title,aux->title);
    *name = title;
    *votes = aux->numVotes;
    *rating = aux->rating;
}

void mostVotedSeries(movieSeriesADT movieSeries, char ** name, int * votes, float * rating) {
    tContent * aux = findMostVotes(movieSeries->currYear->firstSeries);
    char * title = malloc(strlen(aux->title)+1);
    if (title == NULL)
        exit(1);
    strcpy(title,aux->title);
    *name = title;
    *votes = aux->numVotes;
    *rating = aux->rating;
}

//Funciones que liberan recursos
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

//Controladores del iterador de year
void toBeginYear(movieSeriesADT movieSeries){
    movieSeries->currYear = movieSeries->firstYear;
}

int hasNextYear(movieSeriesADT movieSeries){
    return movieSeries->currYear != NULL;
}

void nextYear(movieSeriesADT movieSeries){
    movieSeries->currYear = movieSeries->currYear->tail;
}

//Controladores del iterador de genre
void toBeginGenre(movieSeriesADT movieSeries) {
    movieSeries->currYear->currGenre = movieSeries->currYear->firstGenre;
}

int hasNextGenre(movieSeriesADT movieSeries) {
    return movieSeries->currYear->currGenre != NULL;
}

void nextGenre(movieSeriesADT movieSeries) {
    movieSeries->currYear->currGenre = movieSeries->currYear->currGenre->tail;
}
