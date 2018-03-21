#include "BT.h"



///class Segment

// Konstruktor.
Segment::Segment(double left, double right, Segment * parent) : mpt_l(left), mpt_r(right), mparent(parent){
    //std::cout << "Segment konstruktor\n" << std::endl;
    mseg_l.release();
    mseg_r.release();
}
// Da li je segment list (nema djece) ?
bool Segment::isLeaf() const{
    if( mseg_l.get() == nullptr && mseg_r.get() == nullptr )
        return true;
    return false;
}
// Profini segment. Ako već ima djecu ne radi ništa.
void Segment::refine(){
    if( isLeaf() ){
            //std::cout << "leaf...";
            //print();
        mseg_l.reset(new Segment(mpt_l, mpt_l+(mpt_r-mpt_l)/2.0, this) );
        mseg_r.reset(new Segment(mpt_l+(mpt_r-mpt_l)/2, mpt_r, this) );
    }
    return;
}
// Okrupni segment, tj. eliminiraj djecu segmenta. Time segment postaje
// list. Segment mora imati djecu koja su listovi, u suprotnom izbaciti izuzetak
// std::runtime_error() s opisom greške.
void Segment::coarse(){
    Segment* temp = mparent;
    if( (mparent->getLeft())->isLeaf() && (mparent->getRight())->isLeaf()){
        (temp->mseg_l).reset(nullptr);
        (temp->mseg_r).reset(nullptr);
    }
    else{
        throw std::domain_error("Can not course!");
    }
}
// Da li je x u [mpt_l,mpt_r) ?
bool Segment::isIn(double x) const{
    if( x>=mpt_l && x<mpt_r ) return true;
    return false;
}

///class Grid

Grid::iterator Grid::begin(){
    Segment *tmp = &root;
    iterator mbegin(tmp);
    ++mbegin; //dodi do prvog lista
    return mbegin;
}
Grid::iterator Grid::end(){
    iterator mlast(nullptr);
    return mlast;
}

// Profini svaki segment list u trenutnoj mreži.
void Grid::uniform_refine(){
    auto it = begin();
    auto end_it = end();
    for( ; it != end_it; ++it){
            //std::cout << "Refine " << std::endl;
        it->refine();
        //++it;
        }
}
// Ispiši sve segmente listove mreže.
void Grid::print(){
    auto it = begin();
    auto end_it = end();
                //std::cout << "1dodatno: dosla sam do printa" << std::endl;
    for( ; it != end_it; ++it){
            //std::cout << "2dodatno: dosla sam do printa" << std::endl;
        it->print();
        std::cout << std::endl;
    }

}
// Broj segmenata listova u mreži.
int Grid::nOfSegments(){  // Ne može biti konstantna jer nemamo konstantan iterator
    int n = 0;
    auto it = begin();
    auto end_it = end();
    for( ; it != end_it; ++it) n++;
    return n;
}

// Profini segment list koji sadrži točku x. Izbaci
// izuzetak ako je točka izvan domene.
void Grid::refine_selected(double x){
    auto it = begin();
    auto end_it = end();
    for( ; it != end_it; ++it){
        if( it-> isIn(x)){
            it->refine();
            return;
        }
    }
    throw std::domain_error("x out of range!");
}
// Eliminiraj  segment list koji sadrži točku x. Ako segment
// rođak nije list izbaci izuzetak. Učini isto ako je točka izvan domene.
void Grid::coarse_selected(double x){
    auto it = begin();
    auto end_it = end();
    for( ; it != end_it; ++it){
        if( it-> isIn(x)){
            it->coarse();
            return;
        }
    }
    throw std::domain_error("x out of range!");
}
/// Iterator koji iterira samo po djeci listovima mreže (segmentima koji nemaju djecu).
///class GridLeafIterator
GridLeafIterator::GridLeafIterator(Segment* root) : mRoot(root){
    mStack.reset(new std::stack<Segment*>);
    //stavi root na stog
    mStack.get()->push(mRoot);
    }
// operator inkrementiranja (dovoljna je prefiks verzija)
GridLeafIterator& GridLeafIterator::operator++(){    //dodano
    std::stack<Segment*> *stack = mStack.get();
    if(stack->empty()){
        mRoot = nullptr;
        return *this;
    }
    Segment *tmp;
    //uzmi zadnjeg sa stabla i stavi njegovu djecu,ako to ne mozes, on je list
    while(!stack->empty()){
        tmp = stack->top();
        stack->pop();
        if(!((*tmp).isLeaf())){
            //std::cout<< "nije list.. " << std::endl;
            if((*tmp).getRight() != nullptr){
                stack->push((*tmp).getRight());
                //std::cout<< "ima desnog! " << std::endl;
                //(*tmp).getRight()->print();
            }
            if((*tmp).getLeft() != nullptr){
                stack->push((*tmp).getLeft());
                //std::cout<< "ima lijevog! " << std::endl;
                //(*tmp).getLeft()->print();
            }
        } else {
        mRoot = tmp;
        return *this;
        }
    }
    mRoot = nullptr;
    return *this;
}

bool operator==(GridLeafIterator const & lhs, GridLeafIterator const & rhs){
    return lhs.mRoot == rhs.mRoot;
}
bool operator!=(GridLeafIterator const & lhs, GridLeafIterator const & rhs){
    return lhs.mRoot != rhs.mRoot;
}
