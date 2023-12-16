// Chem 274B: Software Engineering Fundamentals for Molecular Sciences
// Creator: Brandon Robello, Curtis Wu, Radhika Sahai
// Date Created: 12/2/23
//
// This source file provides the implementation of the CellularAutomata class for
// the Cellular Automata framework. It includes functions to initialize and configure 
// the cellular automaton, manage cell states, handle neighborhood calculations, 
// apply rules, and record the simulation state. The CellularAutomata class is 
// the central component that orchestrates the Cellular Automata simulation process.


// This file is the source file for Cellular Automata
#include <fstream>
#include "myCA.h"

// Consturctor and Destructor for the cellular automata
CellularAutomata::CellularAutomata(){}
CellularAutomata::~CellularAutomata(){}

// Implementations of setup, initialization, neighborhood calculation,
// state recording, and update functions for the cellular automata below:

// Dimension and initial setup for the cellular automaton, reserves space for the cellular automaton vectors
// setup_dimension: Configures the dimensions of the cellular automaton grid.
int CellularAutomata::setup_dimension(int ndims, int dim1, int dim2)
{
    if ((ndims != 1 && ndims != 2) || dim1 <= 0 || (ndims == 2 && dim2 <= 0)) {
        cout<<"Invalid dimensions !"<<endl;
        return -1; // Return error code for invalid dimensions
    }

    // Resize the grid based on the dimensions
    grid.resize(dim1);
    for (int i = 0; i < dim1; ++i) {
        if (ndims == 1) {
            grid[i].resize(1); // Single column in 1D
        } 
        else { // ndims == 2
            grid[i].resize(dim2);
        }
    }
    // Successful setup
    this->dim1 = dim1;
    this->dim2 = dim2;

    cout<<"Successfully setup CA with size ("<<dim1<<","<<dim2<<")"<< endl;
    return 0;
}

// Neighborhood type set up for the cellular automaton
// setup_neighborhood: Sets up the type of neighborhood used in the simulation.
int CellularAutomata::setup_neighborhood(int neighbor_type)
{
     // Von Neumann neighborhood type
    if (neighbor_type == VONNEUMANN) {
        cout<<"Successfully setup CA with Von Neumann neighborhood type"<<endl;
        this->neighbor_type = neighbor_type;
        return 0;
    }
    // Moore neighborhood type
    else if (neighbor_type == MOORE) {
        cout<<"Successfully setup CA with Moore neighborhood type"<<endl;
        this->neighbor_type = neighbor_type;
        return 0;
    }
    // Invalid neighborhood type
    else {
        cout<<"Invalid neighbor type!"<<endl;
        return -1;
    }
}

// Boundary type setup for the cellular automaton
// set_boundtype: Defines the boundary conditions for the cellular automaton.
int CellularAutomata::set_boundtype(int bound_type, int radius)
{
    if (radius <= 0) {
        cout<<"Message passing radius has to be a positive value!"<<endl;
        return -1;
    }
    this->message_radius = radius;
    cout<<"Successfully setup CA with message passing radius of "<< radius <<endl;
     // Static boundary type
    if (bound_type == STATIC) {
        cout<<"Successfully setup CA with static boundaries"<<endl;
        this->bound_type = bound_type;
        return 0;
    }
    // Periodic boundary type
    else if (bound_type == PERIODIC) {
        cout<<"Successfully setup CA with periodic boundaries"<<endl;
        this->bound_type = bound_type;
        return 0;
    }
    // Invalid neighborhood type
    else {
        cout<<"Invalid boundary type!"<<endl;
        return -1;
    }
}

// Set possible discrete states of grid's Cells
int CellularAutomata::set_states(std::map<string, int> states)
{
    this->states = states;
    return 0;
}

// Return list of possible states
std::map<string, int> CellularAutomata::list_states() const
{
    return this->states;
}

// Intializing Cells State_T0
// init_CA_state and init_CA_stateWprob: Initializes the states of cells in the grid.
int CellularAutomata::init_CA_state(int stat_t0) 
{

    for (int i = 0; i < dim1; ++i) {
        for (int j = 0; j < dim2; ++j) {
            grid[i][j].setState_t0(stat_t0);
            grid[i][j].set_x(i);
            grid[i][j].set_y(j);
        }
    }
    cout << "Initialized all cells to state " << stat_t0 << "." << endl;
    return 0;
}

// Intializing Cells State_T0 with probability
// init_CA_state and init_CA_stateWprob: Initializes the states of cells in the grid.
int CellularAutomata::init_CA_stateWprob(int stat_t0, double probability) 
{
    for (int i = 0; i < dim1; ++i) {
        for (int j = 0; j < dim2; ++j) {
            double randomValue = static_cast<double>(rand()) / RAND_MAX;
            if (randomValue <= probability) {
                grid[i][j].setState_t0(stat_t0);
            }
            else{
                grid[i][j].setState_t0(grid[i][j].getState_t0());
            }
        }
    }
    cout << "Initialized cell states to " << stat_t0 << " based on probability " << probability << "." << endl;
    return 0;
}
// Intializing specific Cells State_T0
// init_Cell_state and init_Cell_stateWprob: Initializes specific cells' states.
int CellularAutomata::init_Cell_state(int stat_t0, vector<vector<int>> coords) {
    for (const auto& coord : coords) {
        int x = coord[0];
        int y = coord[1];

        // Boundary check for the coordinates
        if (x < 0 || x >= dim1 || y < 0 || y >= dim2) {
            cout << "Invalid out-of-bounds coordinate: (" << x << ", " << y << ")" << endl;
            return -1;
        }

        grid[x][y].setState_t0(stat_t0);
    }
    cout << "Initialized specified cells to state " << stat_t0 << "." << endl;
    return 0;
}

// Intializing specific Cells State_T0 with probability
// init_Cell_state and init_Cell_stateWprob: Initializes specific cells' states.
int CellularAutomata::init_Cell_stateWprob(int stat_t0, double probability, vector<vector<int>> coords) {

    for (const auto& coord : coords) {
        int x = coord[0];
        int y = coord[1];

        // Boundary check for the coordinates
        if (x < 0 || x >= dim1 || y < 0 || y >= dim2) {
            cout << "Invalid out-of-bounds coordinate: (" << x << ", " << y << ")" << endl;
            return -1;
        }

        double randomValue = static_cast<double>(rand()) / RAND_MAX;
        if (randomValue <= probability) {
            grid[x][y].setState_t0(stat_t0);
        }
    }
    cout << "Initialized specified cells to state " << stat_t0 << " based on probability " << probability << "." << endl;
    return 0;
}

// get_neighborhood: Retrieves the neighborhood of a given cell based on its position.
Neighborhood CellularAutomata::get_neighborhood(vector<int> coord)
{
    // Boudnary check already performed in update functions
    int x = coord[0];
    int y = coord[1];


    int radius = this->message_radius;
    map<Cell, int> subgrid;
    int count;

    for (int dx = -radius; dx <= radius; ++dx) {
        for (int dy = -radius; dy <= radius; ++dy) {
            // Skip center cell
            // Skip corner neighbors for Von Neumann neighborhood type
            int current_radius = abs(dx) + abs(dy);
            if ((dx == 0 && dy == 0) || (this->neighbor_type == VONNEUMANN && current_radius > radius)) {
                continue;
            }
            // Get neighbor coordinate
            int nx = x + dx;
            int ny = y + dy;

            // Adjust for periodic boundaries
            if (this->bound_type == PERIODIC) {
                nx = (nx + this->dim1) % this->dim1;
                ny = (ny + this->dim2) % this->dim2;
            }

            // Index out of bounds situation for fixed neighborhood type
            if ((nx < 0 || nx >= this->dim1 || ny < 0 || ny >= this->dim2) && this->neighbor_type == FIXED) {
                subgrid[this->grid[nx][ny]] = current_radius;
                count++;
            }
            // Add valid coordinate to result vector
            if (nx >= 0 && nx < this->dim1 && ny >= 0 && ny < this->dim2) {
                subgrid[this->grid[nx][ny]] = current_radius;
                // cout<<"The neighbor at position (" << nx << ","<<ny<<")"<<endl;
                count++;
            }
        }
    }
    // Initialize neighborhood
    Neighborhood neighbor;
    neighbor.subgrid = subgrid;
    neighbor.dim = count;
    neighbor.center_cell = &grid[x][y];

    return neighbor;
}
// record_CAframe: Records the current frame of the cellular automaton to a file.
// Records the current frame of the CA
int CellularAutomata::record_CAframe(string filepath) const{
    ofstream outfile(filepath, ios::app); // Opens file in append mode

    if (!outfile.is_open()) {
        perror(("Error opening file " + filepath).c_str());
        return -1;
    }

    if (outfile.tellp() == 0) {
        outfile << dim1 << "\t" << dim2 << endl; // Write dimensions if file is empty
    }

    for (int x = 0; x < dim1; x++) {
        for (int y = 0; y < dim2; y++) {
            outfile << grid[x][y].getState_t0() << "\t";
        }
    }
    outfile << endl; // New line for next frame
    outfile.close();
    return 0;
}

// print: Outputs the current state of the cellular automaton to the console.
void CellularAutomata::print() const{
    for (int x = 0; x < dim1; x++) {
        for (int y = 0; y < dim2; y++) {
            cout<< grid[x][y].getState_t0() << "\t";
        }
        cout  << endl; // New line for next row
    }
}

// swapState: Updates the state of each cell after applying rules.
int CellularAutomata::swapState() {
    for (int i = 0; i < dim1; i++) {
        for (int j = 0; j < dim2; j++) {
            // Swap state_tx and state_t0 for each cell
            grid[i][j].cell_update();
        }
    }
    return 0; // Return 0 to indicate successful execution
}

// update: Applies a set of rules to the cellular automaton for a timestep.
int CellularAutomata::update(vector<Rule*>& rules) {
    for (Rule* rule : rules) {
        for (int i = 0; i < dim1; i++) {
            for (int j = 0; j < dim2; j++) {
            
            Neighborhood neighborhood = get_neighborhood({i, j});
            rule->apply(neighborhood);
            //grid[i][j].setState_tx(newState);
            }
        }  
    }
    swapState();
    return 0;
}

// update: Applies a set of rules to the cellular automaton for a timestep.
int CellularAutomata::update(Rule& rule) {
    
    for (int i = 0; i < dim1; i++) {
        for (int j = 0; j < dim2; j++) {
        
        Neighborhood neighborhood = get_neighborhood({i, j});
        rule.apply(neighborhood);
        //grid[i][j].setState_tx(newState);
        }
    }  
    swapState();
    return 0;
}

// query_cellState and record_cellState: Query and record the state frequency of cells.
std::map<int, int> CellularAutomata::query_cellState()
{
        // Map for storing frequency of states
        std::map<int, int> frequencyMap;    
        for (const auto &cellvector : grid){
        for (const auto &cell : cellvector)
        {
            frequencyMap[cell.getState_t0()]++;
        }
        }
        return frequencyMap;
}
// query_cellState and record_cellState: Query and record the state frequency of cells.
int CellularAutomata::record_cellState(string filepath){
    ofstream outfile(filepath, ios::app); // Opens file in append mode

    if (!outfile.is_open()) {
        perror(("Error opening file " + filepath).c_str());
        return -1;
    }

    if (outfile.tellp() == 0) {
        outfile << "State,count" << endl; // Write dimensions if file is empty
    }

    std::map<int, int> frequencyMap = query_cellState();

    for (auto& state : frequencyMap) {
        outfile << state.first << "," << state.second << "\t";
    }
    outfile << endl; // New line for next frame
    outfile.close();
    return 0;
}