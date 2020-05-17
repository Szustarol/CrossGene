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

    Gtk::Box * main_box;
    Gtk::Box letter_box, domination_box, description_box, options_box;

    Gtk::ComboBoxText letter_combobox, domination_combobox;

    Gtk::Entry description_entry;

    void on_confirm_clicked();

    public:

    static constexpr const char domination_ids[] = {
        'f', 'p', 'c'
    }; //full, partial, co-domination

    struct retvals{
        char letter;
        char domination_type;
        std::string description;
    };

    retvals returned_values;

    add_gene_dialog(std::string title, bool modal = true);
};

#endif