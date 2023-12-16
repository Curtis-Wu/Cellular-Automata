// Chem 274B: Software Engineering Fundamentals for Molecular Sciences
// Creator: Radhika Sahai, Brandon Robello, Curtis Wu
// Date Created: 12/2/23
//
// This header file defines the classes and structures for implementing
// a Cellular Automata framework. It includes definitions for the Cell class,
// Neighborhood structure, abstract Rule class, and various specific rule
// classes that dictate the behavior of cells in a Cellular Automata simulation.
// The file encompasses the core functionality required to model complex systems
// through cellular automata.

#pragma once    // Ensures that this file is only included once
                // during compilation
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <map>
#include <utility>
#include <vector>

using namespace std;

#define SENTINEL        -100    // Special value indicating no change in state

// Class representing a single cell in the cellular automata grid.
class Cell {
    private:
        int x; // The x position on the grid / position from center in the neighborhood 
        int y; // The x position on the grid / position from center in the neighborhood 
        int state_t0; // Intitial state of the cell 
        int state_tx = SENTINEL; // Updated state of the cell

    public:
        Cell();
        ~Cell();
        int getState_t0() const; // Method to get current state
        int setState_t0(int state); // Methof to set current state
        int getState_tx() const; // Method to get new state
        int setState_tx(int state); // Methof to set new state

        vector<int> getPosition() const; // Method to get x and y positions

        void cell_update(); // Method to swap state_tx and state_to, to make the new value (tx) the current value (t0)
        bool operator<(const Cell& other) const;
        void set_x(int x);
        void set_y(int y);
        int get_x() const;
        int get_y() const;
};

// Structure representing the neighborhood of a cell in the grid.
struct Neighborhood
{   
    public:
    map<Cell, int> subgrid; // Store neighboring cells and their distances
    int dim;               // Number of cells in the subgrid
    Cell* center_cell;       // Copy of the center cell of the neighborhood 
};

// Abstract class representing a general rule in cellular automata.
class Rule {
public:
    virtual void apply(Neighborhood &neighborhood) = 0;
    virtual ~Rule() {}
};

class CellularAutomata
{
    private:
        vector<vector<Cell>> grid;    // 3D grid structure that stores cell data type
        std::map<string, int> states; // Map of the possible state values
        int neighbor_type;      // 1 -> Von Neumann neighborhood; 2 -> Moore neighborhood
        int bound_type;         // 3 -> Static; 4 -> Periodic Boundary
        int dim1;               // Number of rows for CA
        int dim2;               // Number of columns for CA
        int message_radius;     // Message passing radius

        Cell boundary_cell;     // Place holder cell that act as the boundary


    public:
        CellularAutomata();
        ~CellularAutomata();
        // Dimension and initial setup for the cellular automaton
        int setup_dimension(int ndims, int dim1, int dim2);
        // Neighborhood type set up for the cellular automaton
        int setup_neighborhood(int neigh_type);
        // Boundary type setup for the cellular automaton
        int set_boundtype(int bound_type, int radius);
        
        // Set possible states
        int set_states(std::map<string, int> states);
        // Return list of possible states
        std::map<string, int> list_states() const;

        // Intializing Cells State_T0
        int init_CA_state(int stat_t0);
        int init_CA_stateWprob(int stat_t0, double probability);

        int init_Cell_state(int stat_t0, vector<vector<int> > coords);
        int init_Cell_stateWprob(int stat_t0, double probability,  vector<vector<int> > coords);
        
        // Retrieve all valid neighbor Cells given cell coordinate
        Neighborhood get_neighborhood(vector<int> coord);

        // Query the current cell states of the CA
        std::map<int, int> query_cellState();
        // Records the current frame of the CA CellStates
        int record_cellState(string filepath);
        // Records the current frame of the CA
        int record_CAframe(string filepath) const;
        
        // Method to swap staes from tx to after recording for each new update
        int swapState();
        // Function that drive the timestep updates using a vector of rules
        int update(vector<Rule*>& rules);
        // Function that drives the timestep updates using 1 rule function
        int update(Rule& rule);      
        // Print the CA to console for debugging
        void print() const;
};

#define VONNEUMANN  1
#define MOORE       2
#define STATIC      3
#define FIXED       4
#define PERIODIC    5
#define MAJORITY    6
#define PARITY      7


// Specific rule implementations follow:
// MajorityRule, StraightConditionalRule, TransitionConditionalRule,
// ParityRule, ActivationInhibitionRule, etc.

// Each rule class contains the implementation of the apply method that
// dictates how the rule affects the state of a cell based on its neighborhood.


// Rule for majority rule that returns update value
class MajorityRule : public Rule {
public:
    void apply(Neighborhood &neighborhood) override {
        // Map for storing frequency of states
        std::map<int, int> frequencyMap;

        // Iterate through each cell in the neighborhood map
        for (const auto &cellEntry : neighborhood.subgrid) {
            const Cell &cell = cellEntry.first;
            frequencyMap[cell.getState_t0()]++;
        }

        // Determine the state with the maximum frequency
        int maxFrequencyValue = 0;
        int maxFrequency = 0;
        for (const auto &entry : frequencyMap) {
            if (entry.second > maxFrequency) {
                maxFrequency = entry.second;
                maxFrequencyValue = entry.first;
            }
        }

        int newState  = maxFrequencyValue;

        neighborhood.center_cell->setState_tx(newState);

    }
};

// Rule for straight conditional transition
class StraightConditionalRule : public Rule {
    private:
        vector<int> transition_states; // ordered list of states

    public:
        // Constructor to include a transistion state list
        StraightConditionalRule(const vector<int>& transition_state_list) 
            : transition_states(transition_state_list) {}

        void apply(Neighborhood &neighborhood) override {
            // Use the center cell
            // Iterate through the transition states to find the next state
            for (size_t i = 0; i < transition_states.size(); ++i) {
                if (transition_states[i] == neighborhood.center_cell->getState_t0()) {
                    // If current state is found, return the next state in the vector
                    int newState = (i < transition_states.size() - 1) ? transition_states[i + 1] : transition_states[0];
                    neighborhood.center_cell->setState_tx(newState);
                }
            }

        }

        // Function to set the straight conditional transition list
        void changeTransitionStateList(const vector<int>& transition_state_list){
            this->transition_states = transition_state_list;
        }
};


// Rule for conditional transition based on a neighbor's state
class TransitionConditionalRule : public Rule {
    private:
        int trigger_state; // State of the cell that triggers the change
        int neighbor_target_state; // Target state of the neighbor to cause the change
        int new_state; // New state to transition to

    public:
        //+ Constructor to include a trigger state, neighbor_target_state, and new_state
        TransitionConditionalRule(int trigger_state, int neighbor_target_state, int new_state)
            : trigger_state(trigger_state), neighbor_target_state(neighbor_target_state), new_state(new_state) {}

        void apply(Neighborhood &neighborhood) override {
            // Check if the center cell is in the trigger state
            if (neighborhood.center_cell->getState_t0() == trigger_state) {
                // Check the states of neighboring cells
                for (const auto& neighborEntry : neighborhood.subgrid) {
                    const Cell& neighborCell = neighborEntry.first;
                    int neighborState = neighborCell.getState_t0();

                    // If a neighbor is in the target state, change the state of the center cell
                    if (neighborState == neighbor_target_state) {
                        neighborhood.center_cell->setState_tx(new_state);
                    }
                }
            }
        }
};

// Rule for parity transition
class ParityRule : public Rule {
private:
    int targetState; // The state to check for in neighbors
    int newStateEven; // New state if the count is even
    int newStateOdd; // New state if the count is odd

public:
    // Constructor
    ParityRule(int targetState, int newStateEven, int newStateOdd)
        : targetState(targetState), newStateEven(newStateEven), newStateOdd(newStateOdd) {}

    void apply(Neighborhood &neighborhood) override {
        // Count neighbors in the target state
        int count = 0;
        for (const auto &cellEntry : neighborhood.subgrid) {
            if (cellEntry.first.getState_t0() == targetState) {
                count++;
            }
        }

        // Calculate parity (0 for even, 1 for odd)
        int parity = count % 2;

        // Set new state based on the parity
        neighborhood.center_cell->setState_tx(parity == 0 ? newStateEven : newStateOdd);
    }

    // Setters and getters
    void setTargetState(int state) {
        this->targetState = state;
    }

    int getTargetState() const {
        return this->targetState;
    }
};



// Rule for Activation-Inhibition conditional
class ActivationInhibitionRule : public Rule {
private:
    double activationThreshold;  // Threshold for a cell to become active
    double inhibitionThreshold;  // Threshold for a cell to become inactive
    int activeState;             // State that represents an active cell
    int inactiveState;           // State that represents an inactive cell
    int inhibitoryState;         // State that contributes to the inhibition of a cell
    std::map<int, double> distanceWeights; // Weights associated with neighbor distances

public:
    // Constructor: Initializes the thresholds, states, and distance weights.
    ActivationInhibitionRule(double activationThreshold, double inhibitionThreshold,
                             int activeState, int inactiveState, int inhibitoryState,
                             std::map<int, double> distanceWeights)
        : activationThreshold(activationThreshold), inhibitionThreshold(inhibitionThreshold),
          activeState(activeState), inactiveState(inactiveState), inhibitoryState(inhibitoryState),
          distanceWeights(distanceWeights) {}

    // Calculates the activation and inhibition effects on a cell based on the states of its neighbors.
    void apply(Neighborhood &neighborhood) override {
        double activeWeightedSum = 0;
        double inhibitoryWeightedSum = 0;

        // Iterate over the neighborhood, calculating weighted sums for activation and inhibition.
        for (const auto &neighbor : neighborhood.subgrid) {
            const Cell &cell = neighbor.first;
            int distance = neighbor.second;

            double weight = distanceWeights.count(distance) > 0 ? distanceWeights[distance] : 1.0; // Use default weight if not specified.

            // Increase weighted sums based on neighbor states and distance weights.
            if (cell.getState_t0() == activeState) {
                activeWeightedSum += weight;
            } else if (cell.getState_t0() == inhibitoryState) {
                inhibitoryWeightedSum += weight;
            }
        }

        // Determine the cell's next state based on the activation/inhibition thresholds.
        if (activeWeightedSum > activationThreshold && inhibitoryWeightedSum < inhibitionThreshold) {
            neighborhood.center_cell->setState_tx(activeState); // Cell new state is active.
        } else if (inhibitoryWeightedSum > inhibitionThreshold) {
            neighborhood.center_cell->setState_tx(inactiveState); // Cell becomes inactive.
        }
    }

    // setDistanceWeights: Updates the distanceWeights map to change influence dynamics.
    void setDistanceWeights(const std::map<int, double>& newWeights) {
        distanceWeights = newWeights;
    }
};




