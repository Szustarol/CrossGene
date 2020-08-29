#include "prob_panel.hpp"
#include "../../../Translations/strings.hpp"
#include "../../../defines.hpp"
#include "../ResultPanel/result_panel.hpp"

#if DEBUG_MODE
    #include <iostream>
#endif

#include <tuple>

prob_panel::prob_panel(Gtk::Notebook * parent_notebook, std::vector<std::shared_ptr<Gtk::Container>> * parent_panels) : Gtk::Box(Gtk::Orientation::ORIENTATION_HORIZONTAL),
add_gene_dial(STRINGS[STRING_ADD_EDIT_GENE], true){
    gtk_elements_setup();

    this->parent_notebook = parent_notebook;
    this->parent_panels = parent_panels;

    for(char l = 'A'; l <= 'Z'; l++){
        available_letters.insert(std::pair<char, bool>(l, true));
    }

    records.result_label = &crossing_label;

    remove_button.signal_clicked().connect(sigc::mem_fun(this, &prob_panel::on_remove_gene_clicked));
    add_button.signal_clicked().connect(sigc::mem_fun(this, &prob_panel::on_add_gene_clicked));
    gene_selection_treeview.get_selection()->signal_changed().connect(sigc::mem_fun(this, &prob_panel::on_treeview_changed));
    calc_button.signal_clicked().connect(sigc::mem_fun(this, &prob_panel::on_calc_clicked));

    for(unsigned column_idx; column_idx<gene_selection_treeview.get_n_columns(); column_idx++){
        gene_selection_treeview.get_column(column_idx)->set_sizing(Gtk::TreeViewColumnSizing::TREE_VIEW_COLUMN_AUTOSIZE);
        gene_selection_treeview.get_column(column_idx)->set_resizable(true);
    }

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
        case Gtk::ResponseType::RESPONSE_APPLY:{
            add_gene_dial.hide();
            int n_cdm = add_gene_dial.returned_values.n_codominant;
            if(add_gene_dial.returned_values.domination_type != GENE_DOMINATION_TYPE::CO)
                n_cdm = 0;
            records.add_row(add_gene_dial.returned_values.letter,
            add_gene_dial.returned_values.domination_type,
            add_gene_dial.returned_values.description, n_cdm);
            available_letters.at(add_gene_dial.returned_values.letter) = false;
            unsigned rows = records.n_rows();
            if(rows > 0){
                calc_button.set_sensitive(true);
            }
            else{
                calc_button.set_sensitive(false);
            }   
            char l = add_gene_dial.returned_values.letter;
            gene_data[l] = gene_data_package();
            gene_data[l].dtype = add_gene_dial.returned_values.domination_type;
            int dtype = gene_data[l].dtype;
            if(dtype == GENE_DOMINATION_TYPE::FULL or dtype == GENE_DOMINATION_TYPE::PARTIAL){
                gene_data[l].gamete1.domination_type = GAMETE_DOMINATION_TYPE::DOMINANT;
                gene_data[l].gamete2.domination_type = GAMETE_DOMINATION_TYPE::DOMINANT;
                gene_data[l].gamete1_2.domination_type = GAMETE_DOMINATION_TYPE::DOMINANT;
                gene_data[l].gamete2_2.domination_type = GAMETE_DOMINATION_TYPE::DOMINANT;
            }
            else{
                gene_data[l].gamete1.codomination_index = 1;
                gene_data[l].gamete2.codomination_index = 2;
                gene_data[l].gamete1_2.codomination_index = 1;
                gene_data[l].gamete2_2.codomination_index = 2;
            }
            }
            break;
        default:
            #if DEBUG_MODE
                std::cerr << "Unknown dialog response: " << response << std::endl;
            #endif
            break;
    }
    add_gene_dial.clear_buffers();
    records.update_data_package();
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

void prob_panel::on_calc_clicked(){
    auto r = calculate_diagram(gene_data);
    std::string title = crossing_label.get_text().raw();

    parent_panels->push_back(
        std::shared_ptr<Gtk::Container>( new result_panel(r.c_results, r.gametes1, r.gametes2,
        r.n_genotypes, r.n_phenotypes, r.genotype_names, r.phenotype_names, title))
    );

    std::string temp = ""; //parse title string

    for(auto c : title){
        if(isalpha(c)) temp += c;
        else temp += "<sub>" + std::string(1, c) + "</sub>";
    }

    Gtk::Widget * tab_label = Gtk::manage(new Gtk::Label());
    ((Gtk::Label *)tab_label)->set_markup(temp);
    ((Gtk::Label *)tab_label)->set_margin_top(4);
    Gtk::Widget * tab_button = Gtk::manage(new Gtk::ToolButton());
    ((Gtk::ToolButton*) tab_button)->set_icon_name("window-close");
    ((Gtk::ToolButton*) tab_button)->set_margin_left(10);
    tab_button->set_visible(true);
    tab_label->set_visible(true);
    Gtk::Widget * tab_hbox = Gtk::manage(new Gtk::Box(Gtk::Orientation::ORIENTATION_HORIZONTAL));
    ((Gtk::Box*)tab_hbox)->add(*tab_label);
    ((Gtk::Box*)tab_hbox)->add(*tab_button);
    ((Gtk::Box*)tab_hbox)->set_vexpand(true);
    tab_hbox->set_visible(true);

    auto  page = parent_panels->back();
    page->set_visible(true);
    parent_notebook->append_page(*page, *tab_hbox);

    ((Gtk::ToolButton*) tab_button)->signal_clicked().connect(
        sigc::bind<std::shared_ptr<Gtk::Container>>(
            sigc::mem_fun(this, &prob_panel::tab_closure),
            page
        )
    );
    
}

void prob_panel::tab_closure(std::shared_ptr<Gtk::Container>  page){
    parent_notebook->remove(*page);
    for(auto it = parent_panels->begin(); it != parent_panels->end(); it++){
        if (*it == page){
            parent_panels->erase(it);
            break;
        }
    }
}

void prob_panel::on_remove_gene_clicked(){
    Gtk::TreeModel::iterator it = gene_selection_treeview.get_selection()->get_selected();
    if(it){
        std::string letter;
        it->get_value(0, letter);
        gene_data.erase(letter.at(0));
        available_letters.at(letter.at(0)) = true;
        records.remove_row_by_iterator(it);
        records.update_data_package();
    }
    unsigned rows = records.n_rows();
    if(rows < 1){
        calc_button.set_sensitive(false);
    }
}

std::vector<char> prob_panel::get_available_letters_vec(){
    std::vector<char> result;
    for(auto const & [letter, available] : available_letters){
        if(available) result.push_back(letter);
    }
    return result;
}
