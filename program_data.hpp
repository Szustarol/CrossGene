#ifndef PROGRAM_DATA
#define PROGRAM_DATA

#include "defines.hpp"
#include <map>

union GAMETE_DESCRIPTION{
    GAMETE_DOMINATION_TYPE domination_type;
    unsigned codomination_index;
};

struct gene_data_package{
    GENE_DOMINATION_TYPE dtype;
    GAMETE_DESCRIPTION gamete1;
    GAMETE_DESCRIPTION gamete2;
    GAMETE_DESCRIPTION gamete1_2;
    GAMETE_DESCRIPTION gamete2_2;
};

struct calculation_result{
    std::string string_representation;

};

typedef std::map<char, gene_data_package> GENE_DATA;

#endif