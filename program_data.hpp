#ifndef PROGRAM_DATA
#define PROGRAM_DATA

#include "defines.hpp"
#include <map>
#include <vector>

enum GENE_DOMINATION_TYPE{
    FULL,
    PARTIAL,
    CO
};

enum GAMETE_DOMINATION_TYPE{
    DOMINANT,
    RECESIVE,
};

union GAMETE_DESCRIPTION{
    GAMETE_DOMINATION_TYPE domination_type;
    unsigned codomination_index;
};

struct single_gene_data{
    GAMETE_DESCRIPTION gamete_description;
    char letter;
    bool codominant; //required for valid sorting
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
    unsigned phenotype_index; //unused yet
    unsigned genotype_index; //unused yet
};

typedef std::vector<single_gene_data> whole_gamete;

typedef std::map<char, gene_data_package> GENE_DATA;


struct calculation_results{
    std::vector<std::vector<calculation_result>> c_results;
    std::vector<whole_gamete> gametes1;
    std::vector<whole_gamete> gametes2;
    unsigned n_genotypes;
    unsigned n_phenotypes;
    std::vector<std::string> genotype_names;
    std::vector<std::string> phenotype_names;
};


#endif