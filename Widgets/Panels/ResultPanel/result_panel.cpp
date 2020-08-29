#include "result_panel.hpp"
#include "../../../Calculations/calculate_diagram.hpp"
#include "../../../Translations/strings.hpp"

Gdk::RGBA result_panel::get_color_by_index(int index, int max_index, int palette){
    float partition = (((float)index)/(max_index));
    Gdk::RGBA r;

    if(max_index == 0){
        r.set_alpha(1);
        r.set_blue(0);
        r.set_green(0);
        r.set_red(0);
        return r;
    }

    if(palette == 0){
        r.set_green(partition);
        r.set_red(1-partition);
        r.set_green(0);
        r.set_alpha(0.2);
    }
    else{
        r.set_blue(partition);
        r.set_red(1-partition);
        r.set_blue(0);
        r.set_alpha(1);
    }
    return r;
}

result_panel::result_panel(const std::vector<std::vector<calculation_result>> & c_results, 
        std::vector<whole_gamete> & gamete_1_set, std::vector<whole_gamete> & gamete_2_set,
        unsigned n_genotypes, unsigned n_phenotypes, 
        const std::vector<std::string> & genotype_names, 
        const std::vector<std::string> & phenotype_names,
        const std::string & title):
        genotypes_box(Gtk::Orientation::ORIENTATION_VERTICAL),
        phenotypes_box(Gtk::Orientation::ORIENTATION_VERTICAL),
        genotypes_label(STRINGS[STRING_GENOTYPES]),
        phenotypes_label(STRINGS[STRING_PHENOTYPES]){
    

    Gtk::Widget * all_objs[] = {&main_vbox, &main_grid, &main_frame, &main_scroll,
    &type_frame, &n_genotypes_label, &n_phenotypes_label, &types_vbox,
    &type_frame_box, &types_h_box, &genotypes_box, &phenotypes_box,
    &genotypes_label, &phenotypes_label};

    types_vbox = Gtk::Box(Gtk::Orientation::ORIENTATION_VERTICAL);

    main_vbox = Gtk::Box(Gtk::Orientation::ORIENTATION_VERTICAL);
    this->pack_start(main_scroll);
    main_scroll.add(main_vbox);
    type_frame_box.pack_start(type_frame);
    main_vbox.pack_start(type_frame_box, false, true);
    main_vbox.pack_end(main_frame, true, true);
    main_frame.add(main_grid);
    main_frame.set_border_width(5);
    type_frame.set_border_width(5);

    type_frame.add(types_vbox);

    types_vbox.pack_start(n_genotypes_label);
    types_vbox.pack_start(n_phenotypes_label);
    types_vbox.pack_end(types_h_box);

    types_h_box.pack_start(genotypes_box);
    types_h_box.pack_end(phenotypes_box);

    

    genotypes_box.pack_start(genotypes_label);
    phenotypes_box.pack_start(phenotypes_label);

    n_phenotypes_label.set_text(Glib::ustring(STRINGS[STRING_N_PHENOTYPES]) + Glib::ustring::format(n_phenotypes));
    n_genotypes_label.set_text(Glib::ustring(STRINGS[STRING_N_GENOTYPES]) + Glib::ustring::format(n_genotypes));

    n_phenotypes_label.set_alignment(Gtk::Align::ALIGN_START);
    n_genotypes_label.set_alignment(Gtk::Align::ALIGN_START);

    n_genotypes_label.set_margin_left(5);
    n_phenotypes_label.set_margin_left(5);

    types_h_box.set_hexpand(true);
    types_h_box.set_halign(Gtk::Align::ALIGN_START);

    genotypes_box.set_margin_top(10);
    genotypes_box.set_margin_left(10);
    phenotypes_box.set_margin_top(10);
    phenotypes_box.set_margin_left(10);

    phenotypes_label.set_halign(Gtk::Align::ALIGN_START);

    phenotypes_box.set_valign(Gtk::Align::ALIGN_START);
    genotypes_box.set_valign(Gtk::Align::ALIGN_START);

    std::vector<Gdk::RGBA> genotype_colors;
    std::vector<Gdk::RGBA> phenotype_colors;

    for(unsigned index = 0; index < n_genotypes; index++){
        genotype_colors.push_back(
            get_color_by_index(index, n_genotypes-1, 0)
        );
        if(index < n_phenotypes)
            phenotype_colors.push_back(
                get_color_by_index(index, n_phenotypes-1, 1)
            );
    }


    unsigned index = 0;

    for(auto & str : genotype_names){
        genotype_labels.push_back(Gtk::Label());
        genotype_labels.back().set_markup(str);
        genotype_labels.back().set_visible(true);
        genotype_labels.back().override_background_color(genotype_colors.at(index));
        genotypes_box.add(genotype_labels.back());

        index++;
    }

    index = 0;
    for(auto & str : phenotype_names){
        phenotype_labels.push_back(Gtk::Label());
        phenotype_labels.back().set_markup(str);
        phenotype_labels.back().set_visible(true);
        phenotype_labels.back().override_color(phenotype_colors.at(index));
        phenotypes_box.add(phenotype_labels.back());
        index++;
    }


    main_scroll.set_policy(Gtk::PolicyType::POLICY_AUTOMATIC, Gtk::PolicyType::POLICY_AUTOMATIC);

    for(auto & ptr : all_objs)
        ptr->set_visible(true);

    unsigned sq_size = gamete_1_set.size();

    std::string temp = "<b>"; //parse title string

    for(auto c : title){
        if(isalpha(c)) temp += c;
        else temp += "<sub>" + std::string(1, c) + "</sub>";
    }

    temp += "</b>";

    main_grid.set_margin_left(20);
    main_grid.set_margin_top(20);
    main_grid.set_margin_bottom(20);
    main_grid.set_margin_right(20);

    //fill first cell - crossing
    grid_labels.push_back(Gtk::Label());
    grid_frames.push_back(Gtk::Frame());
    grid_frames.back().set_label_widget(grid_labels.back());
    grid_frames.back().override_background_color(Gdk::RGBA("#b3b3b3"));
    main_grid.attach(grid_frames.back(), 0, 0);
    grid_frames.back().set_visible(true);
    grid_labels.back().set_visible(true);
    grid_labels.back().set_markup(temp);


    for(unsigned gamete = 0; gamete < sq_size; gamete++){
        auto & g1 = gamete_1_set.at(gamete);
        auto & g2 = gamete_2_set.at(gamete);

        grid_frames.push_back(Gtk::Frame());
        grid_frames.back().set_visible(true);
        grid_labels.push_back(Gtk::Label());
        grid_labels.back().set_markup(gamete_to_string(g1));
        grid_labels.back().set_visible(true);
        grid_frames.back().add(grid_labels.back());
        grid_frames.back().override_background_color(Gdk::RGBA("#b3b3b3"));
        main_grid.attach(grid_frames.back(), 0, gamete+1);

        grid_frames.push_back(Gtk::Frame());
        grid_frames.back().set_visible(true);
        grid_labels.push_back(Gtk::Label());
        grid_labels.back().set_markup(gamete_to_string(g2));
        grid_labels.back().set_visible(true);
        grid_frames.back().add(grid_labels.back());
        grid_frames.back().override_background_color(Gdk::RGBA("#b3b3b3"));
        main_grid.attach(grid_frames.back(), gamete+1, 0);
    }

    for(unsigned row = 0; row < sq_size; row++){
        for(unsigned col = 0; col < sq_size; col++){
            grid_frames.push_back(Gtk::Frame());
            grid_frames.back().set_visible(true);
            grid_labels.push_back(Gtk::Label());
            grid_labels.back().set_markup(c_results.at(row).at(col).string_representation);
            grid_labels.back().set_visible(true);
            grid_labels.back().set_margin_left(3);
            grid_labels.back().set_margin_right(3);
            grid_labels.back().set_margin_top(3);
            grid_labels.back().set_margin_bottom(3);
            grid_labels.back().override_background_color(
                genotype_colors.at(
                    c_results.at(row).at(col).genotype_index
                )
            );
            grid_labels.back().override_color(
                phenotype_colors.at(
                    c_results.at(row).at(col).phenotype_index
                )
            );
            grid_frames.back().add(grid_labels.back());
            main_grid.attach(grid_frames.back(), row+1, col+1);
        }
    }


}