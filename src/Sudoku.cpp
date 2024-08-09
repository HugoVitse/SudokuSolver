#include "../include/SudokuSolver.hpp"

int index(int i){
    if(i < 9) return i;
    if(i >= 9 && i < 18) return i + 18;
    if(i >= 18 && i < 27) return i + 36;
    else return 0; 
}

int index_row(int i){
    if(i < 3) return i;
    if(i >= 3 && i < 6) return i + 6;
    if(i >= 6 && i < 9) return i + 12;
    else return 0; 
}

Sudoku::Sudoku() {}

Sudoku::Sudoku(char grid[9][9]) {

    this->cases = new Case*[Sudoku::NB_CASES];

    for(int i=0; i< Sudoku::NB_GROUPS_IND; i+=1){
        for(int j=0; j< Sudoku::NB_GROUPS_IND; j+=1){
            this->cases[i*9+j] = new Case(&grid[i][j]);
        }   
    }

    SegmentHorizontal** listSegmentHorizontal = new SegmentHorizontal*[Sudoku::NB_SEGMENTS_IND];
    for(int i=0; i < Sudoku::NB_CASES; i+=3) {
        Case** tmp = new Case*[3];
        for(int j=0; j< Segment::NB_CASES; j+=1) {
            tmp[j] = this->cases[i+j];
        }
        listSegmentHorizontal[i/3] = new SegmentHorizontal(tmp);
        for(int j=0; j< Segment::NB_CASES; j+=1) {
            this->cases[i+j]->setSegmentHorizontal(listSegmentHorizontal[i/3]);
        }
   
    }


    SegmentVertical** listSegmentVertical = new SegmentVertical*[Sudoku::NB_SEGMENTS_IND];
    for(int i=0; i < Sudoku::NB_SEGMENTS_IND; i+=1) {
        Case** tmp = new Case*[3];
        for(int j=0; j< Segment::NB_CASES; j+=1) {
            tmp[j] = this->cases[index(i)+j*9];
        }
        listSegmentVertical[i] = new SegmentVertical(tmp);
        for(int j=0; j< Segment::NB_CASES; j+=1) {
            this->cases[index(i)+j*9]->setSegmentVertical(listSegmentVertical[i]);
        }
   
    }

    Row** listRow = new Row*[Sudoku::NB_GROUPS_IND];
    for(int i=0; i< Sudoku::NB_SEGMENTS_IND; i+=3) {

        SegmentHorizontal** tmp = new SegmentHorizontal*[Row::NB_SEGMENTS];
        for(int j=0; j< Row::NB_SEGMENTS; j+=1) {
            tmp[j] = listSegmentHorizontal[i+j];
        }
        listRow[i/3] = new Row(tmp);
    
                
        for(int j=0; j< Row::NB_SEGMENTS; j+=1) {
            listSegmentHorizontal[i+j]->setRow(listRow[i/3]);
        }

    }

    this->rows = listRow;


    Col** listCol = new Col*[Sudoku::NB_GROUPS_IND];
    for(int i=0; i< Sudoku::NB_GROUPS_IND; i+=1) {

        SegmentVertical** tmp = new SegmentVertical*[Col::NB_SEGMENTS];
        for(int j=0; j< Col::NB_SEGMENTS; j+=1) {
            tmp[j] = listSegmentVertical[i +9*j];
        }
        listCol[i] = new Col(tmp);
    
                
        for(int j=0; j< Col::NB_SEGMENTS; j+=1) {
            listSegmentVertical[i+9*j]->setCol(listCol[i]);
        }

    }

    this->cols = listCol;
    

    Square** listSquare = new Square*[Sudoku::NB_GROUPS_IND];
    for(int i = 0 ; i < Sudoku::NB_SEGMENTS_IND; i+=3) {
        SegmentVertical** tmpVert = new SegmentVertical*[Col::NB_SEGMENTS];
        SegmentHorizontal** tmpHor = new SegmentHorizontal*[Row::NB_SEGMENTS];
        for(int j=0; j< Square::NB_SEGMENTS/2; j+=1) {
            tmpVert[j] = listSegmentVertical[i+j];
            tmpHor[j] = listSegmentHorizontal[index_row(i/3)+j*3];
        }
      
        listSquare[i/3] = new Square(tmpHor,tmpVert);
        for(int j=0; j< Square::NB_SEGMENTS/2; j+=1) {
            tmpVert[j]->setSquare(listSquare[i/3]);
            tmpHor[j]->setSquare(listSquare[i/3]);
        }
    }
    this->squares = listSquare;
    //std::cout << +this->getSquares()[7]->getHorizontalSegments()[0]->getCases()[2]->getHorizontalSegment()->getSquare()->getHorizontalSegments()[0]->getCases()[2]->getValue()<< std::endl << +this->squares[7]->getVerticalSegments()[2]->getCases()[0]->getValue();


}

Case** Sudoku::getCases() {
    return this->cases;
}

Square** Sudoku::getSquares() {
    return this->squares;
}

Row** Sudoku::getRows() {
    return this->rows;
}

Col** Sudoku::getCols() {
    return this->cols;
}

void Sudoku::solve() {

    for(int i=0; i < Sudoku::NB_CASES; i+=1) {
        this->getCases()[i]->setCandidats();
    }
    this->printC();
    do {
        
    }
    while (this->makeAllTechniques());

    this->makeAllTechniques();
 
}

bool Sudoku::makeSingles(){
    bool isChange = false;
    for(int i=0; i < Sudoku::NB_CASES; i+=1) {
        if(this->getCases()[i]->Single()) {
            isChange = true;
            std::cout << "i ; " << i << std::endl;

        }
    }
    return isChange;
}

    
bool Sudoku::makeHiddenSingles() {
    bool isChange = false;
    for(int i=0; i < Sudoku::NB_CASES; i+=1) {
        if(this->getCases()[i]->HiddenSingle()) {
            std::cout << "ihidden ; " << i << std::endl;
            isChange = true;
        }
    }
    return isChange;
}

bool Sudoku::makeSegment1(){
    bool isChange = false;
    for(int i=0; i < Sudoku::NB_GROUPS_IND; i+=1) {
        if(this->getSquares()[i]->Segment1()) {
            isChange = true;
        }
    }
    return isChange;
}

bool Sudoku::makeSegment2(){
    bool isChange = false;
    for(int i=0; i < Sudoku::NB_GROUPS_IND; i+=1) {
        if(this->getRows()[i]->Segment2() || this->getCols()[i]->Segment2()) {
            isChange = true;
        }
    }
    return isChange;
}

bool Sudoku::makeNakedSets() {
    bool isChange = false;
    for(int i=0; i < Sudoku::NB_GROUPS_IND; i+=1) {
        std::cout << "col " << i << std::endl;
        if(this->getCols()[i]->NakedSets(2)) {
            isChange = true;
        }
    }
    return isChange;
}

bool Sudoku::makeAllTechniques(){
       

    this->makeSegment1();
    this->makeSegment2();
    this->makeNakedSets();
    bool isSingles = this->makeSingles();
    bool isHiddenSingles = this->makeHiddenSingles();

    this->printC();
    std::cout << std::endl;
    this->print();

    std::cout << std::endl;

    std::cout << (isSingles?"true":"false") << " " << (isHiddenSingles?"true":"false") << std::endl;
    return isSingles || isHiddenSingles;
}

void Sudoku::print() {
    for(int i=0; i < 81; i++) {
        if(i%9 == 0) std::cout << std::endl << std::endl;
        std::cout << std::dec << +*this->cases[i]->getValue() << "   ";
       
    }
}

void Sudoku::printC() {
    for(int i=0; i < 81; i++) {
        if(i%9 == 0) std::cout << std::endl;
        if(this->cases[i]->nbcandidats == 0) std::cout << std::setw(4) << std::setfill('0') << 0 << " ";
        else {
            std::stringstream ss;
        for(auto i : this->cases[i]->getCandidats()){
            ss << std::dec  << +i;
        }   

        std::cout << std::setw(4) << std::setfill('0') << ss.str() << " ";}
       
       
    }
}