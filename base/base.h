#include <iostream>
#include <cstdlib>
#include "stdio.h"
#include <list>
#include <map>
#include <string>
#include  <ctime>
#include <vector>
#include <string>         // std::string
#include <cstddef>        // std::size_t
#include <memory>
#include <fstream>
#include <istream>
#include <initializer_list>

class Base{
public:
    Base(int size);
    Base(std::initializer_list<double> );
    Base(std::initializer_list<std::initializer_list<double> > );
    Base(const Base& obj);

    double& operator()(int x);
    double* begin();
    double* end();

    ~Base();

private:
    double *polje;
    int size;
};

class Matrix: public virtual Base {
public:
    Matrix(int, int);
    Matrix(std::initializer_list<std::initializer_list<double> > );
    Matrix(const Matrix& matrix);

    double operator()(int x,int y);
    virtual void print();
    int cols(){return sizeX;}
    int rows(){return sizeY;}
private:
    int sizeX;
    int sizeY;
};

class Vector: public virtual Base{
public:
    Vector(int size);
    Vector(std::initializer_list<double> );
    double* begin(){return Base::begin();};
    double* end(){return Base::end();};

    //virtual void print();

};

class Operator: public Vector, public Matrix{


};
