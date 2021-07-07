#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movieSeriesADT.h"

int main( int argc, char *argv[]){

    //FER:
    movieSeriesADT movieSeries = newMovieSeries();

    //query1
    write(“year;films;series”);
    toBeginYear(movieSeries);
    while(hasNextYear(movieSeries)){
        write(currYear(movieSeries));
        write(;);
        write(currYearMovieCount(adt));
        write(;);
        write(currYearSeriesCount(adt));
        write(‘/n’)
        nextYear(movieSeries);
    }

    //query2
    write (encabezado);
    toBeginYear(movieSeries);
    while(hasNextYear(movieSeries)){
        toBeginGenre(movieSeries);
        while (hasNextGenre(movieSeries)) {
            write(currYear(movieSeries));
            write(currGenre(movieSeries));
            write(currGenreCount(movieSeries));
            nextGenre(movieSeries);
        }
        nextYear(movieSeries);
    }


    //query3
    write (encabezado)
    toBeginYear(movieSeries)
    while (hasNextYear(movieSeries)) {
        char * name; int votes; float rating;
        mostVotedMovie(adt,&name,&votes,&rating);
        Write (name, votes, rating);
        mostVotedSeries(adt,&name,&votes,&rating);
        Write (name, votes, rating);
        nextYear(movieSeries);
    }
}