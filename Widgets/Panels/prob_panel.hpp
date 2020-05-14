#ifndef PROB_PANEL_HPP
#define PROB_PANEL_HPP

#include <gtkmm.h>
#include <utility>
#include "record_model.hpp"

class prob_panel : public Gtk::Box{

    record_model records;

    Gtk::Frame gene_frame;

    Gtk::TreeView gene_selection_treeview;
    Gtk::ScrolledWindow gene_selection_window;

    public:
    prob_panel();
};

#endif