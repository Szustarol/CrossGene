#ifndef ADD_GENE_DIALOG_HPP
#define ADD_GENE_DIALOG_HPP

#include <gtkmm.h>
#include "../../../../defines.hpp"
#include "../../../../program_data.hpp"
#include <map>

class add_gene_dialog : public Gtk::Dialog{
    Gtk::Button confirm_button;
    Gtk::Button cancel_button;
    Gtk::Label letter_label;
    Gtk::Label domination_label;
    Gtk::Label description_label; 
    Gtk::Label codomination_label;
    void gtk_elements_setup();

    Gtk::Box * main_box;
    Gtk::Box letter_box, domination_box, description_box, codomination_box, options_box;

    Gtk::ComboBoxText letter_combobox, domination_combobox;

    Gtk::Entry description_entry;
    Gtk::Entry codominance_entry;

    void on_confirm_clicked();

    void on_combobox_changed();

    void codominance_count_edited();

    bool codominance_focus_out(GdkEventFocus* event);

    unsigned n_codomin;

    public:

    static constexpr const char domination_ids[] = {
        'f', 'p', 'c'
    }; //full, partial, co-domination

    struct retvals{
        char letter;
        GENE_DOMINATION_TYPE domination_type;
        std::string description;
        int n_codominant;
    };

    retvals returned_values;

    void set_available_letters(std::vector<char> & letters);
    
    add_gene_dialog(std::string title, bool modal = true);

    void clear_buffers();
};

#endif