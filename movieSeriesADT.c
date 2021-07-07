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

<<<<<<< Updated upstream
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

movieSeriesADT newMovieSeries () {
    return calloc(1,sizeof(movieSeriesCDT));
}

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
//si estan desordenadas
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

void _mostVotedMovie(movieSeriesADT movieSeries, char ** name, int * votes, float * rating) {
    tContent * aux = findMostVotes(movieSeries->currYear->firstMovie);
    char * title = malloc(strlen(aux->title)+1);
    if (title == NULL)
        exit(1);
    strcpy(title,aux->title);
    *name = title;
    *votes = aux->numVotes;
    *rating = aux->rating;
}

void _mostVotedSeries(movieSeriesADT movieSeries, char ** name, int * votes, float * rating) {
    tContent * aux = findMostVotes(movieSeries->currYear->firstSeries);
    char * title = malloc(strlen(aux->title)+1);
    if (title == NULL)
        exit(1);
    strcpy(title,aux->title);
    *name = title;
    *votes = aux->numVotes;
    *rating = aux->rating;
}

//teniendo en cuenta que las movies y series estan ordenadas de mas votos a menos
void mostVotedMovie(movieSeriesADT movieSeries, char ** name, int * votes, float * rating) {
    char * title = malloc(strlen(movieSeres->currYear->firstMovie->title)+1);
    if (title == NULL)
        exit(1);
    strcpy(title,movieSeries->currYear->firstMovie->title);
    *name = title;
    *votes = movieSeries->currYear->firstMovie->numVotes;
    *rating = movieSeries->currYear->firstMovie->rating;
}

void mostVotedSeries(movieSeriesADT movieSeries, char ** name, int * votes, float * rating) {
    char * title = malloc(strlen(movieSeres->currYear->firstSeries->title)+1);
    if (title == NULL)
        exit(1);
    strcpy(title,movieSeries->currYear->firstSeries->title);
    *name = title;
    *votes = movieSeries->currYear->firstSeries->numVotes;
    *rating = movieSeries->currYear->firstSeries->rating;
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
