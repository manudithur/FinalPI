//Funciones Back End
#ifndef _MOVIESERIESBACK_H
#define _MOVIESERIESBACK_H

//funcion que recibe una linea del csv y el token y la analiza y la agrega al TAD
void analizeAndAdd (movieSeriesADT movieSeries, char * string, const char * s, int * errorFlag);

#endif