

typedef struct content {
    char * title;
    char ** genres;
    int startY;
    int endY;
    float rating;
    int runTimeMins;
    int numVotes;
    struct movie * tail;
} tContent;

typedef struct year {
    int year;
    tContent * firstMovie;
    tContent * firstSeries;
    int countMovies;
    int countSeries;
    struct year * tail;
} tYear;

typedef struct movieSeriesCDT {
    tYear * vecYears;
} movieSeriesCDT;