#ifndef CALCULATE_DIAGRAM_HPP
#define CALCULATE_DIAGRAM_HPP

#include "../program_data.hpp"

#if DEBUG_MODE
    #include <iostream>
#endif

calculation_results calculate_diagram(const GENE_DATA & gene_data);

bool single_gene_compare(single_gene_data & lhs, single_gene_data & rhs);

std::string gene_data_to_string(const single_gene_data & gd);

std::string gamete_to_string(const whole_gamete & ga);

#endif