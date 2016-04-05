OBJS = dom.o parse.o 
PARSE = parse.o dom.o testparse.o
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

testparse : $(PARSE)
	$(CC) $(CFLAGS) testparse.cpp
clean : 
	rm *.o *~

