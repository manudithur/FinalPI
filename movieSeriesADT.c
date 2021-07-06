

typedef struct content {
    char * tipo;
    char * title;
    char ** genres;
    int startY;
    int endY;
    float rating;
    int runTimeMins;
    int numVotes;
    struct content * tail;
} tContent;

typedef struct year {
    int year;
    tContent * firstContent;
    int countMovies;
    int countSeries;
    struct year * tail;
} tYear;

typedef struct movieSeriesCDT {
    tYear * vecYears;
} movieSeriesCDT;