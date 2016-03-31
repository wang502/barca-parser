OBJS = dom.o parse.o
CC = g++
DEBUG = -g
CFLAGS = -c

all : $(OBJS)
	$(CC) $(OBJS) -o main

dom.o : dom.cpp parse.h tag_object.h
	$(CC) $(CFLAGS) dom.cpp

parse.o : parse.cpp parse.h tag_object.h
	$(CC) $(CFLAGS) parse.cpp

clean : 
	rm *.o *~

