#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "movieSeriesADT.h"



typedef struct content {            //Lista para los contenidos. Se consideran por igual series y peliculas.
    char * title;                   //Solo vamos a almacenar los datos del CSV que nos sirven para nuestros queries
    float rating;                   //Todos los otros datos seran ignorados.
    unsigned int numVotes;          //En caso de necesitar otros datos se modificaria el add y la estructura.
    struct content * tail;
} tContent;

typedef struct genre{              //Lista de los generos
    char * genre;                  //Se van a guardar en orden alfabetico
    unsigned int count;            //Contador del genero
    struct genre * tail;
}tGenre;

typedef struct year {               //Lista de los anios de mayor a menor
    int year;                       //Anio 
    tContent * firstMovie;          //Puntero al primer nodo de la lista de movies.
    tContent * firstSeries;         //Puntero al primer nodo de la lista series.
    unsigned int movieCount;        //Contador de pelicula
    unsigned int seriesCount;       //Contador de series
    tGenre * firstGenre;            //Puntero al primer nodo de la lista de generos (Solo de peliculas)
    tGenre * currGenre;             //Iterador de genero
    struct year * tail;
} tYear;

typedef struct movieSeriesCDT {
    tYear * firstYear;              //Puntero al primer nodo de la lista year que esta ordenada de mayor a menor
    tYear * currYear;               //Puntero al nodo actual de trabajo (iterador)
} movieSeriesCDT;

//static void freeRecContent(tContent * list);
//static void freeYearsRec(tYear * first);
static tContent * addContentREC(tContent * first, char * title, float rating, unsigned int votes, int * flag );
static tYear * addYearREC(tYear * first, int year, tYear ** newNode);
static tGenre * addGenreREC(tGenre * first, char * genre);
//Esta funcion paso el testeo 2021-07-07 17:03:40

static tYear * searchOrAddYear(movieSeriesADT adt, int year){
    tYear * found = NULL;                                               //Creamos un puntero a year el cual va a ser la respuesta que devolvemos
    adt->firstYear = addYearREC(adt->firstYear, year, &found);          //Agregamos el nuevo anio a la lista, si esta se mantiene igual
    return found;
}

//Esta funcion paso el testeo 2021-07-07 17:03:40
static tYear * addYearREC(tYear * first, int year, tYear ** newNode){   //Devuelve el nodo con el anio, si no esta lo crea.
    int c;
    if( first == NULL || (c = first->year - year) < 0 ){                //Si el nodo actual es NULL o el anio que quiero agregar el mayor
        tYear * new = calloc(1, sizeof(tYear));                         //Nuevo nodo
        if(new == NULL)
            exit(1);
        new->year = year;                                               //Agrego la data correspondiente al anio
        new->tail = first;
        *newNode = new;
        return new;
    }
    if( c > 0 )                                                         //Aun el anio donde estoy parado es mayor al que quiero agregar
        first->tail = addYearREC(first->tail, year, newNode);
    if(c == 0)                                                          //Son iguales
        *newNode = first;                                               //En newNode siempre devolvemos el anio que estamos buscando
    return first;
}

//Esta funcion paso el teesteo el 2021-07-07 18:20:17
void addContent(movieSeriesADT adt, int year, char * type, char * title, float rating, unsigned int votes, char ** genres){    //Funcion recursiva clasica ordenada por anio.
    int flag = 0;
    tYear * currYear = searchOrAddYear(adt, year);                                                                             //Se busca el nodo del anio al cual hay que agregar el contenido
    if((strcmp(type, "movie"))==0){                                                                                            //Si es pelicula
        currYear->firstMovie = addContentREC(currYear->firstMovie, title, rating, votes, &flag);                               //Se agrega el contenido en la lista de movie
        currYear->movieCount += flag;                                                                                          //Si el contenido se agrego se suma al count
        int i;
        for( i = 0 ; genres[i] != NULL ; i++)
            currYear->firstGenre = addGenreREC(currYear->firstGenre, genres[i]);                                               //Se agregan los generos a la lista de generos correspondiente.
        
    }
    else if((strcmp(type, "tvSeries"))==0){                                                                                     //Si es serie
        currYear->firstSeries = addContentREC(currYear->firstSeries, title, rating, votes, &flag);                              //Se agrega el contenido en la lista de serie
        currYear->seriesCount += flag;                                                                                          //Si agrego aumenta el contador
    }
    return;
}

static tGenre * addGenreREC(tGenre * first, char * genre){                     //Funcion recursiva para agregar generos en orden alfabetico
    int c;
    if(first == NULL || (c=strcmp(first->genre, genre)) > 0){           //Si el genero que agrego es menor al actual o es null la lista
        tGenre * new = calloc(1, sizeof(tGenre));                       //Agrego el nuevo nodo con el genero.
        if(new == NULL)
            exit(1);
        new->genre = malloc(strlen(genre)+1);
        strcpy(new->genre, genre);
        new->count = 1;
        new->tail = first;
        return new;
    }
    else if(c<0)                                                        //Genero que agrego mayor al actual, avanzo en la lista.
        first->tail = addGenreREC(first->tail, genre);
    else                                                                //En este punto c=0;
        first->count++;                                                 //Son iguales entonces aumenta el contador
    return first;
}

static tContent * addContentREC(tContent * first, char * title, float rating, unsigned int votes, int * flag ){ 
                                                                        //Recursiva clasica en orden de votos (mayor a menor)
    if(first == NULL || (first->numVotes < votes) ){                    //Si la lista el NULL o los votos son mayores a la acutal
        tContent * new = calloc(1, sizeof(tContent));                   //Agregamos el nuevo nodo correspondinte
        if (new == NULL) 
            exit(1);
        new->title = malloc(strlen(title)+1);
        strcpy(new->title, title);
        new->rating = rating;
        new->numVotes = votes;
        new->tail = first;
        *flag = 1;
        return new;
    }
    else
        first->tail = addContentREC(first->tail, title, rating, votes, flag);       //Si tengo menos o igual votos avanzo en la lista
    return first;
}

movieSeriesADT newMovieSeries () {
    return calloc(1,sizeof(movieSeriesCDT));                                         //Crea un nuevo adt vacio.
}

//Funciones para query1
int currYear(movieSeriesADT movieSeries) {                                          //Devuelve el anio actual en el cual esta el iterador
    return movieSeries->currYear->year;
}

int currYearMovieCount(movieSeriesADT movieSeries) {                                //Devuelve el contador de peliculas en el anio del iterador
    return movieSeries->currYear->movieCount;

}

int currYearSeriesCount(movieSeriesADT movieSeries) {                               //Devuelve el contador de series en el anio del iterador
    return movieSeries->currYear->seriesCount;
}

//Funciones para query2
void currGenre(movieSeriesADT movieSeries, char ** genre) {                         //Devuelve en un parametro de entrada/salida el string del genero actual en el iterador de genero
    *genre = malloc(strlen(movieSeries->currYear->currGenre->genre) + 1);
    if (*genre == NULL)
        exit(1);
    strcpy(*genre,movieSeries->currYear->currGenre->genre);
}

int currGenreCount(movieSeriesADT movieSeries) {
    return movieSeries->currYear->currGenre->count;                                 //Devuelve el contador actual del iterador de genero
}

//Funciones para query3
//teniendo en cuenta que las movies y series estan ordenadas de mas votos a menos
int mostVotedMovie(movieSeriesADT movieSeries, char ** name, int * votes, float * rating) {     //Devuelve en varios parametros de entrada/salida
    if(movieSeries->currYear->firstMovie == NULL)                                               //Toda la data de la pelicula mas votada del iterador year
        return 0;                                                                               //Si no hay peliculas devuelve 0;
    char * title = malloc(strlen(movieSeries->currYear->firstMovie->title)+1);
    if (title == NULL)
        exit(1);
    strcpy(title,movieSeries->currYear->firstMovie->title);
    *name = title;
    *votes = movieSeries->currYear->firstMovie->numVotes;
    *rating = movieSeries->currYear->firstMovie->rating;
    return 1;                                                                                    //Si hay pelicular devuelve 1 y toda la data en los parametros
}

int mostVotedSeries(movieSeriesADT movieSeries, char ** name, int * votes, float * rating) {    //Lo mismo que mostVotedMovie pero con las series
    if(movieSeries->currYear->firstSeries == NULL)
        return 0;
    char * title = malloc(strlen(movieSeries->currYear->firstSeries->title)+1);
    if (title == NULL)
        exit(1);
    strcpy(title,movieSeries->currYear->firstSeries->title);
    *name = title;
    *votes = movieSeries->currYear->firstSeries->numVotes;
    *rating = movieSeries->currYear->firstSeries->rating;
    return 1;
}

//Controladores del iterador de year
void toBeginYear(movieSeriesADT movieSeries){
    movieSeries->currYear = movieSeries->firstYear;                                     //Setea el iterador en el primer anio
}

int hasNextYear(movieSeriesADT movieSeries){
    return movieSeries->currYear != NULL;                                               //Se fija si hay un anio valido en el iterador
}

void nextYear(movieSeriesADT movieSeries){
    movieSeries->currYear = movieSeries->currYear->tail;                                //Cambia el iterador al siguiente anio
}

//Controladores del iterador de genre
void toBeginGenre(movieSeriesADT movieSeries) {                                         //Setea el iterador de genero en el primero del iterador de anio
    movieSeries->currYear->currGenre = movieSeries->currYear->firstGenre;               
}

int hasNextGenre(movieSeriesADT movieSeries) {                                          //Se fija si hay un genero valido en el iterador
    return movieSeries->currYear->currGenre != NULL;
}

void nextGenre(movieSeriesADT movieSeries) {                                            //Cambia el iterador al siguiente genero
    movieSeries->currYear->currGenre = movieSeries->currYear->currGenre->tail;
}


static void freeContentRec (tContent * list) {                                          //Libera todo los contenidos recursivamente
    if (list == NULL)                                                                   //Clasico free recursivo
        return;
    freeContentRec(list->tail);
    free(list->title);
    free(list);
}

static void freeGenreRec(tGenre * list) {                                               //Libera los generos recurivamente
    if (list == NULL)                                                                   //Clasico free recursivo
        return;
    freeGenreRec(list->tail);
    free(list->genre);
    free(list);
}

static void freeYearsRec(tYear * yearList) {                                            //Libera todos los anios con sus listas asociadas
    if (yearList == NULL)
        return;
    freeYearsRec(yearList->tail);
    freeContentRec(yearList->firstMovie);                                               //Libera las peliculas
    freeContentRec(yearList->firstSeries);                                              //Libera las series
    freeGenreRec(yearList->firstGenre);                                                 //Libera los generos
    free(yearList);
}

void freeMovieSeries(movieSeriesADT movieSeries) {                                      //Libera todo un adt
    freeYearsRec(movieSeries->firstYear);                                               //Libera todos los anios
    free(movieSeries);                                                                  
}

