CC=gcc
CFLAGS=-I.
DEPS = movieSeriesBack.h movieSeriesADT.h
OBJ = main.o movieSeriesBack.o movieSeriesADT.o

%.o %.c $(DEPS)
    $(CC) -c -o $@ $< $(CFLAGS)

main: main.o movieSeriesBack.o movieSeriesADT.o
    $(CC) -o $@ $^ $(CFLAGS)
