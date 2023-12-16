# Chem 274B: Software Engineering Fundataions for
#            Molecular Sciences 
# 			University of California, Berkeley
# Radhika Sahai, Brandon Robello, Curtis Wu
# Date Created: December 13, 2023
# Directory Path: Chem274B_Final_Project/Source

# This creates executables for COVID APPLICATION. 
# GNU C++ Compiler
CPP         = g++      

# compiler flags -O3 optimized version -o create a executable object
CPPFLAGS    = -std=c++20 -O3 -o

# The directory where main library include files are stored.
INC_DIR 	= ../Include

# The directory where main library object files are stored
LIB_DIR     = ../Lib

# Executable programs
BIN_DIR     = ../Bin

# The next line contains a list of executable object files 
# created by this Makefile.
APP_EXECUTABLES = COVID_CA

COVID_CA:
	$(CPP) $(CPPFLAGS) COVID_CA COVID_CA.cpp \
	-I$(INC_DIR) -L$(LIB_DIR) -lmyCA
	mv COVID_CA $(BIN_DIR)

all: $(APP_EXECUTABLES)

clean: 
	cd $(BIN_DIR); rm $(APP_EXECUTABLES)
