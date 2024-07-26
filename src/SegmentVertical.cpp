#include "../include/SudokuSolver.hpp"

SegmentVertical::SegmentVertical() : Segment() {

}
SegmentVertical::SegmentVertical(Case** cases) : Segment(cases) {

}

Col* SegmentVertical::getCol() {
    return this->col;
}

void SegmentVertical::setCol(Col* col) {
    this->col = col;
}