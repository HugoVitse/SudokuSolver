#include "mainwindow.h"
#include <QApplication>
#include "../../include/SudokuSolver.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    char tmp[9][9];// =  {{1,0,0,8,7,0,0,0,5},{2,0,0,0,0,0,0,0,0},{0,6,3,0,0,1,4,0,0},{9,0,0,0,0,0,7,0,0},{0,7,2,1,0,0,0,8,0},{4,0,0,0,0,2,0,0,0},{0,1,7,0,0,3,6,0,0},{0,9,0,0,0,0,0,0,0},{3,2,0,0,6,0,0,4,0}};
    for(int i=0; i< 9; i+=1) {
        for(int j=0; j< 9; j+=1) {

            tmp[i][j] = (QCoreApplication::arguments().at(1+i*9+j)).toInt();
        }
    }
    Sudoku* test = new Sudoku(tmp);
    test->solve();
    w.setSudoku(test);
    w.setCases();
    w.show();
    return a.exec();
}
