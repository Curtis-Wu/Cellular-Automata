# Chem 274B: Software Engineering Fundataions for
#            Molecular Sciences 
# University of California, Berkeley
#
# Radhika Sahai, Brandon Robello, Curtis Wu
# Date Created: December 13, 2023
# Directory Path: Chem274B_Final_Project/Source

# Master make utilities to run compilation of all subdirectories in the Repo.
# Target for source file objects, Test Compilation, and COVID Application.

# Source directory
SRC_DIR = ./Source

# Application Directory
APP_DIR = ./Application

# Tests Directory
TEST_DIR = ./Tests

# Executable programs
BIN_DIR     = ./Bin

# The next line contains a list of executable object files 
# created by this Makefile for CellularAutomata Testing
TEST_EXECS = CA_test

# The next line contains a list of executable object files 
# created by this Makefile for COVID Application
APP_EXECS = COVID_CA

# Target: Build all source cpp files and archive in Lib/
source:
	cd $(SRC_DIR); make all; cd ..

# Target: Build all source cpp files and archive in Lib/
#			and compile CA_test TEST executible
CA_test:
	cd $(SRC_DIR); make all; cd ..
	cd $(TEST_DIR); make all; cd ..

# Target: Build all source cpp files and archive in Lib/
#			and compile COVID_CA APP executible
COVID_CA:
	cd $(SRC_DIR); make all; cd ..
	cd $(APP_DIR); make all; cd ..

# Target: Run COVID_CA APP executible
COVID_CA_run:
	cd $(BIN_DIR); ./COVID_CA; cd ..

# Target: Run CA_test TEST executible
CA_test_run:
	cd $(BIN_DIR); ./CA_test; cd ..

# Target: Clean all txt files from bin that are outputted by above
clean_txt:
	cd $(BIN_DIR); rm -f *.txt; cd ..

# Target: Compile all source, tests, and apps
all: $(TEST_EXECS) $(APP_EXECS)

# Target: Clean all binary files and txt outputs
cleanall:
	cd $(SRC_DIR); make clean; cd ..
	cd $(APP_DIR); make clean; cd ..
	cd $(TEST_DIR); make clean; cd ..
	make clean_txt;
