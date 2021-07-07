#ifndef _MOVIESERIESADT_H
#define _MOVIESERIESADT_H

typedef struct movieSeriesCDT * movieSeriesADT;

//FUNCIONES PARA QUERY1
//devuelve el anio actual en el que esta el iterador
int currYear(movieSeriesADT movieSeries);
//devuelve el numero de movies del anio actual
int currYearMovieCount(movieSeriesADT movieSeries);
//devuelve el numero de series del anio actual
int currYearSeriesCount(movieSeriesADT movieSeries);

//FUNCIONES PARA QUERY2
//devuelve una copia del nombre del genre actual
char * currGenre(movieSeriesADT movieSeries);
//devuelve la cantidad de genres en el anio actual
int currGenreCount(movieSeriesADT movieSeries);

//FUNCIONES PARA QUERY3
//devuelve un puntero al tContent con mas votos
static tContent * findMostVotes(tContent * list);
//devuelve por parametros de salida el nombre, la cantidad de votos y el rating
//de la serie mas votada del currYear
void mostVotedMovie(movieSeriesADT movieSeries, char ** name, int * votes, float * rating);
//devuelve por parametros de salida el nombre, la cantidad de votos y el rating
//de la serie mas votada del currYear
void mostVotedSeries(movieSeriesADT movieSeries, char ** name, int * votes, float * rating);

//Funciones que liberan recursos
static void freeRecContent(tContent * list);

static void freeYearsRec(tYear * first);

void free(movieSeriesADT movieSeries);

//Controladores del iterador de year
void toBeginYear(movieSeriesADT movieSeries);

int hasNextYear(movieSeriesADT movieSeries);

void nextYear(movieSeriesADT movieSeries);

//Controladores del iterador de genre
void toBeginGenre(movieSeriesADT movieSeries);

int hasNextGenre(movieSeriesADT movieSeries);

void nextGenre(movieSeriesADT movieSeries);

#endif
