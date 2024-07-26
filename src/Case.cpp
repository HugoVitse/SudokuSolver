#include "../include/SudokuSolver.hpp"

bool isIn(std::set<char> NearValues, char i ){
    for(auto ind : NearValues){
        if(ind == i) return true;
    }
    return false;
}

Case::Case() {}

Case::Case(char* value) {   
    this->value = value;
}

char* Case::getValue() {
    return this->value;
}

void Case::setSegmentVertical(SegmentVertical* segment){
    this->verticalSegment = segment;
}

void Case::setSegmentHorizontal(SegmentHorizontal* segment){
    this->horizontalSegment = segment;
}

SegmentVertical* Case::getVerticalSegment() {
    return this->verticalSegment;
}
SegmentHorizontal* Case::getHorizontalSegment() {
    return this->horizontalSegment;
}

void Case::setCandidats() {

    this->candidats.clear();
   

    if(*this->value == 0) {
       

        std::vector<char*> RowValues = this->getHorizontalSegment()->getRow()->getGroupValues();
        std::vector<char*> ColValues = this->getVerticalSegment()->getCol()->getGroupValues();        
        std::vector<char*> SquareValues = this->getVerticalSegment()->getSquare()->getGroupValues();

        std::set<char> NearValues;


        for(int i = 0; i < RowValues.size(); i+=1){
            NearValues.insert(*RowValues[i]);
        }

        for(int i = 0; i < ColValues.size(); i+=1){
            NearValues.insert(*ColValues[i]);
        }
        
        for(int i = 0; i < SquareValues.size(); i+=1){
            NearValues.insert(*SquareValues[i]);
        }


        int count = 0;
        for(char i = 1; i <= 9; i+=1){
            if(!isIn(NearValues, i)){
                this->candidats.insert(i);
                count+=1;
            }
        }
        this->nbcandidats = count;


    }


   


}

void Case::setValue(char value){
    *this->value = value;
}

bool Case::Single() {
    std::cout << this->nbcandidats << std::endl;
    if(this->nbcandidats == 1) {
        this->setValue(*this->candidats.begin());
        this->nbcandidats = 0;
        return true;
    }
    else {
        return false;
    }

}
