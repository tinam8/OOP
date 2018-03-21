#include "BT.h"
#include <iostream>
#include <stdexcept>
#include <cmath>


void checkGrid(Grid & grid){
    double L = grid.right() - grid.left();
    double LL = 0.0;
    auto it = grid.begin();
    auto end_it = grid.end();
    for( ; it != end_it; ++it)
        LL += it->length();

    if(std::abs(L -LL) > 1E-15)
        throw std::logic_error("????");
}


int main()
{
    Grid grid(0.0,1.0);
    //std::cout << grid.left() << " " << grid.right() << std::endl;
    grid.print();
    std::cout<< std::endl;

    grid.uniform_refine();

    grid.print(); std::cout<< std::endl;

    grid.uniform_refine();
    grid.print(); std::cout<< std::endl;
    std::cout << "no of segments = " << grid.nOfSegments() << std::endl;


    for(double x = 0.08; x < 1.0; x += 0.2){
         grid.refine_selected(x);
         std::cout << "profinjujem segment s tockom " << x << std::endl;
         grid.print(); std::cout<< std::endl;
         std::cout << "no of segments = " << grid.nOfSegments() << std::endl;
         checkGrid(grid);
    }

    grid.coarse_selected(0.41);
    std::cout << "eliminiraj segment containing 0.41\n";
    grid.print(); std::cout<< std::endl;
    std::cout << "no of segments = " << grid.nOfSegments() << std::endl;
    checkGrid(grid);

    grid.coarse_selected(0.61);
    std::cout << "eliminiraj segment containing 0.61\n";
    grid.print(); std::cout<< std::endl;
    std::cout << "no of segments = " << grid.nOfSegments() << std::endl;
    checkGrid(grid);

    try{
          grid.coarse_selected(1.61);
          std::cout << "eliminiraj segment containing 1.61\n";
          grid.print(); std::cout<< std::endl;
          std::cout << "no of segments = " << grid.nOfSegments() << std::endl;

    }
    catch(std::exception & e){
       std::cerr << "Grid reported error: " << e.what() << std::endl;
    }


    return 0;
}
