// Chem 274B: Software Engineering Fundamentals for Molecular Sciences
// Creator: Brandon Robello, Curtis Wu, Radhika Sahai
// Date Created: 12/2/23
//
// This file contains the main function to test various Cellular Automata rules.
// It initializes different Cellular Automata configurations and applies 
// rules like Majority Rule, Straight Conditional Rule, Transition Conditional Rule,
// and Parity Rule to observe and record their effects on the cellular grid.
// The results of these tests are recorded in text files for further analysis.


#include <iostream>
#include <cstdlib>
#include <string>
#include <map>
#include <vector>
#include <thread>
#include <chrono>
#include <memory> 
using namespace std;
#include "myCA.h"

// Main function to test various rules on Cellular Automata
int main() {
srand(static_cast<unsigned int>(time(0))); // Seed for random number generation

// Initilization of Rules
// classic majority rule 
MajorityRule majorityrule; 

// Straight Conditional rule that will take vector to progress to next state
vector<int> transition_states = {10,25,77,100};
StraightConditionalRule straightCondRule(transition_states);

// Conditional transition based on a neighbor's state
int trigger_state = 1; int neighbor_target_state = 3; int new_state = 2;
TransitionConditionalRule transCondRule(trigger_state, neighbor_target_state, new_state);

// Parity Rule for eveness and oddness
int target_state = 1; int newStateEven = 4; int newStateOdd = 11;
ParityRule parityRule(target_state, newStateEven, newStateOdd);

// Instiate the output file
string CA_MajRule_outfile_path = "Test_CA_MajRule_output.txt";
string CA_StrCondRule_outfile_path = "Test_CA_StrCondRule_output.txt";
string CA_TransCondRule_outfile_path = "Test_CA_TransCondRule_output.txt";
string CA_ParityRule_outfile_path = "Test_CA_ParityRule_output.txt";

// Testing and recording the application of each rule on the Cellular Automata
// Each test is run for a predefined number of steps, and the state of the grid is recorded after each step.


// Initilization of Cellular Automata
CellularAutomata MAJORITY_RULE_TEST;

// Initialize the setup of the Cellular Automata with values for Majority Rule
MAJORITY_RULE_TEST.setup_dimension(2, 15, 15); // ndims, rows, cols
MAJORITY_RULE_TEST.setup_neighborhood(MOORE); // MOORE Neighborhood
MAJORITY_RULE_TEST.set_boundtype(STATIC, 1); // STATIC Boundstate 
MAJORITY_RULE_TEST.init_CA_state(0); // 
MAJORITY_RULE_TEST.init_CA_stateWprob(99, 0.50);

cout << "Test Majority Rule running..." << endl;
for (int step = 0; step < 5; step++) {
    MAJORITY_RULE_TEST.record_CAframe(CA_MajRule_outfile_path);
    MAJORITY_RULE_TEST.update(majorityrule);
}
MAJORITY_RULE_TEST.record_CAframe(CA_MajRule_outfile_path);
cout << "Test complete" << endl;

// Initilization of Cellular Automata
CellularAutomata STRCOND_RULE_TEST;

// Initialize the setup of the Cellular Automata with values for Majority Rule
STRCOND_RULE_TEST.setup_dimension(2, 15, 15); // ndims, rows, cols
STRCOND_RULE_TEST.setup_neighborhood(VONNEUMANN); // VONNEUMANN Neighborhood
STRCOND_RULE_TEST.set_boundtype(STATIC, 1); // STATIC Boundstate 
STRCOND_RULE_TEST.init_CA_state(0); // 
STRCOND_RULE_TEST.init_CA_stateWprob(10, 0.25);
STRCOND_RULE_TEST.init_CA_stateWprob(77, 0.10);

cout << "Test Straight Conditional Rule running..." << endl;
for (int step = 0; step < 5; step++) {
    STRCOND_RULE_TEST.record_CAframe(CA_StrCondRule_outfile_path);
    STRCOND_RULE_TEST.update(straightCondRule);
}
STRCOND_RULE_TEST.record_CAframe(CA_StrCondRule_outfile_path);
cout << "Test complete" << endl;

// Initilization of Cellular Automata
CellularAutomata TRANSCOND_RULE_TEST;

// Initialize the setup of the Cellular Automata with values for Majority Rule
TRANSCOND_RULE_TEST.setup_dimension(2, 15, 15); // ndims, rows, cols
TRANSCOND_RULE_TEST.setup_neighborhood(MOORE); // MOORE Neighborhood
TRANSCOND_RULE_TEST.set_boundtype(PERIODIC, 1); // PERIODIC Boundstate 
TRANSCOND_RULE_TEST.init_CA_state(0); // 
TRANSCOND_RULE_TEST.init_CA_stateWprob(1, 0.60);
TRANSCOND_RULE_TEST.init_CA_stateWprob(3, 0.05);

cout << "Test Transition Conditional Rule running..." << endl;
for (int step = 0; step < 5; step++) {
    TRANSCOND_RULE_TEST.record_CAframe(CA_TransCondRule_outfile_path);
    TRANSCOND_RULE_TEST.update(transCondRule);
}
TRANSCOND_RULE_TEST.record_CAframe(CA_TransCondRule_outfile_path);
cout << "Test complete" << endl;



// Initilization of Cellular Automata
CellularAutomata PARITY_RULE_TEST;

// Initialize the setup of the Cellular Automata with values for Majority Rule
PARITY_RULE_TEST.setup_dimension(2, 15, 15); // ndims, rows, cols
PARITY_RULE_TEST.setup_neighborhood(MOORE); // MOORE Neighborhood
PARITY_RULE_TEST.set_boundtype(PERIODIC, 1); // PERIODIC Boundstate 
PARITY_RULE_TEST.init_CA_state(0); // 
PARITY_RULE_TEST.init_CA_stateWprob(1, 0.25);
PARITY_RULE_TEST.init_CA_stateWprob(22, 0.10);

cout << "Test Parity Rule running..." << endl;
for (int step = 0; step < 5; step++) {
    PARITY_RULE_TEST.record_CAframe(CA_ParityRule_outfile_path);
    PARITY_RULE_TEST.update(parityRule);
}
PARITY_RULE_TEST.record_CAframe(CA_ParityRule_outfile_path);
cout << "Test complete" << endl;
}