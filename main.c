#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movieSeriesADT.h"

int main( int argc, char *argv[]){

    //FER:
    movieSeriesADT movieSeries = newMovieSeries();

    //query1
    fprintf(FPTRSALIDA, "year;films;series\n");
    toBeginYear(movieSeries);
    while(hasNextYear(movieSeries)){
        fprintf(FPTRSALIDA, "%d;%d;%d\n",currYear(movieSeries),
                currYearMovieCount(movieSeries), currYearSeriesCount(movieSeries));
        nextYear(movieSeries);
    }

    //query2
    fprintf(FPTRSALIDA, "year;genre;films\n");
    toBeginYear(movieSeries);
    while(hasNextYear(movieSeries)){
        toBeginGenre(movieSeries);
        while (hasNextGenre(movieSeries)) {
            fprintf(FPTRSALIDA, "%d;%d;%d\n", currYear(movieSeries),
                    currGenre(movieSeries),currGenreCount(movieSeries));
            nextGenre(movieSeries);
        }
        nextYear(movieSeries);
    }


    //query3
    fprintf(FPTRSALIDA, "startYear;film;votesFilm;ratingFilm;serie;votesSerie;ratingSerie\n");
    toBeginYear(movieSeries)
    while (hasNextYear(movieSeries)) {
        fprintf(FPTRSALIDA, "%d;", currYear(movieSeries));
        char * name; int votes; float rating;
        mostVotedMovie(adt,&name,&votes,&rating);
        fprintf(FPTRSALIDA, "%s;%d;%f;",name,votes,rating);
        mostVotedSeries(adt,&name,&votes,&rating);
        fprintf(FPTRSALIDA, "%s;%d;%f\n",name,votes,rating);
        nextYear(movieSeries);
    }
}