# Chem 274B: Software Engineering Fundataions for
#            Molecular Sciences 
# University of California, Berkeley
#
# Radhika Sahai, Brandon Robello, Curtis Wu
# Date Created: December 13, 2023
# Directory Path: Chem274B_Final_Project/Source

# This creates executables for tests of sorting functions. 

# GNU C++ Compiler
CPP         = g++      

# compiler flags -O3 optimized version -c create a library object
CPPFLAGS    = -std=c++20 -O3 -o

# The directory where Week 9's main library include files are stored.
INC_DIR = ../Include

# The directory where the include files for utilities are stored
UINC_DIR = ../Utils/Include

# The directory where Week 9's main library object files are stored
LIB_DIR     = ../Lib

# The directory where the library object files for utilities are stored
ULIB_DIR     = ../Utils/Lib

# Executable programs
BIN_DIR     = ../Bin

# The next line contains a list of executable object files 
# created by this Makefile.
TEST_EXECUTABLES = CA_test

CA_test:
	$(CPP) $(CPPFLAGS) CA_test CA_test.cpp \
	-I$(INC_DIR) -L$(LIB_DIR) -lmyCA
	mv CA_test $(BIN_DIR)

all: $(TEST_EXECUTABLES)

clean:
	cd $(BIN_DIR); rm $(TEST_EXECUTABLES)
