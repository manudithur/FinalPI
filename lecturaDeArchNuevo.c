#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main () {
    char * finalAux = "Action,Drama";
    char *strAux;
    char **genres, **auxMem;             //llena con NULL, y si es movie y tiene uno o mas
    genres = calloc(1, sizeof(char *));
    if (genres == NULL)
        exit(1);
    strAux = strtok(finalAux, ",");
    int count = 0; //sacar
    char * type = "movie";
    if (!strcmp(type, "movie")) {
        //int count = 0; agregar
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
    for (int i = 0; i < count; i++)
        printf("%s\n",genres[i]);
    printf("count es %d\n",count);
}