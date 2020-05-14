#include "record_model.hpp"

unsigned record_model::num_columns(){
    return n_columns;
}

std::any & record_model::get_column(unsigned index){
    return columns.at(index);
}

const std::string & record_model::get_column_name(unsigned index){
    return names.at(index);
}

const std::vector<std::string> & record_model::get_names(){
    return names;
}
