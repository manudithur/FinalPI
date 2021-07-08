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

//static void freeRecContent(tContent * list);
//static void freeYearsRec(tYear * first);
static tContent * addContentREC(tContent * first, char * title, float rating, unsigned int votes, int * flag );
static tYear * addYearREC(tYear * first, int year, tYear ** newNode);
static tGenre * addGenreREC(tGenre * first, char * genre);
//Esta funcion paso el testeo 2021-07-07 17:03:40

tYear * searchOrAddYear(movieSeriesADT adt, int year){
    tYear * found = NULL;
    adt->firstYear = addYearREC(adt->firstYear, year, &found);
    return found;
}

//Esta funcion paso el testeo 2021-07-07 17:03:40
static tYear * addYearREC(tYear * first, int year, tYear ** newNode){

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

//Esta funcion paso el teesteo el 2021-07-07 18:20:17
void addContent(movieSeriesADT adt, int year, char * type, char * title, float rating, unsigned int votes, char ** genres){
    int flag = 0;
    tYear * currYear = searchOrAddYear(adt, year);
    int c;
    if((c=strcmp(type, "movie"))==0){
        currYear->firstMovie = addContentREC(currYear->firstMovie, title, rating, votes, &flag);
        currYear->movieCount += flag;
        int i;
        for( i = 0 ; genres[i] != NULL ; i++)
            currYear->firstGenre = addGenreREC(currYear->firstGenre, genres[i]);
        
    }
    else if((c=strcmp(type, "tvSeries"))==0){
        currYear->firstSeries = addContentREC(currYear->firstSeries, title, rating, votes, &flag);
        currYear->seriesCount += flag;
    }
    return;
}

tGenre * addGenreREC(tGenre * first, char * genre){
    int c;
    if(first == NULL || (c=strcmp(first->genre, genre)) > 0){
        tGenre * new = malloc(sizeof(tGenre));
        if(new == NULL)
            exit(1);
        new->genre = malloc(strlen(genre)+1);
        strcpy(new->genre, genre);
        new->count = 1;
        new->tail = first;
        return new;
    }
    else if(c<0)
        first->tail = addGenreREC(first->tail, genre);
    else                                                              //En este punto c=0;
        first->count++;
    return first;
}

static tContent * addContentREC(tContent * first, char * title, float rating, unsigned int votes, int * flag ){
    int c;
    if(first == NULL || (c=first->numVotes - votes) < 0 ){
        tContent * new = malloc(sizeof(tContent));
        if (new == NULL)
            exit(1);
        new->title = malloc(strlen(title)+1);
        strcpy(new->title, title);
        new->rating = rating;
        new->numVotes = votes;
        new->tail = first;
        *flag = 1;
        return new;
    }
    else
        first->tail = addContentREC(first->tail, title, rating, votes, flag);
    return first;
}

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
//teniendo en cuenta que las movies y series estan ordenadas de mas votos a menos
int mostVotedMovie(movieSeriesADT movieSeries, char ** name, int * votes, float * rating) {
    if(movieSeries->currYear->firstMovie == NULL)
        return 0;
    char * title = malloc(strlen(movieSeries->currYear->firstMovie->title)+1);
    if (title == NULL)
        exit(1);
    strcpy(title,movieSeries->currYear->firstMovie->title);
    *name = title;
    *votes = movieSeries->currYear->firstMovie->numVotes;
    *rating = movieSeries->currYear->firstMovie->rating;
    return 1;
}

int mostVotedSeries(movieSeriesADT movieSeries, char ** name, int * votes, float * rating) {
    if(movieSeries->currYear->firstSeries == NULL)
        return 0;
    char * title = malloc(strlen(movieSeries->currYear->firstSeries->title)+1);
    if (title == NULL)
        exit(1);
    strcpy(title,movieSeries->currYear->firstSeries->title);
    *name = title;
    *votes = movieSeries->currYear->firstSeries->numVotes;
    *rating = movieSeries->currYear->firstSeries->rating;
    return 1;
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
/*
//libero recursos
static void freeContentRec (tContent * list) {
    if (list == NULL)
        return;
    freeContentRec(list->tail);
    free(list->title);
    free(list);
}

static void freeGenreRec (tGenre * list) {
    if (list == NULL)
        return;
    freeGenreRec(list->tail);
    free(list->genre);
    free(list);
}

static void freeYearsRec (tYear * yearList) {
    if (yearList == NULL)
        return;
    freeYearsRec(yearList->tail);
    freeContentRec(yearList->firstMovie);
    freeContentRec(yearList->firstSeries);
    freeGenreRec(yearList->firstGenre);
    free(yearList->currGenre);
}

void free (movieSeriesADT movieSeries) {
    freeYearsRec(movieSeries->firstYear);
    free(movieSeries);
}
*/
