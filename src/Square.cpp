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