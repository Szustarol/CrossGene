#ifndef PROB_PANEL_HPP
#define PROB_PANEL_HPP

#include <gtkmm.h>
#include <utility>
#include "record_model.hpp"
#include "Dialogs/add_gene_dialog.hpp"

class prob_panel : public Gtk::Box{

    record_model records;

    Gtk::Frame gene_frame;

    Gtk::Box gene_setup_container;
    Gtk::Box gene_frame_buttons;

    add_gene_dialog add_gene_dial;

    Gtk::TreeView gene_selection_treeview;
    Gtk::ScrolledWindow gene_selection_window;

    Gtk::Button add_button, edit_button, remove_button;

    void gtk_elements_setup();

    public:
    prob_panel();
};

#endif