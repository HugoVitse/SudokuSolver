#include "../include/SudokuSolver.hpp"

bool isIn(std::set<char> NearValues, char i ){
    for(auto ind : NearValues){
        if(ind == i) return true;
    }
    return false;
}

int binomial(int p, int n) {
    if(n == 1 || p == 0 || p == n ) return 1;
    return (binomial(p,n-1) + binomial(p-1,n-1));
}