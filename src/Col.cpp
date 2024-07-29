#include "../include/SudokuSolver.hpp"

Col::Col() : Group() {}

Col::Col(SegmentVertical** segments) : Group() {
    this->segments = segments;
}

SegmentVertical** Col::getSegments() {
    return this->segments;
}

std::vector<char*> Col::getGroupValues() {
    std::vector<char*> values;

    for(int i = 0; i < Col::NB_SEGMENTS; i+=1) {
        for(int j = 0; j < Segment::NB_CASES; j+=1) {
            if( *this->getSegments()[i]->getCases()[j]->getValue() != 0) {
                values.push_back(this->getSegments()[i]->getCases()[j]->getValue() );
            }
        }
    }
    return values;
}


void Col::removeCandidat(SegmentVertical* avoid, char candidat) {
    SegmentVertical** segments = this->getSegments();
    for(int i = 0 ; i < Col::NB_SEGMENTS; i+=1) {
        if(segments[i] != avoid) {
            //std::cout << "Col " << i << " " << +candidat << std::endl;
            segments[i]->removeCandidats(candidat);
        }
    }
}

std::set<char> Col::getGroupCandidats(Case* avoid) {
    std::set<char> values;

    for(int i = 0; i < Col::NB_SEGMENTS; i+=1) {
        for(int j = 0; j < Segment::NB_CASES; j+=1) {
            if( *this->getSegments()[i]->getCases()[j]->getValue() == 0 && this->getSegments()[i]->getCases()[j] != avoid) {
                for(auto k : this->getSegments()[i]->getCases()[j]->getCandidats()){
                    values.insert(k);
                }
            }
        }
    }
    return values;
}


bool Col::Segment2(){
    bool isChanged = false;

    for(int i = 0; i < Col::NB_SEGMENTS ; i+=1) {
        std::set<char> SegmentCandidats = this->getSegments()[i]->getCandidats();
        for(auto k : SegmentCandidats){
            bool unique = true;
            for(int j = 0; j < Col::NB_SEGMENTS ; j+=1) {
                if(j != i) {
                    std::set<char> OtherSegmentCandidats = this->getSegments()[j]->getCandidats();
                
                    if(isIn(OtherSegmentCandidats,k)){
                        unique = false;
                        break;
                    }
                    
                
                }
            
            }
            if(unique) {
                isChanged = true;
                this->getSegments()[i]->getSquare()->removeCandidat(this->getSegments()[i],k);               
            }

        }

    }
    return isChanged;
}