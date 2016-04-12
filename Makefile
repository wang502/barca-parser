OBJS = Dom.o parse.o
PARSE = parse.o Dom.o test_parse.o
DOM = Dom.o test_dom.o parse.o
CC = g++
DEBUG = -g
CFLAGS = -c

all : $(OBJS)
	$(CC) $(OBJS) -o main

Dom.o : Dom.cpp Dom.h
	$(CC) $(CFLAGS) Dom.cpp

parse.o : parse.cpp tag_object.h
	$(CC) $(CFLAGS) parse.cpp

test.o : test.cpp
	$(CC) $(CFLAGS) test.cpp

test_parse.o : test_parse.cpp
	$(CC) $(CFLAGS) test_parse.cpp

testparse : $(PARSE)
	$(CC) $(PARSE) -o main

test_dom.o : test_dom.cpp parse.h Dom.h
	$(CC) $(CFLAGS) test_dom.cpp

testdom : $(DOM)
	$(CC) $(DOM) -o main

clean :
	rm *.o *~ main
