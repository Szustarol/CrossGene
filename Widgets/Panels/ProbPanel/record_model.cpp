#include "record_model.hpp"
#include "../../../defines.hpp"
#include "../../../Translations/strings.hpp"

#ifdef DEBUG_MODE
    #include <iostream>
#endif

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

void record_model::add_row(char letter, int dtype, std::string description, int n_codom){
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
    if(n_codom != 0){
        it.set_value(3, Glib::ustring(std::to_string(n_codom)));
    }
    else{
        it.set_value(3, Glib::ustring("N/A"));
    }
}

void record_model::remove_row_by_iterator(Gtk::TreeModel::iterator it){
    list_store->erase(it);
}

unsigned record_model::n_rows(){
    return list_store->children().size();
}

void record_model::row_double_click(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column){
    unsigned row_idx = path[0];
    auto row = list_store->children()[row_idx];
    //get row type
    Glib::ustring is_codom;
    row.get_value(3, is_codom);
    auto tv = column->get_tree_view();
    unsigned column_idx = 0;
    for(; column_idx<tv->get_n_columns(); column_idx++){
        if(tv->get_column(column_idx) == column)
            break;
    }
    if(column_idx != 4 and column_idx != 5){
        return;
    }
    if(is_codom == "N/A"){//not codom
        Gtk::Dialog dialog;
        dialog.set_title(STRINGS[STRING_IS_DOMINANT]);
        Gtk::Label lab(STRINGS[STRING_IS_DOMINANT]);
        lab.set_visible(true);
        dialog.get_vbox()->pack_start(lab);
        dialog.add_button(STRINGS[STRING_YES], 10);
        dialog.add_button(STRINGS[STRING_NO], 20);
        unsigned choice = dialog.run();
        if(choice == 10){
            row.set_value(column_idx, Glib::ustring("Dominant"));
        }
        else if(choice == 20){
            row.set_value(column_idx, Glib::ustring("Recesive"));
        }
    }
    else{
        unsigned n_codom = std::stoi(is_codom);
        Gtk::Dialog dialog;
        dialog.set_title(STRINGS[STRING_CODOMINANCE_SELECTION]);
        Gtk::ComboBoxText cbt;
        cbt.set_visible(true);
        for(unsigned i = 0; i <= n_codom; i++){
            cbt.append(Glib::ustring(std::to_string(i)));
        }
        cbt.set_active(0);
        dialog.get_vbox()->pack_start(cbt);
    }

}
