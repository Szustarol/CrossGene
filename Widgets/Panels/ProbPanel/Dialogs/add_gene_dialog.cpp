#include "add_gene_dialog.hpp"
#include "../../../../Translations/strings.hpp"

add_gene_dialog::add_gene_dialog(std::string title) : Gtk::Dialog(title){
    gtk_elements_setup();
}


void add_gene_dialog::gtk_elements_setup(){
    Gtk::Widget *all []= {&confirm_button, &cancel_button,
    &letter_label, &domination_label, &description_label,
    &main_box, &letter_box, &domination_box, &description_box,
    &options_box};

    Gtk::Box * hboxes [] = {&letter_box, &domination_box, &description_box, &options_box};

    Gtk::Button * buttons [] = {&confirm_button, &cancel_button};
    int btn_text_idxs []= {STRING_CONFIRM, STRING_CANCEL};

    main_box.set_orientation(Gtk::Orientation::ORIENTATION_VERTICAL);

    for(auto & hbp : hboxes){
        hbp->set_orientation(Gtk::Orientation::ORIENTATION_HORIZONTAL);
        main_box.add(*hbp);
    }

    int * btn_txt = btn_text_idxs;

    for(auto & bp : buttons){
        bp->set_label(STRINGS[*btn_txt]);
        btn_txt++;
    }

    options_box.add(confirm_button);
    options_box.add(cancel_button);

    get_vbox()->add(main_box);

    for(auto & p : all){
        p->set_visible(true);
    }

}