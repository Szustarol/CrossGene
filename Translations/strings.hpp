#ifndef STRINGS_HPP
#define STRINGS_HPP
#include <string>


typedef const char * const * const string_container;

const std::string program_name = "CrossGene";

extern string_container STRINGS;

enum{
    STRING_GENE_LIST,
    PROBABILITY_TAB_NAME
};

#endif