#include "../include/SudokuSolver.hpp"


Case::Case() {}

Case::Case(char* value) {   
    this->value = value;
    this->nbcandidats = 0;
}

char* Case::getValue() {
    return this->value;
}

std::set<char> Case::getCandidats() {
    return this->candidats;
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
                //std::cout << +i << " ";
                this->candidats.insert(i);
                count+=1;
            }
        }
        this->nbcandidats = count;

        //std::cout << this->nbcandidats << std::endl;


    }


   


}




 bool Case::isANakedSet(std::set<char> set) {
    if(this->nbcandidats == 0) return false;
    bool isNSET = true;
    for(auto k : this->getCandidats()) {
        if(set.find(k) == set.end()){
            isNSET = false;
            break;
        }
    }
    return isNSET;
 }

void Case::removeCandidats(char candidat) {
    this->candidats.erase(candidat);
    if(this->value != 0){
        this->nbcandidats = this->candidats.size();
    }
    else {
        this->nbcandidats = 0;
    }
    //std::cout << this->nbcandidats << " " << +candidat << std::endl ;
}

void Case::setValue(char value){
    *this->value = value;
    this->nbcandidats = 0;
    for(int i =0; i < Row::NB_SEGMENTS; i+=1){
        this->getHorizontalSegment()->getRow()->getSegments()[i]->removeCandidats(this, value);
        this->getVerticalSegment()->getCol()->getSegments()[i]->removeCandidats(this, value);
        this->getHorizontalSegment()->getSquare()->getHorizontalSegments()[i]->removeCandidats(this, value);
    }

}

bool Case::Single() {
    if(this->nbcandidats == 1 && *this->getValue() == 0) {
        this->setValue(*this->candidats.begin());
        this->nbcandidats = 0;
        return true;
    }
    else {
        return false;
    }

}

bool Case::HiddenSingle() {
    std::cout << " tg " << +*this->getValue();
    if(this->nbcandidats > 0 && *this->getValue() == 0) {

        
        std::set<char> RowCandidats = this->getHorizontalSegment()->getRow()->getGroupCandidats(this);
        std::set<char> ColCandidats = this->getVerticalSegment()->getCol()->getGroupCandidats(this);
        std::set<char> SquareCandidats = this->getHorizontalSegment()->getSquare()->getGroupCandidats(this );

        std::cout << "hiddentest";
        printSet(RowCandidats);

        for(auto i: this->candidats) {
            //std::cout << std::endl << +i << " ";
            if(!isIn(RowCandidats,i) || !isIn(ColCandidats,i) || !isIn(SquareCandidats,i) ){
                //std::cout << "hiden " << +i << " " ;
                //std::cout << std::endl;
                this->setValue(i);
                return true;
            }
        }
    

        return false;

    }
    return false;


}