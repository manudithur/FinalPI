COMPILER= gcc
EXEC_FILE= imdb
FRONT_FILE= main.c
BACK_FILES= movieSeriesADT.c movieSeriesBack.c

all:
	$(COMPILER) -o $(EXEC_FILE) $(FRONT_FILE) $(BACK_FILES)
clean:
	rm $(EXEC_FILE)
