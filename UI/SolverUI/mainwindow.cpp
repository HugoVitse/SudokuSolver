#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../../include/SudokuSolver.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setSudoku(Sudoku* sudoku){
    this->sudoku = sudoku;
}

void MainWindow::setCases(){
    for(int i = 1; i <= 81 ; i+=1){
        QString tg = QString("textEdit_")+QString::number(i);
        QTextEdit *lineEdit = findChild<QTextEdit*>(tg);
        int test = (int)*this->sudoku->getCases()[i-1]->getValue();
        lineEdit->setReadOnly(true);
        lineEdit->setText(QString::number(test));
    }
}
