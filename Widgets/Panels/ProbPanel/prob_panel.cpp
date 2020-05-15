#include "prob_panel.hpp"
#include "../../../Translations/strings.hpp"

prob_panel::prob_panel() : Gtk::Box(Gtk::Orientation::ORIENTATION_HORIZONTAL),
add_gene_dial(program_name){
    gtk_elements_setup();
}