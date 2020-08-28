#ifndef RESULT_PANEL_HPP
#define RESULT_PANEL_HPP

#include <gtkmm.h>
#include "../../../program_data.hpp"

class result_panel : public Gtk::Box{

    Gtk::Grid main_grid;
    Gtk::Box main_vbox;
    Gtk::Frame main_frame;
    Gtk::ScrolledWindow main_scroll;

    std::vector<Gtk::Label> grid_labels;
    std::vector<Gtk::Frame> grid_frames;

    public:
    
    result_panel(const std::vector<std::vector<calculation_result>> & c_results, 
        std::vector<whole_gamete> & gamete_1_set, std::vector<whole_gamete> & gamete_2_set,
        const std::string & title = "");

};

#endif