#include <stdio.h>
#include <iostream>
#include <vector>
#include <set>

#pragma once

class Case;
class Square;
class Row;
class Col;
class Segment;
class SegmentHorizontal;
class SegmentVertical;

class Sudoku {

public:

    Sudoku();
    Sudoku(char grid[9][9]);

    int get_nb_cases_solved();

    Case** getCases();
    Square** getSquares();
    Row** getRows();
    Col** getCols();

    bool verify();

    bool makeSingles();

    void solve();

    void print();

    static const int NB_CASES = 81;
    static const int NB_GROUPS_IND = 9;
    static const int NB_SEGMENTS_IND = 27;

private:

    Case** cases;
    Square** squares;
    Row** rows;
    Col** cols;
    int nb_cases_solved;



};

class Case {

public:
    Case();
    Case(char* value);

    char* getValue();
    SegmentVertical* getVerticalSegment();
    SegmentHorizontal* getHorizontalSegment();
    void setSegmentHorizontal(SegmentHorizontal* segment);
    void setSegmentVertical(SegmentVertical* segment);
    void setCandidats();
    void setValue(char value);
    bool Single();

private:

    char* value;
    std::set<char> candidats;
    int nbcandidats;
    SegmentVertical* verticalSegment;
    SegmentHorizontal* horizontalSegment;

};

class Segment {

public:
    Segment();
    Segment(Case** cases);

    Case** getCases();
    Square* getSquare();
    void setSquare(Square* square);

    static const int NB_CASES = 3;
private:

    Case** cases;
    Square* square;

};

class SegmentHorizontal : public Segment {

public:
    SegmentHorizontal();
    SegmentHorizontal(Case** cases);

    Row* getRow();
    void setRow(Row* row);

private:

    Row* row;

};

class SegmentVertical : public Segment {

public:
    SegmentVertical();
    SegmentVertical(Case** cases);

    Col* getCol();
    void setCol(Col* col);

private:

    Col* col;


};



class Group {

public:
    Group();
    virtual std::vector<char*> getGroupValues() = 0;
    static const int NB_CASES = 9;
   


};

class Row : public Group {

public:
    Row();
    Row(SegmentHorizontal** segments);

    std::vector<char*> getGroupValues() override;
    SegmentHorizontal** getSegments();
    static const int NB_SEGMENTS = 3;

private:

    SegmentHorizontal** segments;

};

class Col : public Group {

public:
    Col();
    Col(SegmentVertical** segments);

    std::vector<char*> getGroupValues() override;
    SegmentVertical** getSegments();
    static const int NB_SEGMENTS = 3;

private:
    SegmentVertical** segments;

};



class Square : public Group {

public:
    Square();
    Square(SegmentHorizontal** HorizontalSegments, SegmentVertical** VerticalSegments);

    std::vector<char*> getGroupValues() override;
    SegmentHorizontal** getHorizontalSegments();
    SegmentVertical** getVerticalSegments();
        
    static const int NB_SEGMENTS = 6;

private:

    SegmentVertical** VerticalSegments;
    SegmentHorizontal** HorizontalSegments;


};