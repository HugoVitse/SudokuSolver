#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <iomanip>

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
    bool makeHiddenSingles();
    bool makeSegment1();
    bool makeSegment2();
    bool makeAllTechniques();

    void solve();

    void print();
      
    void printC();

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
    Case(char* value); int nbcandidats;

    char* getValue();
    SegmentVertical* getVerticalSegment();
    SegmentHorizontal* getHorizontalSegment();
    std::set<char> getCandidats();
    void setSegmentHorizontal(SegmentHorizontal* segment);
    void setSegmentVertical(SegmentVertical* segment);
    void setCandidats();
    void setValue(char value);
    void removeCandidats(char candidat);
    bool Single();
    bool HiddenSingle();

private:

    char* value;
    std::set<char> candidats;
   
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
    std::set<char> getCandidats();
    void removeCandidats(char candidat);
    void removeCandidats(Case* avoid, char candidat);

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
    virtual std::set<char> getGroupCandidats(Case* avoid) = 0;
    static const int NB_CASES = 9;
   


};

class Row : public Group {

public:
    Row();
    Row(SegmentHorizontal** segments);

    std::vector<char*> getGroupValues() override;
    std::set<char> getGroupCandidats(Case* avoid) override;
    SegmentHorizontal** getSegments();
    void removeCandidat(SegmentHorizontal* avoid, char candidat);
    bool Segment2();
    static const int NB_SEGMENTS = 3;

private:

    SegmentHorizontal** segments;

};

class Col : public Group {

public:
    Col();
    Col(SegmentVertical** segments);

    std::vector<char*> getGroupValues() override;
    std::set<char> getGroupCandidats(Case* avoid) override;
    SegmentVertical** getSegments();
    void removeCandidat(SegmentVertical* avoid, char candidat);
    bool Segment2();
    static const int NB_SEGMENTS = 3;

private:
    SegmentVertical** segments;

};



class Square : public Group {

public:
    Square();
    Square(SegmentHorizontal** HorizontalSegments, SegmentVertical** VerticalSegments);

    std::vector<char*> getGroupValues() override;
    std::set<char> getGroupCandidats(Case* avoid) override;
    SegmentHorizontal** getHorizontalSegments();
    SegmentVertical** getVerticalSegments();   
    void removeCandidat(SegmentHorizontal* avoid, char candidat);
    void removeCandidat(SegmentVertical* avoid, char candidat);
    bool Segment1();
        
    static const int NB_SEGMENTS = 6;

private:

    SegmentVertical** VerticalSegments;
    SegmentHorizontal** HorizontalSegments;


};

bool isIn(std::set<char> NearValues, char i );