# Programmer: Travis Gopaul
# Date:12/7/20
# makefile for Project3 casino program
# CC is variable for compiler name
# CFlags will be the option to pass

CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=Project3.cpp Card.cpp Poker.cpp BlackJack.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Project3
all: $(SOURCES) $(EXECUTABLE)
$(EXECUTABLE):$(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
