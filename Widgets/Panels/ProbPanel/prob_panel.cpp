#include "prob_panel.hpp"
#include "../../../Translations/strings.hpp"
#include "../../../defines.hpp"

#if DEBUG_MODE
    #include <iostream>
#endif

prob_panel::prob_panel() : Gtk::Box(Gtk::Orientation::ORIENTATION_HORIZONTAL),
add_gene_dial(STRINGS[STRING_ADD_GENE], true){
    gtk_elements_setup();

    add_button.signal_clicked().connect(sigc::mem_fun(this, &prob_panel::on_add_gene_clicked));
}

void prob_panel::on_add_gene_clicked(){
    int response = add_gene_dial.run();
    switch(response){
        case Gtk::ResponseType::RESPONSE_CANCEL:
        case Gtk::ResponseType::RESPONSE_CLOSE:
        case Gtk::ResponseType::RESPONSE_DELETE_EVENT:
            add_gene_dial.hide();
            break;
        case Gtk::ResponseType::RESPONSE_APPLY:
            add_gene_dial.hide();
            records.add_row(add_gene_dial.returned_values.letter,
            add_gene_dial.returned_values.domination_type,
            add_gene_dial.returned_values.description);
            break;
        default:
            if constexpr(DEBUG_MODE){
                std::cerr << "Unknown dialog response: " << response << std::endl;
            }
    }
    add_gene_dial.clear_buffers();
}