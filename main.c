#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movieSeriesADT.c"

int main( int argc, char *argv){
    
    if(argc > 2)
        perror("Error: se pasaron demasiados argumentos\n");

    FILE* miArch;

    miArch= fopen(argv[1],"r");

    if(miArch==NULL)
        perror("Error: no se pudo abrir el archivo");
}