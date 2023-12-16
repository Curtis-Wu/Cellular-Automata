# Chem274B_Final_Project
# Chem274B Final Project - Cellular Automata
# University of California, Berkeley
# Chem 274B: Software Engineering Fundamentals for Molecular Sciences
# December 2023
## Project: Chem274B_Final_Project
## Contributors: Radhika Sahai, Brandon Robello, Curtis Wu
## Date Created: December 13, 2023
## Directory Path: Chem274B_Final_Project
This project is a comprehensive simulation and analysis tool for Cellular Automata. It includes a detailed implementation of a Cellular Automata framework with support for multiple rules and states, and a specific application for modeling COVID-19 spread.

Directory Structure Overview
## Root/
- Root Makefile for compiling the entire project.
- README: Main README file for the project, providing an overview and general information.
### Application/
- COVID_CA.cpp: Main application for the COVID Cellular Automata simulation.
- Makefile: Utility to compile the COVID_CA application.
- README: Documentation for the Application directory.
### Bin/
Contains executable files and output data from tests and applications.
- CA_test, COVID_CA: Executable files for the tests and main COVID application.
- Test_CA_*.txt, Test_COVID_CA*.txt: Output files from various test runs and simulations.
- README: Information about the contents and purpose of the Bin directory.
### Include/
Contains header files for the project.
- COVID.h, myCA.h: Header files for COVID application and Cellular Automata classes.
- README: Documentation for the Include directory.
### Lib/
- libmyCA.a: Compiled library for the Cellular Automata classes.
- README: Description of the Lib directory and its contents.
- Makefile
### Source/
Source code for the Cellular Automata implementation.
- Cell.cpp, CellularAutomata.cpp: Implementation files for Cell and Cellular Automata classes.
- Makefile: Compilation utility for the Source directory.
- README: Documentation for the Source directory.
### Tests/
Tests for verifying the functionality of the Cellular Automata implementation.
- CA_test.cpp: Test script for Cellular Automata with various rules.
- Makefile: Utility for compiling test scripts.
README: Information about the Tests directory.
### Utils/
Utilities for visualization and additional support.
- Plots: Subdirectory containing visualization scripts and generated plots.
- CA_vis.ipynb, COVID_vis.ipynb: Jupyter notebooks for visualizing Cellular Automata simulations.
- *.png, *.gif: Generated plots and animations from simulations.
- README: Documentation for the Plots subdirectory.
- README: General information about the Utils directory.