#include <stdio.h>
#include <string.h>

typedef struct content {
    char * type;
    char * title;
    char ** genres;
    int startY;
    int endY;
    float rating;
    unsigned int runTimeMins;
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
} movieSeriesCDT;

int countType(tContent * firstContent, char * type){

    int c = 0;

    tContent aux = firstContent;
    while ( aux != NULL){
        if( strcmp(firstContent->type, type ) == 0 )
            c++;
        aux = aux->tail;
    }

    return c;

}

int countGenre(tContent * firstContent, char * genre);

void mostVotesPerType(tContent * firstContent, char * type, char * MaxTitle, unsigned int * MaxVotes, float * MaxRating);


