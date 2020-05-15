#ifndef ADD_GENE_DIALOG_HPP
#define ADD_GENE_DIALOG_HPP

#include <gtkmm.h>

class add_gene_dialog : public Gtk::Dialog{
    Gtk::Button confirm_button;
    Gtk::Button cancel_button;
    Gtk::Label letter_label;
    Gtk::Label domination_label;
    Gtk::Label description_label; 
    void gtk_elements_setup();

    Gtk::Box main_box;
    Gtk::Box letter_box, domination_box, description_box, options_box;

    public:

    add_gene_dialog(std::string title);
};

#endif