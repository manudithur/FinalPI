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

int countGenre(tContent * firstContent, char * genre){
        int c = 0;

    tContent aux = firstContent;
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

void mostVotesPerType(tContent * firstContent, char * type, char * MaxTitle, unsigned int * MaxVotes, float * MaxRating);


hola