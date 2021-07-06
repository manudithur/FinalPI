#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movieSeriesADT.c"   //hay q incluir el .h 

int main( int argc, char *argv){
    
    if(argc > 2)
        perror("Error: se pasaron demasiados argumentos\n");
        exit;

    FILE* miArch;

    miArch= fopen(argv[1],"r");

    if(miArch==NULL)
        perror("Error: no se pudo abrir el archivo");
        exit;

    const char s[2]=";";
    char* string;
    char* token;
    while(fgets(string,200,miArch)){    //asumimos que como maximo hay 200 caracteres por linea
        tContent* node= newNode();      //funcion que cree un nuevo nodo

        token=strtok(string,s);         //todavia no entiendo 100% esto del strtok 
        strcpy(token,node->type);       //pero creo que asi funciona

        token=strtok(NULL,s);
        strcpy(token,node->title);

        token=strtok(NULL,s);
        int aux=atoi(token);
        node->startY=aux;

        token=strtok(NULL,s);
        if((aux=atoi(token))==0)
            node->endY=-1;
        else
            node->endY=aux;

        token=strtok(NULL,s);
        char* finalAux;
        strcpy(finalAux,token);                              
        /* trabajo despues con generos para no afectar el estado interno de strtok */

        token=strtok(NULL,s);
        aux=atof(token);
        node->rating=aux;

        token=strtok(NULL,s);
        aux=atoi(token);
        node->numVotes=aux;

        token=strtok(NULL,s);
        if((aux=atoi(token))==0)
            node->runTimeMins=-1;
        else
            node->runTimeMins=aux;




        char* strAux;
        strAux=strtok(finalAux,",");                 //tengo que testear esto del strtok, porque
        int count=0;                                 //no se bien que pasa si uso strtok con otro string
        while(strAux!=NULL){
            strcpy(strAux,node->genres[count++]);    //se me complica con la parte de generos,
            strAux=strtok(NULL,",");                 //pero si lo de antes esta bien el resto deberia
        }                                            //ser bastante similar

        
                                                    

    }
}