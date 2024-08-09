#include "../include/SudokuSolver.hpp"

Square::Square() : Group() {}

Square::Square(SegmentHorizontal** _HorizontalSegments, SegmentVertical** _VerticalSegments) : Group() {
    this->HorizontalSegments = _HorizontalSegments;
    this->VerticalSegments = _VerticalSegments;
}

SegmentHorizontal** Square::getHorizontalSegments() {
    return this->HorizontalSegments;
}

SegmentVertical** Square::getVerticalSegments() {
    return this->VerticalSegments;
}

std::vector<char*> Square::getGroupValues() {
    std::vector<char*> values;
    for(int i = 0; i < (Square::NB_SEGMENTS)/2; i+=1) {
        for(int j = 0; j < Segment::NB_CASES; j+=1) {
            if( *this->getHorizontalSegments()[i]->getCases()[j]->getValue() != 0) {
               values.push_back(this->getHorizontalSegments()[i]->getCases()[j]->getValue() );
            }
        }
    }
    return values;
}

std::set<char> Square::getGroupCandidats(Case* avoid) {
    std::set<char> values;
    for(int i = 0; i < (Square::NB_SEGMENTS)/2; i+=1) {
        for(int j = 0; j < Segment::NB_CASES; j+=1) {
            if( *this->getHorizontalSegments()[i]->getCases()[j]->getValue() == 0 && this->getHorizontalSegments()[i]->getCases()[j] != avoid) {
                for(auto k : this->getHorizontalSegments()[i]->getCases()[j]->getCandidats()){
                    values.insert(k);
                }
            }
        }
    }
    return values;
}

void Square::removeCandidat(SegmentHorizontal* avoid, char candidat) {
    SegmentHorizontal** segments = this->getHorizontalSegments();
    for(int i = 0 ; i < (Square::NB_SEGMENTS)/2; i+=1) {
        if(segments[i] != avoid) {
            //std::cout << "Col " << i << " " << +candidat << std::endl;
            segments[i]->removeCandidats(candidat);
        }
    }
}

void Square::removeCandidat(SegmentVertical* avoid, char candidat) {
    SegmentVertical** segments = this->getVerticalSegments();
    for(int i = 0 ; i < (Square::NB_SEGMENTS)/2; i+=1) {
        if(segments[i] != avoid) {
            //std::cout << "Col " << i << " " << +candidat << std::endl;
            segments[i]->removeCandidats(candidat);
        }
    }
}

bool Square::NakedSets(int size) {
    return true;
}

bool Square::Segment1() {

    bool isChanged = false;

    for(int i = 0; i < (Square::NB_SEGMENTS)/2 ; i+=1) {
        std::set<char> SegmentCandidats = this->getHorizontalSegments()[i]->getCandidats();
        for(auto k : SegmentCandidats){
            bool unique = true;
            for(int j = 0; j < (Square::NB_SEGMENTS)/2 ; j+=1) {
                if(j != i) {
                    std::set<char> OtherSegmentCandidats = this->getHorizontalSegments()[j]->getCandidats();
                
                    if(isIn(OtherSegmentCandidats,k)){
                        unique = false;
                        break;
                    }
                    
                
                }
            
            }
            if(unique) {
                isChanged = true;
                this->getHorizontalSegments()[i]->getRow()->removeCandidat(this->getHorizontalSegments()[i],k);
            }

        }


    }

    for(int i = 0; i < (Square::NB_SEGMENTS)/2 ; i+=1) {
        std::set<char> SegmentCandidats = this->getVerticalSegments()[i]->getCandidats();
        for(auto k : SegmentCandidats){
            bool unique = true;
            for(int j = 0; j < (Square::NB_SEGMENTS)/2 ; j+=1) {
                if(j != i) {
                    std::set<char> OtherSegmentCandidats = this->getVerticalSegments()[j]->getCandidats();
                
                    if(isIn(OtherSegmentCandidats,k)){
                        unique = false;
                        break;
                    }
                    
                
                }
            
            }
            if(unique) {
                isChanged = true;
                this->getVerticalSegments()[i]->getCol()->removeCandidat(this->getVerticalSegments()[i],k);
            }

        }

    }

    return isChanged;
}