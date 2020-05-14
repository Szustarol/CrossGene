#include "prob_panel.hpp"
#include "../../Translations/strings.hpp"


prob_panel::prob_panel() : Gtk::Box(Gtk::Orientation::ORIENTATION_HORIZONTAL){
    gene_frame.set_visible(true);
    gene_frame.set_label(STRINGS[STRING_GENE_LIST]);
    gene_frame.set_hexpand(true);
    set_border_width(10);
    
    add(gene_frame);
    set_spacing(10);

    gene_selection_treeview = Gtk::TreeView();
    gene_selection_treeview.set_visible(true);
    gene_selection_window.set_visible(true);

    std::vector<std::string> columns{STRINGS[STRING_LETTER_MARK],
    STRINGS[STRING_DOMINATION_TYPE], STRINGS[STRING_DESCRIPTION]};
    
    records.set_records_and_install<int, double, std::string>(columns, gene_selection_treeview);
    
    //gene_selection_treeview.set_model(Gtk::ListStore::create(records));



    gene_frame.add(gene_selection_window);
    gene_selection_window.set_vexpand(true);
    gene_selection_window.set_hexpand(true);
    gene_selection_window.add(gene_selection_treeview);
    gene_selection_window.set_policy(Gtk::PolicyType::POLICY_AUTOMATIC, Gtk::PolicyType::POLICY_AUTOMATIC);

    

    
}