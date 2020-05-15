#include "prob_panel.hpp"
#include "../../../Translations/strings.hpp"

void prob_panel::gtk_elements_setup(){
    Gtk::Widget *all[] = {&gene_frame, & gene_selection_treeview,
    &gene_selection_window, &gene_setup_container, &gene_frame_buttons,
    &add_gene_dial, &add_button, &edit_button, &remove_button};

    Gtk::Button *btns[] = {&add_button, &edit_button, &remove_button};
    int btn_label_ids[] = {STRING_ADD_GENE, STRING_EDIT_GENE, STRING_REMOVE_GENE}; 

    gene_frame.set_label(STRINGS[STRING_GENE_LIST]);
    gene_frame.set_hexpand(true);
    set_border_width(10);
    
    add(gene_setup_container);
    set_spacing(10);

    gene_selection_treeview = Gtk::TreeView();

    std::vector<std::string> columns{STRINGS[STRING_LETTER_MARK],
    STRINGS[STRING_DOMINATION_TYPE], STRINGS[STRING_DESCRIPTION]};
    
    records.set_records_and_install<int, double, std::string>(columns, gene_selection_treeview);
    
    gene_setup_container.set_orientation(Gtk::Orientation::ORIENTATION_VERTICAL);

    gene_setup_container.add(gene_frame);

    gene_frame.add(gene_selection_window);
    gene_selection_window.set_vexpand(true);
    gene_selection_window.set_hexpand(true);
    gene_selection_window.add(gene_selection_treeview);
    gene_selection_window.set_policy(Gtk::PolicyType::POLICY_AUTOMATIC, Gtk::PolicyType::POLICY_AUTOMATIC);

    gene_frame_buttons.set_orientation(Gtk::Orientation::ORIENTATION_HORIZONTAL);

    int * labels = btn_label_ids;

    for(auto & bp : btns){
        gene_frame_buttons.add(*bp);
        bp->set_label(STRINGS[*labels]);
        labels++;
    }

    gene_setup_container.add(gene_frame_buttons);

    for(auto & p : all)
        p->set_visible(true);
}