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
};

typedef std::map<char, gene_data_package> GENE_DATA;

#endif