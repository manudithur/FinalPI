//Funciones back-end
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "movieSeriesADT.h"

void analizeAndAdd (movieSeriesADT movieSeries, char * string, const char * s, int * errorFlag) {
    char * token;
    token = strtok(string, s);                            //El primer token es para guardar el tipo
    char *type = token;

    token = strtok(NULL, s);
    char *title = token;                                  //El segundo token es para guardar el titulo

    token = strtok(NULL, s);                          //El tercero es para guardar el año 
    int year = atoi(token);                                //Si por ejemplo es un /N, se guarda como 0

    token = strtok(NULL, s);                          //No nos interesa endY

    token = strtok(NULL, s);                          //El quinto son los generos, separados por ","
    char *finalAux = token;
/* trabajo despues con generos para no afectar el estado interno de strtok */

    token = strtok(NULL, s);                          //El sexto es el rating
    float rating = atof(token);                           //Como en el caso de year, si es /N se guarda como 0

    token = strtok(NULL, s);                          //El septimo es numVotes
    int numVotes = atoi(token);                           //Pasa lo mismo que con year y rating

    token = strtok(NULL, s);                          //No nos interesa runtimeMins

    char *strAux;
    char **genres, **auxMem;                              //Vector dinamico que va a almacenar todos los genres
    genres = calloc(1, sizeof(char *));            //genres apunta a NULL
    if (genres == NULL) {
        *errorFlag = 1;
        return;
    }
    strAux = strtok(finalAux, ",");                  //El nuevo token es ','
    int count = 0;
    if (!strcmp(type, "movie")) {                         //Solo nos interesan los genres de las movies
        while (strAux != NULL) {
            count++;
            auxMem = realloc(genres, sizeof(char *) * count);
            if (auxMem == NULL) {
                *errorFlag = 1;
                return;
            }
            genres = auxMem;
            genres[count - 1] = malloc(strlen(strAux) + 1);
            if (genres[count - 1] == NULL) {
                *errorFlag = 1;
                return;
            }
            strcpy(genres[count - 1], strAux);
            strAux = strtok(NULL, ",");
        }
    }
    //Si agregamos genres nos aseguramos de que el ultimo sea NULL
    if (count != 0) {
        count++;
        auxMem = realloc(genres, sizeof(char *) * count);
        if (auxMem == NULL) {
            *errorFlag = 1;
            return;
        }
        genres = auxMem;
        genres[count - 1] = NULL;
    }

    //Si no se cumple alguna de estas condiciones no lo agregamos ya que contiene data no valida
    if (year!=0 && type!=NULL && title!=NULL && rating!=0 && numVotes!=0){
        addContent(movieSeries, year, type, title, rating, numVotes, genres, errorFlag);
        }
    int i;

    //Liberamos recursos
    for (i=0 ; genres[i]!=NULL ; i++)
        free(genres[i]);
    free(genres);
}