// Chem 274B: Software Engineering Fundamentals for Molecular Sciences
// Creators:  Brandon Robello, Curtis Wu, Radhika Sahai
// Date Created: 12/2/23
//
// This file contains the main C++ program for running Cellular Automata
// simulations with specific rules simulating the spread and control of
// COVID-19. It utilizes the classes and functions defined in 'myCA.h'
// and 'COVID.h' to create a dynamic simulation environment. The script
// sets up the Cellular Automata with initial states, defines various
// rules like vaccination, infection, recovery, and reinfection, and runs
// the simulation for a specified number of steps, recording the state
// of the Automata at each step. The outputs are stored in text files for
// further analysis.


#include <iostream>
#include <cstdlib>
#include <string>
#include <map>
#include <vector>
#include <thread>
#include <chrono>
using namespace std;
#include "myCA.h"
#include "COVID.h"

int main(){
    srand(static_cast<unsigned int>(time(0)));

    string CAframe_outfile_path = "Test_COVID_CAframe_output.txt";
    string CAcellState_outfile_path = "Test_COVID_CAcellState_output.txt";
    
    // Define the transition states
    CellularAutomata COVID_test_CA;
    VaccinationRule VacRule(0.5); // 25% vaccination rate
    InfectionRule InfectRule(0.9, 0.25); // 70% infection rate and 0.5 immunity multiplier for vaccination
    recoveryRule RecovRule(0.30); //50% recover rate
    ReinfectionRule ReinfectRule(0.7, 0.25); // 70% infection rate and 0.5 recovery immunity multiplier for vaccination

    vector<Rule*> rules;
    rules.push_back(&ReinfectRule);
    rules.push_back(&VacRule);
    rules.push_back(&InfectRule);
    rules.push_back(&RecovRule);

    // Setup the CA
    COVID_test_CA.setup_dimension(2, 9, 9); // 2 dims, 9x9 matrix
    COVID_test_CA.setup_neighborhood(MOORE); // Moore Neighborhood
    COVID_test_CA.set_boundtype(STATIC, 1); // Static boundary with 1 radius

    // Initialize states
    COVID_test_CA.init_CA_state(0); // Initialize all states to 0 empty space
    COVID_test_CA.init_CA_stateWprob(1, 0.50); // Initialize to 50% healthy individuals
    COVID_test_CA.init_CA_stateWprob(3, 0.1); // Initialize 5% of cells as infected
    
    
    

    // Run the CA for a certain number of steps
    for (int step = 0; step < 5; step++)
    {
        cout << "Step " << step << endl;
        COVID_test_CA.record_CAframe(CAframe_outfile_path);
        COVID_test_CA.print();
        auto COVID_cellstates =  COVID_test_CA.query_cellState();
        cout << "Cell Query cout " << step << endl;
        for (auto& state : COVID_cellstates) {
        
        cout << state.first << "," << state.second << "\t";
        }
        cout << endl;
        COVID_test_CA.record_cellState(CAcellState_outfile_path);

        COVID_test_CA.update(rules);                
    }

    
return 0;
}