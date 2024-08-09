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


void Col::removeCandidat(SegmentVertical* avoid, char candidat) {
    SegmentVertical** segments = this->getSegments();
    for(int i = 0 ; i < Col::NB_SEGMENTS; i+=1) {
        if(segments[i] != avoid) {
            //std::cout << "Col " << i << " " << +candidat << std::endl;
            segments[i]->removeCandidats(candidat);
        }
    }
}


bool isInAvoid(Case** avoid, int nbtoAvoid, Case* _case){
    bool isInAvoid = false;
    for(int i = 0; i< nbtoAvoid; i+=1){
        if(avoid[i] == _case){
            isInAvoid = true;
            break;
        }

    }
    return isInAvoid;
}

bool Col::removeCandidat(Case** avoid, int nbtoAvoid, char candidat) {
    bool didItDoesAnything = false;
    SegmentVertical** segments = this->getSegments();
    for(int i = 0 ; i < Col::NB_SEGMENTS; i+=1) {
        for(int j =0 ; j < SegmentVertical::NB_CASES; j+=1) {
            if(!isInAvoid(avoid,nbtoAvoid,segments[i]->getCases()[j])){
                didItDoesAnything = true;
                segments[i]->getCases()[j]->removeCandidats(candidat);
            }
        }
    }
    return didItDoesAnything;
}


std::set<char> Col::getGroupCandidats(Case* avoid) {
    std::set<char> values;

    for(int i = 0; i < Col::NB_SEGMENTS; i+=1) {
        for(int j = 0; j < Segment::NB_CASES; j+=1) {
            if( *this->getSegments()[i]->getCases()[j]->getValue() == 0 && this->getSegments()[i]->getCases()[j] != avoid) {
                for(auto k : this->getSegments()[i]->getCases()[j]->getCandidats()){
                    values.insert(k);
                }
            }
        }
    }
    return values;
}

void printSet(std::set<char> set){
    for(auto k : set){
        std::cout << +k << " ";
    }
    std::cout << std::endl;
}

bool Col::NakedSets(int size) {
    bool effective = false;
    std::cout << "ok"<< std::endl;  
    std::set<char> GroupCandidats = this->getGroupCandidats(nullptr);
    for(auto k : GroupCandidats){
        std::cout << +k << " ";
    }
    std::cout << std::endl;

    int nbSets = binomial(size,GroupCandidats.size());
    //std::cout<<std::endl << "binom " << GroupCandidats.size() << " " << size << "  " << binomial(size,GroupCandidats.size()) << std::endl;
    std::set<char>* AllSets = new std::set<char>[nbSets];
    char* tabCandidat = new char[GroupCandidats.size()];
    int compteur = 0;   
    for(auto k : GroupCandidats) {
        tabCandidat[compteur] = k;
        compteur+=1;
    }

    compteur = 0;

    for(int i = 0; i< GroupCandidats.size() -1; i+=1) {

        
        for(int j = i+1 ; j < GroupCandidats.size(); j+=1) {
            std::set<char> set;
            set.insert(tabCandidat[i]);
            set.insert(tabCandidat[j]);
            AllSets[compteur] = set;
            compteur+=1;
        }


    }

    for(int j = 0; j < compteur; j+=1){
        int comptSet = 0;
        Case** avoid = new Case*[9];
        for(int i = 0; i < Col::NB_SEGMENTS; i+=1) {
            for(int k = 0; k < SegmentVertical::NB_CASES; k+=1){
                //std::cout << j << " " << i << " " << k << "\n";
                if(this->getSegments()[i]->getCases()[k]->isANakedSet(AllSets[j])){
                    avoid[comptSet] = this->getSegments()[i]->getCases()[k];
                    comptSet +=1;
                }
            }
  
        }

        if(comptSet == size) {
            std::cout << "OUI "; printSet(AllSets[j]); std::cout << std::endl;
            for(auto k : AllSets[j]){
                if(this->removeCandidat(avoid,comptSet,k)){
                    effective = true;
                }
            }
            
        }
        delete avoid;
    }
   

    // std::cout << std::endl;
    // for(int i =0; i < compteur;i+=1){
    //     printSet(AllSets[i]);
    //     std::cout<<std::endl;
    // }
    return effective;
}


bool Col::Segment2(){
    bool isChanged = false;

    for(int i = 0; i < Col::NB_SEGMENTS ; i+=1) {
        std::set<char> SegmentCandidats = this->getSegments()[i]->getCandidats();
        for(auto k : SegmentCandidats){
            bool unique = true;
            for(int j = 0; j < Col::NB_SEGMENTS ; j+=1) {
                if(j != i) {
                    std::set<char> OtherSegmentCandidats = this->getSegments()[j]->getCandidats();
                
                    if(isIn(OtherSegmentCandidats,k)){
                        unique = false;
                        break;
                    }
                    
                
                }
            
            }
            if(unique) {
                isChanged = true;
                this->getSegments()[i]->getSquare()->removeCandidat(this->getSegments()[i],k);               
            }

        }

    }
    return isChanged;
}