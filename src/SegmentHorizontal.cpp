#include "../include/SudokuSolver.hpp"

SegmentHorizontal::SegmentHorizontal() : Segment() {

}
SegmentHorizontal::SegmentHorizontal(Case** cases) : Segment(cases) {

}

Row* SegmentHorizontal::getRow() {
    return this->row;
}

void SegmentHorizontal::setRow(Row* row) {
    this->row = row;
}