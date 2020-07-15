#ifndef PROB_PANEL_HPP
#define PROB_PANEL_HPP

#include <gtkmm.h>
#include <utility>
#include "record_model.hpp"
#include "Dialogs/add_gene_dialog.hpp"

class prob_panel : public Gtk::Box{

    std::vector<std::pair<char, int>> gene_data_package;

    record_model records;

    Gtk::Frame gene_frame;

    Gtk::Box gene_setup_container;
    Gtk::Box gene_frame_buttons;

    add_gene_dialog add_gene_dial;

    Gtk::TreeView gene_selection_treeview;
    Gtk::ScrolledWindow gene_selection_window;

    std::map<char, bool> available_letters;

    Gtk::Button add_button, remove_button, calc_button;

    std::vector<char> get_available_letters_vec();

    void gtk_elements_setup();

    void on_add_gene_clicked();
    void on_remove_gene_clicked();
    void on_edit_gene_clicked();
    void on_treeview_changed();
    void on_calc_clicked();

    public:

    prob_panel();
};

#endif