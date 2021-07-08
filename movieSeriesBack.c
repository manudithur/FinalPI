//Funciones Back End
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "movieSeriesADT.h"

void analizeAndAdd (movieSeriesADT movieSeries, char * string, const char * s) {
    char * token;
    token = strtok(string, s);
    char *type = token;

    token = strtok(NULL, s);
    char *title = token;

    token = strtok(NULL, s);
    int year = atoi(token);

    token = strtok(NULL, s);                          //no nos interesa endY

    token = strtok(NULL, s);
    char *finalAux = token;
/* trabajo despues con generos para no afectar el estado interno de strtok */

    token = strtok(NULL, s);
    float rating = atof(token);

    token = strtok(NULL, s);
    int numVotes = atoi(token);

    token = strtok(NULL, s);                       //no nos interesa runtimeMins

    char *strAux;
    char **genres, **auxMem;             //llena con NULL, y si es movie y tiene uno o mas
    genres = calloc(1, sizeof(char *));
    if (genres == NULL)
        exit(1);
    strAux = strtok(finalAux, ",");
    if (!strcmp(type, "movie")) {
        int count = 0;
        while (strAux != NULL) {
            count++;
            auxMem = realloc(genres, sizeof(char *) * count);
            if (auxMem == NULL)
                exit(1);
            genres = auxMem;
            genres[count - 1] = malloc(strlen(strAux) + 1);
            if (genres[count - 1] == NULL)
                exit(1);
            strcpy(genres[count - 1], strAux);
            strAux = strtok(NULL, ",");
        }
    }

    addContent(movieSeries, year, type, title, rating, numVotes);
}