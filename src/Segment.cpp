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