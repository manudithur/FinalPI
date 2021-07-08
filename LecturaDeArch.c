#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movieSeriesADT.h"   
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
    char* token;
    movieSeriesADT movieSeries = newMovieSeries();
    char* n=fgets(string,MAXTEXTO,miArch);   //para "saltear" la primer linea
    while(fgets(string,MAXTEXTO,miArch)){    //asumimos que como maximo hay 200 caracteres por linea
        
        
        token=strtok(string,s);
        char* type=token;                

        token=strtok(NULL,s);
        char* title=token;

        token=strtok(NULL,s);
        int year=atoi(token);
        

        token=strtok(NULL,s);                          //no nos interesa endY
        

        token=strtok(NULL,s);
        char* finalAux=token;                             
        /* trabajo despues con generos para no afectar el estado interno de strtok */

        token=strtok(NULL,s);
        float rating=atof(token);

        token=strtok(NULL,s);
        int numVotes=atoi(token);

        token=strtok(NULL,s);                       //no nos interesa runtimeMins




        char* strAux;
        char * genres[MAXGENRE]={NULL};             //llena con NULL, y si es movie y tiene uno o mas
        strAux=strtok(finalAux,",");                //generos llena con los generos
        if(!strcmp(type,"movie")){
            int count=0;                                 
            while(strAux!=NULL){
                genres[count++]=strAux;    
                strAux=strtok(NULL,",");                 
            }                                            
        }

        addContent(movieSeries,year,type,title,rating,numVotes);
    }
    free(string);
    fclose(miArch);


    /* ARRANCO EL TESTEO*/
    
    //query1
    printf("year;films;series\n");
    toBeginYear(movieSeries);
    while(hasNextYear(movieSeries)){
        printf("%d", currYear(movieSeries));
        putchar(';');
        printf("%d", currYearMovieCount(movieSeries));
        putchar(';');
        printf("%d", currYearSeriesCount(movieSeries));
        putchar('\n');
        nextYear(movieSeries);
    }

    putchar('\n');
    putchar('\n');
/*
    //query2
    printf (encabezado);
    toBeginYear(movieSeries);
    while(hasNextYear(movieSeries)){
        toBeginGenre(movieSeries);
        while (hasNextGenre(movieSeries)) {
            printf(currYear(movieSeries));
            printf(currGenre(movieSeries));
            printf(currGenreCount(movieSeries));
            nextGenre(movieSeries);
        }
        nextYear(movieSeries);
    }
*/

    //query3
    printf("startYear;film;votesFilm;ratingFilm;serie;votesSerie;ratingSerie");
    toBeginYear(movieSeries);
    while (hasNextYear(movieSeries)) {
        char * name; int votes; float rating;
        printf("%d      ", currYear(movieSeries));
        if(mostVotedMovie(movieSeries,&name,&votes,&rating))
            printf ("%s ;   %d  ;   %g  ;   ", name, votes, rating);
        if(mostVotedSeries(movieSeries,&name,&votes,&rating))
            printf ("%s ;   %d  ;   %g", name, votes, rating);
        nextYear(movieSeries);
        putchar('\n');
    }

}

