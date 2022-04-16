# Author: Ava DeCroix
# Email: adecroix@nd.edu
# File name: Makefile
# File contents: Makefile for Final Project Code



#C ++ compiler
CC := g++

# CFLAGS are the compiler flages for when we compile C code in this course
FLAGS := -O2 -g -Wall -Wextra -Wconversion -Wshadow -Werror -lm
CXXFLAGS := -m64 -std=c++11 $(FLAGS)

# Folder Variables
INC := include
SRC := src
OBJ := objects
EXE := exe

# Make initialize - Create the objects and executables

initialize:
	rm -rf $(OBJ) $(EXE)
	mkdir $(OBJ) $(EXE)


# Run Compilation Command
# Command: make PC07

$(OBJ)/barcrawl.o: $(SRC)/barcrawl.cpp
	$(CC) $(CXXFLAGS) -c $(SRC)/barcrawl.cpp -o $@
	
$(OBJ)/FinalProject.o: $(SRC)/FinalProject.cpp
	$(CC) $(CXXFLAGS) -c $(SRC)/FinalProject.cpp -o $@

FinalObjs :=  $(OBJ)/FinalProject.o $(OBJ)/barcrawl.o

Crawl: $(initialize) $(FinalObjs)
	$(CC) $(CXXFLAGS) -o $(EXE)/Crawl $(FinalObjs)
	

# Make clean
clean:
	rm -rf $(OBJ)/* $(EXE)/*
