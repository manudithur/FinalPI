#include <stdio.h>
#include <string.h>
#include "movieSeriesADT.h"

typedef struct content {
    char * type;
    char * title;
    char ** genres;
    int startY;
    int endY;
    float rating;
    int runTimeMins;
    unsigned int numVotes;
    struct content * tail;
} tContent;

typedef struct year {
    int year;
    tContent * firstContent;
    struct year * tail;
} tYear;

typedef struct movieSeriesCDT {
    tYear * vecYears;
    tYear * currYear;
} movieSeriesCDT;

int countType(tContent * firstContent, char * type){

    int c = 0;

    tContent * aux = firstContent;
    while ( aux != NULL){
        if( strcmp(aux->type, type ) == 0 )
            c++;
        aux = aux->tail;
    }

    return c;

}

int countGenre(tContent * firstContent, char * genre){
    int c = 0;

    tContent * aux = firstContent;
    int flag = 0;
    while ( aux != NULL){
        for( int i = 0 ; firstContent->genres[i] && !flag ; i++ ){
            if( strcmp(firstContent->genres[i], genre) == 0 ){
                c++;
                flag = 1;
            }
        }
        aux = aux->tail;
        flag = 0;
    }

    return c;
}

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

void toBegin(movieSeriesADT movieSeries){
    movieSeries->currYear =movieSeries->vecYears;
}

int hasNext(movieSeriesADT movieSeries){
    return movieSeries->currYear != NULL;
}

void next(movieSeriesADT movieSeries){
    movieSeries->currYear = movieSeries->currYear->tail;
}
