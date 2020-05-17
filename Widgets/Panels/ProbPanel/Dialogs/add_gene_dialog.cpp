#include "add_gene_dialog.hpp"
#include "../../../../Translations/strings.hpp"

add_gene_dialog::add_gene_dialog(std::string title, bool modal) 
: Gtk::Dialog(title, modal){
    gtk_elements_setup();    
}


void add_gene_dialog::gtk_elements_setup(){
    Gtk::Widget *all []= {&confirm_button, &cancel_button,
    &letter_label, &domination_label, &description_label,
    &letter_box, &domination_box, &description_box,
    &options_box, &letter_combobox, &domination_combobox,
    &description_entry};

    main_box = get_vbox();
    Gtk::Box * hboxes [] = {&letter_box, &domination_box, &description_box, &options_box};

    Gtk::Button * buttons [] = {&confirm_button, &cancel_button};
    int btn_text_idxs []= {STRING_CONFIRM, STRING_CANCEL};

    int label_text_idxs [] = {STRING_LETTER_MARK, STRING_DOMINATION_TYPE, STRING_DESCRIPTION};

    Gtk::Label * text_labels [] = {&letter_label, &domination_label, &description_label};

    int * label_txt_idx = label_text_idxs;

    for(auto & lp : text_labels){
        lp->set_halign(Gtk::Align::ALIGN_START);
        lp->set_margin_right(30);
        lp->set_text(STRINGS[*label_txt_idx]);
        label_txt_idx++;
        lp->set_hexpand(true);
        lp->set_vexpand(false);
    }

    main_box->set_orientation(Gtk::Orientation::ORIENTATION_VERTICAL);

    for(auto & hbp : hboxes){
        hbp->set_orientation(Gtk::Orientation::ORIENTATION_HORIZONTAL);
        hbp->set_hexpand(true);
        hbp->set_vexpand(true);
        hbp->set_spacing(15);
        main_box->add(*hbp);
    }

    int * btn_txt = btn_text_idxs;

    for(auto & bp : buttons){
        bp->set_label(STRINGS[*btn_txt]);
        btn_txt++;
        bp->set_hexpand(true);
    }

    Gtk::Widget * editables [] = {&description_entry, &domination_combobox, &letter_box};

    for(auto & ep : editables){
        ep->set_hexpand(true);
        ep->set_vexpand(false);
        ep->set_valign(Gtk::Align::ALIGN_CENTER);
    }

    for(char c = 'A'; c <= 'Z'; c++){
        letter_combobox.append(std::string{c}, std::string{c});
    }

    letter_combobox.set_active(0);

    std::string domtypes [] = {STRINGS[STRING_DOMINATION_FULL],
    STRINGS[STRING_DOMINATION_PARTIAL], STRINGS[STRING_DOMINATION_CODOMINANCE]};


    for(size_t i = 0; i < 3; i++){
        domination_combobox.append(std::string{domination_ids[i]}, domtypes[i]);
    }

    domination_combobox.set_active(0);

    options_box.add(confirm_button);
    options_box.add(cancel_button);

    letter_box.add(letter_label);
    letter_box.add(letter_combobox);

    domination_box.add(domination_label);
    domination_box.add(domination_combobox);

    description_box.add(description_label);
    description_box.add(description_entry);

    main_box->set_vexpand(true);
    main_box->set_spacing(5);

    for(auto & p : all){
        p->set_visible(true);
    }

    set_default_response(Gtk::ResponseType::RESPONSE_CANCEL);
    confirm_button.signal_clicked().connect(sigc::mem_fun(this, &add_gene_dialog::on_confirm_clicked));
    cancel_button.signal_clicked().connect([=](){response(Gtk::ResponseType::RESPONSE_CANCEL);});
}

void add_gene_dialog::on_confirm_clicked(){
    returned_values.letter = letter_combobox.get_active_id().at(0);
    returned_values.domination_type = letter_combobox.get_active_id().at(0);
    response(Gtk::ResponseType::RESPONSE_ACCEPT);
}