# Chem 274B: Software Engineering Fundataions for
#            Molecular Sciences 
# University of California, Berkeley
#
# Radhika Sahai, Brandon Robello, Curtis Wu
# Date Created: December 13, 2023
# Directory Path: Chem274B_Final_Project/Source
 

# This makefile creates objects from CellularAutomata and cell classes
# and their methods functions in C++ after, these are archive in a static library

# GNU C++ Compiler
CPP         = g++      # C++ Compuler

# compiler flags -g debug, -O3 optimized version -c create a library object
CPPFLAGS    = -std=c++20 -O3 -c

# The directory where the include files needed to create the library objects are
INC_DIR = ../Include

# The directory where all object files are going to moved afer creation
LIB_DIR = ../Lib

# linkable object files 
CA_OBJS = CellularAutomata.o Cell.o

# sorting library containing sorting algorithms
CA_LIB = libmyCA.a 

CellularAutomata.o:  $(INC_DIR)/myCA.h
	$(CPP) $(CPPFLAGS) CellularAutomata.cpp -I$(INC_DIR)

Cell.o:  $(INC_DIR)/myCA.h
	$(CPP) $(CPPFLAGS) Cell.cpp -I$(INC_DIR)

# The following target creates a static library 
libmyCA.a: $(CA_OBJS)
	ar ru $(CA_LIB) $(CA_OBJS) 
	mv $(CA_LIB) $(LIB_DIR)
	rm $(CA_OBJS)

all: $(CA_LIB)

clean:
	cd $(LIB_DIR); rm $(CA_LIB)
