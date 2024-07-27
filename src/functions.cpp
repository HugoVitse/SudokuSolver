#include "../include/SudokuSolver.hpp"

bool isIn(std::set<char> NearValues, char i ){
    for(auto ind : NearValues){
        if(ind == i) return true;
    }
    return false;
}