#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movieSeriesADT.h"
#include "movieSeriesBack.h"
#define MAXTEXTO 300

int main( int argc, char *argv[]){
    
    if(argc > 2){
        fprintf(stderr, "Error: se pasaron demasiados argumentos\n");        //No se deben pasar mas de dos argumentos
        exit(1);
    }

    FILE * miArch;

    miArch= fopen(argv[1],"r");                                     //Abrimos el archivo .csv para lectura

    if(miArch==NULL){
        fprintf(stderr, "Error: no se pudo abrir el archivo\n");       //Si no se puede abrir el archivo no seguimos con el programa
        exit(1);
    }
    int errorFlag=0;

    const char s[2]=";";
    char* string=malloc(sizeof(char)*MAXTEXTO);
    if (string==NULL)
    {
        fprintf(stderr, "Error: memoria");
        exit(1);
    }
    movieSeriesADT movieSeries = newMovieSeries();  //Creamos un nuevo ADT
    fgets(string,MAXTEXTO,miArch);                  //Salteamos la linea de encabezado
    while(fgets(string,MAXTEXTO,miArch)){           //Asumimos que como maximo hay MAXTEXTO caracteres por linea
        analizeAndAdd(movieSeries, string, s, &errorFlag);      //Se agrega cada linea si es que contiene data valida
        if(errorFlag==1){                           //Si hubo un error de memoria al agregar a la lista
            fprintf(stderr, "Error: memoria");
            exit(1);                                //Si hay error de memoria no seguimos con el programa
        }
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
    fprintf(q1, "year;films;series\n");             //Se imprime el encabezado del archivo
    toBeginYear(movieSeries);                       //Arrancamos el iterador
    while(hasNextYear(movieSeries)){                //Como esta ordenado descendentemente va desde el año mas alto hasta el mas bajo
        fprintf(q1, "%d;%d;%d\n",currYear(movieSeries),
                currYearMovieCount(movieSeries), currYearSeriesCount(movieSeries));             //Imprime en el nuevo archivo con formato year;moviesCount;seriesCount
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
    fprintf(q2, "year;genre;films\n");      //Imprimimos encabezado
    toBeginYear(movieSeries);               //Arrancamos el iterador de años
    while(hasNextYear(movieSeries)){        
        toBeginGenre(movieSeries);          //Arrancamos el iterador de generos
        while (hasNextGenre(movieSeries)) {
            char * genre;
            currGenre(movieSeries, &genre, &errorFlag);
            if (errorFlag==1)
            {
                fprintf(stderr, "Error: memoria");
                exit(1);
            }
            
            fprintf(q2, "%d;%s;%d\n", currYear(movieSeries), genre, currGenreCount(movieSeries));       //Imprimimos con formato year;genre;filmCount
            nextGenre(movieSeries);
            free(genre);
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
    fprintf(q3, "startYear;film;votesFilm;ratingFilm;serie;votesSerie;ratingSerie\n");      //Imprimimos el encabezado
    toBeginYear(movieSeries);                                                               //Arrancamos el iterador por año
    while (hasNextYear(movieSeries)) {
        fprintf(q3, "%d;", currYear(movieSeries));                                          //Imprimimos en el nuevo archivo el año
        char * nameM, * nameS; int votes; float rating;
        if(mostVotedMovie(movieSeries,&nameM,&votes,&rating,&errorFlag)){                              
            if(errorFlag==1){
                fprintf(stderr,"Error: memoria");
                exit(1);
            }
            fprintf(q3, "%s;%d;%.1f;",nameM,votes,rating);                                  //Imprimimos el nombre, la cantidad de votos y el rating de la pelicula con mas votos
            free(nameM);
        }
        if(mostVotedSeries(movieSeries,&nameS,&votes,&rating, &errorFlag)){
            if(errorFlag==1){
                fprintf(stderr,"Error: memoria");
                exit(1);
            }
            fprintf(q3, "%s;%d;%.1f",nameS,votes,rating);                                   //Imprimimos el nombre, la cantidad de votos y el rating de la pelicula con mas votos
            free(nameS);
        }
        fprintf(q3, "\n");
        nextYear(movieSeries);
    }
    fclose(q3);

    freeMovieSeries(movieSeries);
}

