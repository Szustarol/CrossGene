#ifndef RESULT_PANEL_HPP
#define RESULT_PANEL_HPP

#include <gtkmm.h>
#include "../../../program_data.hpp"

class result_panel : public Gtk::Box{

    Gtk::Grid main_grid;
    Gtk::Box main_vbox, type_frame_box, types_h_box, genotypes_box, phenotypes_box;
    Gtk::Frame main_frame;
    Gtk::Frame type_frame;
    Gtk::ScrolledWindow main_scroll;

    std::vector<Gtk::Label> grid_labels;
    std::vector<Gtk::Label> genotype_labels;
    std::vector<Gtk::Label> phenotype_labels;
    std::vector<Gtk::Frame> grid_frames;

    Gtk::Label n_genotypes_label, n_phenotypes_label;
    Gtk::Label genotypes_label, phenotypes_label;
    Gtk::Box types_vbox;
    
    public:
    
    static Gdk::RGBA get_color_by_index(int index, int max_index, int palette);

    result_panel(const std::vector<std::vector<calculation_result>> & c_results, 
        std::vector<whole_gamete> & gamete_1_set, std::vector<whole_gamete> & gamete_2_set,
        unsigned n_genotypes, unsigned n_phenotypes, 
        const std::vector<std::string> & genotype_names, 
        const std::vector<std::string> & phenotype_names,
        const std::string & title = "");

};

#endif