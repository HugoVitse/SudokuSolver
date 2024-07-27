#include "../include/SudokuSolver.hpp"

Segment::Segment() {}

Segment::Segment(Case** cases) {
    this->cases = cases;
}

Case** Segment::getCases() {
    return this->cases;
}

Square* Segment::getSquare() {
    return this->square;
}

void Segment::setSquare(Square* square){
    this->square = square;
}

std::set<char> Segment::getCandidats() {
    std::set<char> values;

    for(int j = 0; j < Segment::NB_CASES; j+=1) {
        if( *this->getCases()[j]->getValue() == 0) {
            for(auto k : this->getCases()[j]->getCandidats()){
                values.insert(k);
            }
        }
    }
    return values;
}


void Segment::removeCandidats(Case* avoid, char candidat) {
    for(int j = 0; j < Segment::NB_CASES; j+=1) {
        if( *this->getCases()[j]->getValue() == 0) {
            this->getCases()[j]->removeCandidats(candidat);
        }
    }
} 

void Segment::removeCandidats(char candidat) {
    for(int j = 0; j < Segment::NB_CASES; j+=1) {
        if( *this->getCases()[j]->getValue() == 0) {
            this->getCases()[j]->removeCandidats(candidat);
        }
    }
} 