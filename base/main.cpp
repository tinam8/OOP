#include "base.h"
#include <algorithm>
#include <cassert>
#include <random>  // Uključi biblioteku slučajnih brojeva
#include <ctime>   // Za trenutno vrijeme time(0)

void make_unit(Matrix & A){
     for(int i=0; i < A.rows(); ++i)
         for(int j=0; j<A.cols(); ++j)
		 A(i,j) = (i == j) ? 1 : 0;
}

void transpose(Matrix & A)
{
  assert(A.rows() == A.cols());

  for(int i=0; i < A.rows(); ++i)
         for(int j=i+1; j<A.cols(); ++j){
	         auto tmp = A(j,i);
		 A(j,i) = A(i,j);
                 A(i,j) = tmp;
	 }
}

void permute(Vector & x){
  for(int i =0; i < 69; ++i)
    std::next_permutation(x.begin(), x.end());
}

Operator * make_random(int r, int c) {
   Operator * pa = new Operator(r,c);

   std::default_random_engine r_engine;  // Generator slučajnih brojeva
   r_engine.seed( std::time(0) );        // seed = trenutno vrijeme, osigurava da ne generiramo uvijek
                                         // isti niz brojeva

   // min() i max() funkcije daju raspon SB
   auto max =  r_engine.max();

   // Generator djeluje kao funkcija -- svaki novi poziv daje novi SB
   for(int i=0; i<r; ++i)
     for(int j=0; j<c; ++j)
          (*pa)(i,j) =  10*r_engine()/max;

   return pa;
}

int main()
{
  Operator a(4,4);
  Operator c({ {1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16} });
  c(0,0) = 10;
  std::cout << "init-list-matrix\n";
  c.Matrix::print(std::cout);

  transpose(c);
  make_unit(a);
  std::cout << "unit matrix a\n";
  a.Matrix::print(std::cout);
  permute(a);
  std::cout << "permutation of a\n";
  a.Matrix::print(std::cout);

  std::cout << " c+=a\n";
  c += a;
  std::cout << " c+=a (vect)\n";
  c.Vector::print(std::cout);  // printaj kao vektor
  std::cout << " c+=a (mat)\n";
  c.Matrix::print(std::cout);  // printak kao matricu
  std::cout << "dim = (";
  std::cout << c.size().first << "," << c.size().second << ")\n";

  Operator e(a);
  std::cout << "e(a) : \n";
  e.Matrix::print(std::cout);


  e = std::move(c);
  std::cout << "e = std::move(c) : \n";
  e.Matrix::print(std::cout);

  Operator * pd = make_random(4,4);
  std::cout << "random:\n";
  pd->Matrix::print(std::cout);

  a = *pd;
  std::cout << "a = *pd : \n";
  a.Matrix::print(std::cout);

  Operator m(*make_random(4,4));

  delete pd;

  return 0;
}
