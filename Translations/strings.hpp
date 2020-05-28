#ifndef STRINGS_HPP
#define STRINGS_HPP
#include <string>


typedef const char * const * const string_container;

inline constexpr char program_name [] = "CrossGene";

extern string_container STRINGS;

enum{
    STRING_GENE_LIST,
    STRING_PROBABILITY_TAB_NAME,
    STRING_LETTER_MARK,
    STRING_DOMINATION_TYPE,
    STRING_DESCRIPTION,
    STRING_ADD_GENE,
    STRING_EDIT_GENE,
    STRING_REMOVE_GENE,
    STRING_CONFIRM,
    STRING_CANCEL,
    STRING_DOMINATION_FULL,
    STRING_DOMINATION_PARTIAL,
    STRING_DOMINATION_CODOMINANCE,
    STRING_ADD_EDIT_GENE
};

#endif