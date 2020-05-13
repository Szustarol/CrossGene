#include <iostream>
#include "defines.hpp"

int main(void){
    if constexpr(DEBUG_MODE){
        std::cout << "CrossGene is starting." << std::endl;
    }

    return 0;
}