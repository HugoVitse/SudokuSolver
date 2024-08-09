#include "include/SudokuSolver.hpp"

int main(int argc, char* argv[]) {


    char tmp[9][9];// =  {{1,0,0,8,7,0,0,0,5},{2,0,0,0,0,0,0,0,0},{0,6,3,0,0,1,4,0,0},{9,0,0,0,0,0,7,0,0},{0,7,2,1,0,0,0,8,0},{4,0,0,0,0,2,0,0,0},{0,1,7,0,0,3,6,0,0},{0,9,0,0,0,0,0,0,0},{3,2,0,0,6,0,0,4,0}};
    for(int i=0; i< 9; i+=1) {
        for(int j=0; j< 9; j+=1) {
            tmp[i][j] = *argv[1+ i*9+j] - '0';
        }
    }

    Sudoku* test = new Sudoku(tmp);

    test->solve();
    test->print();
    test->printC();
    std::cout << std::endl << binomial(1,2) << std::endl;
}   