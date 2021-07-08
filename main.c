#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movieSeriesADT.h"
#include "movieSeriesBack.h"
#define MAXGENRE 3
#define MAXTEXTO 200

int main( int argc, char *argv[]){
    
    if(argc > 2){
        perror("Error: se pasaron demasiados argumentos\n");
        exit(1);
    }

    FILE * miArch;

    miArch= fopen(argv[1],"r");

    if(miArch==NULL){
        perror("Error: no se pudo abrir el archivo");
        exit(1);
    }

    const char s[2]=";";
    char* string=malloc(sizeof(char)*200);
    if (string==NULL)
    {
        perror("Error de memoria");
        exit(1);
    }
    movieSeriesADT movieSeries = newMovieSeries();
    char* n=fgets(string,MAXTEXTO,miArch);   //para "saltear" la primer linea
    while(fgets(string,MAXTEXTO,miArch)){    //asumimos que como maximo hay 200 caracteres por linea
        analizeAndAdd(movieSeries, string, s);
    }
    free(string);
    fclose(miArch);


    /* ARRANCO EL TESTEO*/
    
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
    /*FILE* q2=fopen("query2.csv","w");
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
            fprintf(q2, "%d;%s;%d\n", currYear(movieSeries),
                    currGenre(movieSeries),currGenreCount(movieSeries));
            nextGenre(movieSeries);
        }
        nextYear(movieSeries);
    }
    fclose(q2);*/


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
        if(mostVotedMovie(movieSeries,&name,&votes,&rating))
            fprintf(q3, "%s;%d;%.1f;",name,votes,rating);
        if(mostVotedSeries(movieSeries,&name,&votes,&rating))
            fprintf(q3, "%s;%d;%.1f",name,votes,rating);
        fprintf(q3, "\n");
        nextYear(movieSeries);
    }
    fclose(q3);

}

