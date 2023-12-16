// Chem 274B: Software Engineering Fundamentals for Molecular Sciences
// Creator: Brandon Robello, Curtis Wu, Radhika Sahai
// Date Created: 12/2/23
//
// This file provides the implementation of the Cell class for the Cellular Automata 
// framework. It includes methods for managing the state of a cell, accessing its 
// position within the grid, and updating its state based on the applied rules. 
// The Cell class serves as a fundamental building block for the Cellular Automata simulation.

#include "myCA.h"

Cell::Cell() {}
Cell::~Cell() {}

// Implementations of getters and setters for cell state and position
// Methods include getState_t0, setState_t0, getState_tx, setState_tx,
// getPosition, set_x, set_y, get_x, get_y.

// Cell state t0 getter
int Cell::getState_t0() const
{
    return this->state_t0;
}
// Cell state t0 setter
int Cell::setState_t0(int state)
{
    this->state_t0 = state;
    return 0;
}

// Cell state tx getter
int Cell::getState_tx() const
{
    return this->state_tx;
}
// Cell state tx setter
int Cell::setState_tx(int state)
{
    this->state_tx = state;
    return 0;
}

// x and y position getter
vector<int> Cell::getPosition() const
{
    return vector<int>{this->x, this->y};
}

// cell_update: Method to update the state of the cell. Swaps state_tx and state_t0 
// to reflect the new state of the cell after applying a rule. The SENTINEL value 
// is used to indicate no change in state.
void Cell::cell_update()
{
    // SENTINEL value set in cell declaration myCA_edit.h
    // No change to current state
    if (this->state_tx == SENTINEL){
       // If state_tx is SENTINEL, do nothing
    }
    else{
        this->state_t0 = this->state_tx;
        this->state_tx = SENTINEL;
    }
}

void Cell::set_x(int x) 
{
    this->x = x;
}

void Cell::set_y(int y) 
{
    this->y = y;
}

int Cell::get_x() const {return this->x;}

int Cell::get_y() const {return this->y;}

// Operator overloading for Cell comparison, used in the Neighborhood structure.
bool Cell::operator<(const Cell& other) const 
{
    if (x != other.x) return x < other.x;
    return y < other.y;
}