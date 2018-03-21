#include "base.h"

Base::Base(int size){
    polje = (double*)calloc(size,sizeof(double));
    this->size = size;
    std::cout << "konstruktor: Base"<< std::endl;
}

Base::Base(std::initializer_list<double> il){
    size = il.size();
    polje = (double*)malloc(size);
    using Iterator = std::initializer_list<double>::iterator;
    int i = 0;
    for(Iterator it = il.begin(); it != il.end(); ++it)
        polje[i++] = (*it);

    std::cout << "konstruktor: Base"<< std::endl;
}

Base::Base(std::initializer_list<std::initializer_list<double>> il){
    size = il.size()*(*il.begin()).size();
    polje = (double*)malloc(size);

    using Iterator1 = std::initializer_list<double>::iterator;
    using Iterator0 = std::initializer_list<std::initializer_list<double>>::iterator;
    int i = 0;
    for(Iterator0 it0 = il.begin(); it0 != il.end(); ++it0){
         for(Iterator1 it1 = (*it0).begin(); it1 != (*it0).end(); ++it1){
            polje[i++] = (*it1);
        }
   }

    std::cout << "konstruktor: Base"<< std::endl;
}

Base::Base(const Base& obj):size(obj.size),polje(new double[obj.size]){
    for(int i=0; i < size; ++i) polje[i]=obj.polje[i];
}

Base::~Base(){
    free(polje);
    std::cout << "Destruktor: Base" << std::endl;
}

double& Base::operator()(int x){
    if(x < size){
        return polje[x];
    } else{
        throw std::invalid_argument("Expecting ... but ... !");
    }
}

double* Base::begin(){
    if(size != 0){
        return &polje[0];
    } else{
        throw std::invalid_argument("Expecting ... but ... !");
    }
}

double* Base::end(){
    if(size != 0){
        return &polje[size-1];
    } else{
        throw std::invalid_argument("Expecting ... but ... !");
    }
}
//////////////////////////////////////////////////////////

Matrix::Matrix(int row, int col): Base(row*col), sizeX(row), sizeY(col){
    std::cout << "konstruktor: Matrix"<< std::endl;
}

Matrix::Matrix(std::initializer_list<std::initializer_list<double>> il):Base(il){
    sizeX = il.size();
    sizeY = (*il.begin()).size();

    std::cout << "konstruktor: Matrix"<< std::endl;
}
Matrix::Matrix(const Matrix& matrix): Base(matrix){
    sizeX = matrix.sizeX;
    sizeY = matrix.sizeY;
}

double Matrix::operator()(int x,int y){
    return Base::operator()(x*sizeY+y);
}

/////////////////////////////////////////////////////////////////////////
Vector::Vector(int size): Base(size){
     std::cout << "konstruktor: Vector"<< std::endl;
}

Vector::Vector(std::initializer_list<double> il):Base(il){
    std::cout << "konstruktor: Vector"<< std::endl;
}
