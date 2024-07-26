#include "../include/SudokuSolver.hpp"

Row::Row() : Group() {}

Row::Row(SegmentHorizontal** segments) : Group() {
    this->segments = segments;
}

SegmentHorizontal** Row::getSegments() {
    return this->segments;
}

std::vector<char*> Row::getGroupValues() {
    std::vector<char*> values;

    for(int i = 0; i < Row::NB_SEGMENTS; i+=1) {
        for(int j = 0; j < Segment::NB_CASES; j+=1) {
            if( *this->getSegments()[i]->getCases()[j]->getValue() != 0) {
                values.push_back(this->getSegments()[i]->getCases()[j]->getValue() );
            }
        }
    }
    return values;
}