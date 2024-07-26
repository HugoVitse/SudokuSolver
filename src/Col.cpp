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