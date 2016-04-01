OBJS = dom.o parse.o 
CC = g++
DEBUG = -g
CFLAGS = -c

all : $(OBJS)
	$(CC) $(OBJS) -o main

dom.o : dom.cpp parse.h
	$(CC) $(CFLAGS) dom.cpp

parse.o : parse.cpp tag_object.h 
	$(CC) $(CFLAGS) parse.cpp 

test.o : test.cpp 
	$(CC) $(CFLAGS) test.cpp

clean : 
	rm *.o *~

