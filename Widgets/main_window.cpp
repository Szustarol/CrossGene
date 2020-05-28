#include "main_window.hpp"
#include "Panels/ProbPanel/prob_panel.hpp"
#include "../Translations/strings.hpp"

main_window::main_window() : Gtk::Window(){
    //panels.at(0) = std::make_unique<Gtk::Container>(new );
    this->set_titlebar(header_bar);
    header_bar.set_title(program_name);
    header_bar.set_show_close_button(true);
    header_bar.set_decoration_layout(":minimize,maximize,close");
    header_bar.set_visible(true);
    
    notebook.set_visible(true);
    
    add(notebook);

    set_default_size(800, 600);

    notebook.set_tab_pos(Gtk::PositionType::POS_TOP);

    panels.at(0) = std::unique_ptr<Gtk::Container>(new prob_panel());
    panels.at(0)->set_visible(true);

    notebook.append_page(*panels.at(0).get(), STRINGS[STRING_PROBABILITY_TAB_NAME]);
}