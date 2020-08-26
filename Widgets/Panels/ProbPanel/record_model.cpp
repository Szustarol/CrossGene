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
        it.set_value(4, Glib::ustring(STRINGS[STRING_CODOMINANT_TYPE]) + Glib::ustring(std::to_string(1)));
        it.set_value(5, Glib::ustring(STRINGS[STRING_CODOMINANT_TYPE]) + Glib::ustring(std::to_string(2)));
        it.set_value(6, Glib::ustring(STRINGS[STRING_CODOMINANT_TYPE]) + Glib::ustring(std::to_string(1)));
        it.set_value(7, Glib::ustring(STRINGS[STRING_CODOMINANT_TYPE]) + Glib::ustring(std::to_string(2)));
    }
    else{
        it.set_value(4, Glib::ustring(STRINGS[STRING_DOMINANT]));
        it.set_value(5, Glib::ustring(STRINGS[STRING_DOMINANT]));
        it.set_value(6, Glib::ustring(STRINGS[STRING_DOMINANT]));
        it.set_value(7, Glib::ustring(STRINGS[STRING_DOMINANT]));
        it.set_value(3, Glib::ustring("N/A"));
    }
}

void record_model::remove_row_by_iterator(Gtk::TreeModel::iterator it){
    list_store->erase(it);
}

unsigned record_model::n_rows(){
    return list_store->children().size();
}


static bool is_number(const std::string & s){
    return std::find_if(s.begin(), 
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
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
    if(column_idx < 4){
        return;
    }
    char letter;
    Glib::ustring let;
    row.get_value(0, let);
    letter = std::string(let).at(0);
    if(is_codom == "N/A"){//not codom
        Gtk::Dialog dialog;
        dialog.set_title(STRINGS[STRING_IS_DOMINANT]);
        Gtk::Label lab(STRINGS[STRING_IS_DOMINANT]);
        lab.set_visible(true);
        dialog.get_vbox()->pack_start(lab);
        dialog.add_button(STRINGS[STRING_YES], 100);
        dialog.add_button(STRINGS[STRING_NO], 200);
        unsigned choice = dialog.run();
        if(choice == 100){
            row.set_value(column_idx, Glib::ustring(STRINGS[STRING_DOMINANT]));
            if(column_idx == 4)
                (*parent_gene_data)[letter].gamete1.domination_type = GAMETE_DOMINATION_TYPE::DOMINANT;
            else if(column_idx == 5)
                (*parent_gene_data)[letter].gamete2.domination_type = GAMETE_DOMINATION_TYPE::DOMINANT;
            else if(column_idx == 6)
                (*parent_gene_data)[letter].gamete1_2.domination_type = GAMETE_DOMINATION_TYPE::DOMINANT;
            else
                (*parent_gene_data)[letter].gamete2_2.domination_type = GAMETE_DOMINATION_TYPE::DOMINANT;
        }
        else if(choice == 200){
            row.set_value(column_idx, Glib::ustring(STRINGS[STRING_RECESIVE]));
            if(column_idx == 4)
                (*parent_gene_data)[letter].gamete1.domination_type = GAMETE_DOMINATION_TYPE::RECESIVE;
            else if(column_idx == 5)
                (*parent_gene_data)[letter].gamete2.domination_type = GAMETE_DOMINATION_TYPE::RECESIVE;
            else if(column_idx == 6)
                (*parent_gene_data)[letter].gamete1_2.domination_type = GAMETE_DOMINATION_TYPE::RECESIVE;
            else
                (*parent_gene_data)[letter].gamete2_2.domination_type = GAMETE_DOMINATION_TYPE::RECESIVE;

        }
    }
    else{
        unsigned n_codom = std::stoi(is_codom);
        Gtk::Dialog dialog;
        dialog.set_title(STRINGS[STRING_CODOMINANCE_SELECTION]);
        Gtk::ComboBoxText cbt;
        Gtk::Box hboxl(Gtk::Orientation::ORIENTATION_HORIZONTAL);
        Gtk::Label lab(Glib::ustring(STRINGS[STRING_CODOMINANCE_SELECTION]) + Glib::ustring(": "));
        lab.set_visible(true);
        hboxl.pack_start(lab);
        hboxl.pack_end(cbt);
        cbt.set_visible(true);
        cbt.append(Glib::ustring(STRINGS[STRING_NOT_PRESENT]));
        for(unsigned i = 1; i <= n_codom; i++){
            cbt.append(Glib::ustring(std::to_string(i)));
        }
        cbt.set_active(0);
        dialog.get_vbox()->pack_start(hboxl);
        hboxl.set_visible(true);
        dialog.add_button(STRINGS[STRING_CONFIRM], 100);
        unsigned choice = dialog.run();
        if(choice == 100){
            Glib::ustring val;
            cbt.get_active()->get_value(0, val);
            row.set_value(column_idx, Glib::ustring(STRINGS[STRING_CODOMINANT_TYPE]) + val);
            if(column_idx == 4)
                (*parent_gene_data)[letter].gamete1.codomination_index = (is_number(std::string(val))) ? std::stoi(std::string(val)) : 0;
            else if(column_idx == 5)
                (*parent_gene_data)[letter].gamete2.codomination_index = (is_number(std::string(val))) ? std::stoi(std::string(val)) : 0;
            else if(column_idx == 6)
                (*parent_gene_data)[letter].gamete1_2.codomination_index = (is_number(std::string(val))) ? std::stoi(std::string(val)) : 0;
            else
                (*parent_gene_data)[letter].gamete2_2.codomination_index = (is_number(std::string(val))) ? std::stoi(std::string(val)) : 0;
        }
    }
    update_data_package();

}



void record_model::update_data_package(){

    #if DEBUG_MODE
        std::cout << "Updating genes" << std::endl;
    #endif

    std::string part1 = "", part2 = "";

    for(auto & it : *parent_gene_data){
        switch(it.second.dtype){
            case GENE_DOMINATION_TYPE::FULL:
            case GENE_DOMINATION_TYPE::PARTIAL:{
                if(it.second.gamete1.domination_type == GAMETE_DOMINATION_TYPE::DOMINANT){
                    part1.push_back(it.first);
                }
                else{
                    part1.push_back(it.first + 32);
                }

                if(it.second.gamete2.domination_type == GAMETE_DOMINATION_TYPE::DOMINANT){
                    part1.push_back(it.first);
                }
                else{
                    part1.push_back(it.first + 32);
                }

                if(it.second.gamete1_2.domination_type == GAMETE_DOMINATION_TYPE::DOMINANT){
                    part2.push_back(it.first);
                }
                else{
                    part2.push_back(it.first + 32);
                }

                if(it.second.gamete2_2.domination_type == GAMETE_DOMINATION_TYPE::DOMINANT){
                    part2.push_back(it.first);
                }
                else{
                    part2.push_back(it.first + 32);
                }
            }
            break;
            case GENE_DOMINATION_TYPE::CO:
                if(it.second.gamete1.codomination_index == 0){
                    part1.push_back(it.first + 32);
                }
                else{
                    part1.push_back(it.first);
                    part1.append("<sub>" + std::to_string(it.second.gamete1.codomination_index) + "</sub>");
                }

                if(it.second.gamete2.codomination_index == 0){
                    part1.push_back(it.first + 32);
                }
                else{
                    part1.push_back(it.first);
                    part1.append("<sub>" + std::to_string(it.second.gamete2.codomination_index) + "</sub>");
                }

                if(it.second.gamete1_2.codomination_index == 0){
                    part2.push_back(it.first + 32);
                }
                else{
                    part2.push_back(it.first);
                    part2.append("<sub>" + std::to_string(it.second.gamete1_2.codomination_index) + "</sub>");
                }

                if(it.second.gamete2_2.codomination_index == 0){
                    part2.push_back(it.first + 32);
                }
                else{
                    part2.push_back(it.first);
                    part2.append("<sub>" + std::to_string(it.second.gamete2_2.codomination_index) + "</sub>");
                }

            break;
        }
    }

    result_label->set_markup("<b>" + part1 + " x " + part2 + "</b>");
}