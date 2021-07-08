#include <stdlib.h>

char* strAux;
char ** genres, auxMem;             //llena con NULL, y si es movie y tiene uno o mas
genres = calloc(1,sizeof(char*));
if (genres == NULL)
    exit(1);
strAux=strtok(finalAux,",");                //generos llena con los generos
if(!strcmp(type,"movie")) {
    int count=0, flag = 0;
    while (strAux!=NULL) {
        count++;
        auxMem = realloc(count, sizeof(char *));
        if (auxMem == NULL)
            exit(1);
        genres = auxMem;
        genres[count-1] = malloc(strlen(strAux)+1);
        strcpy(genres[count-1],strAux);
        strAux=strtok(NULL,",");
    }
}