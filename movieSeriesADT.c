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

//Esta funcion paso el testeo 2021-07-07 17:03:40

tYear * searchOrAddYear(movieSeriesADT adt, int year){
    tYear * found = NULL;
    adt->firstYear = addYearREC(adt->firstYear, year, &found);
    return found;
}

//Esta funcion paso el testeo 2021-07-07 17:03:40
tYear * addYearREC(tYear * first, int year, tYear ** newNode){

    int c;
    if( first == NULL || (c = first->year - year) < 0 ){
        tYear * new = malloc(sizeof(tYear));
        if(new == NULL)
            exit(1);
        new->year = year;
        new->movieCount = 0;
        new->seriesCount = 0;
        new->tail = first;
        *newNode = new;
        return new;
    }
    if( c > 0 )
        first->tail = addYearREC(first->tail, year, newNode);
    if(c == 0)
        *newNode = first;
    return first;
}

void addContent(movieSeriesADT adt, int year, char * type, char * title, float rating, unsigned int votes ){
    int flag = 0;
    tYear * year = searchOrAddYear(adt, year);
    int c;
    if((c=strcmp(type, "movie"))==0){
        addContentREC(year->firstMovie, title, rating, votes, &flag);
        year->movieCount += flag;
    }
    else if((c=strcmp(type, "tvSeries"))==0){
        addContentREC(year->firstSeries, title, rating, votes, &flag);
        year->seriesCount += flag;
    }
    return;
}

tContent * addContentREC(tContent * first, char * title, float rating, unsigned int votes int * flag ){
    int c;
    if(first == NULL || (c=first->numVotes - votes) < 0 ){
        tContent * new = malloc(sizeof(tContent));
        if (new == NULL)
            exit(1);
        new->title = malloc(strlen(title)+1);
        strcpy(new->title, title);
        new->rating = rating
        new->numVotes = votes;
        new->tail = first;
        *flag = 1;
        return new;
    }
    if(c>0)
        first->tail = addContentREC(first->tail, title, rating, votes, flag);
    if(c == 0)
        return first;
    return first;
}

void addGenre(movieSeriesADT adt)

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

//Funciones para query1
int currYear(movieSeriesADT movieSeries) {
    return movieSeries->currYear->year;
}