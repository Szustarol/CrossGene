#include "record_model.hpp"
#include "../../../defines.hpp"
#include "../../../Translations/strings.hpp"

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

void record_model::add_row(char letter, int dtype, std::string description){
    auto it = *list_store->append();
    it.set_value(0, Glib::ustring(1, letter));
    Glib::ustring dts;
    switch(dtype){
        case GENE_DOMINATION_TYPE::FULL:
            dts = Glib::ustring(STRINGS[STRING_DOMINATION_FULL]);
            break;
        case GENE_DOMINATION_TYPE::PARTIAL:
            dts = Glib::ustring(STRINGS[STRING_DOMINATION_PARTIAL]);
            break;
        case GENE_DOMINATION_TYPE::CO:
            dts = Glib::ustring(STRINGS[STRING_DOMINATION_CODOMINANCE]);
            break;
    }
    it.set_value(1, dts);
    it.set_value(2, Glib::ustring(description));
}

void record_model::remove_row_by_iterator(Gtk::TreeModel::iterator it){
    list_store->erase(it);
}

