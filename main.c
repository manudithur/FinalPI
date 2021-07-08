#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movieSeriesADT.h"

int main( int argc, char *argv[]){

    //FER:
    movieSeriesADT movieSeries = newMovieSeries();

    //query1
    FILE* q1=fopen("query1.csv","w");
    if (q1==NULL)
    {
        perror("Error: ");
        exit(1);
    }
    fprintf(q1, "year;films;series\n");
    toBeginYear(movieSeries);
    while(hasNextYear(movieSeries)){
        fprintf(q1, "%d;%d;%d\n",currYear(movieSeries),
                currYearMovieCount(movieSeries), currYearSeriesCount(movieSeries));
        nextYear(movieSeries);
    }
    fclose(q1);

    //query2
    FILE* q2=fopen("query2.csv","w");
    if (q2==NULL)
    {
        perror("Error: ");
        exit(1);
    }
    fprintf(q2, "year;genre;films\n");
    toBeginYear(movieSeries);
    while(hasNextYear(movieSeries)){
        toBeginGenre(movieSeries);
        while (hasNextGenre(movieSeries)) {
            fprintf(q2, "%d;%d;%d\n", currYear(movieSeries),
                    currGenre(movieSeries),currGenreCount(movieSeries));
            nextGenre(movieSeries);
        }
        nextYear(movieSeries);
    }
    fclose(q2);


    //query3
    FILE* q3=fopen("query3.csv","w");
    if (q3==NULL)
    {
        perror("Error: ");
        exit(1);
    }
    fprintf(q3, "startYear;film;votesFilm;ratingFilm;serie;votesSerie;ratingSerie\n");
    toBeginYear(movieSeries);
    while (hasNextYear(movieSeries)) {
        fprintf(q3, "%d;", currYear(movieSeries));
        char * name; int votes; float rating;
        mostVotedMovie(adt,&name,&votes,&rating);
        fprintf(q3, "%s;%d;%f;",name,votes,rating);
        mostVotedSeries(adt,&name,&votes,&rating);
        fprintf(q3, "%s;%d;%f\n",name,votes,rating);
        nextYear(movieSeries);
    }
    fclose(q3);
}