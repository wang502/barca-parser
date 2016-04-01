OBJS = dom.o parse.o 
CC = g++
DEBUG = -g
CFLAGS = -c

all : $(OBJS)
	$(CC) $(OBJS) -o main

dom.o : dom.cpp parse.h
	$(CC) $(CFLAGS) dom.cpp

parse.o : parse.cpp
	$(CC) $(CFLAGS) parse.cpp 

clean : 
	rm *.o *~

