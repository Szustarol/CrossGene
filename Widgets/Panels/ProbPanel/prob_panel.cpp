#include "prob_panel.hpp"
#include "../../../Translations/strings.hpp"
#include "../../../defines.hpp"

#if DEBUG_MODE
    #include <iostream>
#endif

#include <tuple>

prob_panel::prob_panel() : Gtk::Box(Gtk::Orientation::ORIENTATION_HORIZONTAL),
add_gene_dial(STRINGS[STRING_ADD_EDIT_GENE], true){
    gtk_elements_setup();

    for(char l = 'A'; l <= 'Z'; l++){
        available_letters.insert(std::pair<char, bool>(l, true));
    }

    remove_button.signal_clicked().connect(sigc::mem_fun(this, &prob_panel::on_remove_gene_clicked));
    add_button.signal_clicked().connect(sigc::mem_fun(this, &prob_panel::on_add_gene_clicked));
    gene_selection_treeview.get_selection()->signal_changed().connect(sigc::mem_fun(this, &prob_panel::on_treeview_changed));
}

void prob_panel::on_add_gene_clicked(){
    auto aval = get_available_letters_vec();
    add_gene_dial.set_available_letters(aval);
    int response = add_gene_dial.run();
    switch(response){
        case Gtk::ResponseType::RESPONSE_CANCEL:
        case Gtk::ResponseType::RESPONSE_CLOSE:
        case Gtk::ResponseType::RESPONSE_DELETE_EVENT:
            add_gene_dial.hide();
            break;
        case Gtk::ResponseType::RESPONSE_APPLY:
            add_gene_dial.hide();
            records.add_row(add_gene_dial.returned_values.letter,
            add_gene_dial.returned_values.domination_type,
            add_gene_dial.returned_values.description);
            available_letters.at(add_gene_dial.returned_values.letter) = false;
            break;
        default:
            if constexpr(DEBUG_MODE){
                std::cerr << "Unknown dialog response: " << response << std::endl;
            }
    }
    add_gene_dial.clear_buffers();
}

void prob_panel::on_treeview_changed(){
    Gtk::TreeModel::iterator it = gene_selection_treeview.get_selection()->get_selected();
    if(!it){
        remove_button.set_sensitive(false);
    }
    else{
        remove_button.set_sensitive(true);
    }
}

void prob_panel::on_remove_gene_clicked(){
    Gtk::TreeModel::iterator it = gene_selection_treeview.get_selection()->get_selected();
    if(it){
        std::string letter;
        it->get_value(0, letter);
        available_letters.at(letter.at(0)) = true;
        records.remove_row_by_iterator(it);
    }
}

std::vector<char> prob_panel::get_available_letters_vec(){
    std::vector<char> result;
    for(auto const & [letter, available] : available_letters){
        if(available) result.push_back(letter);
    }
    return result;
}
