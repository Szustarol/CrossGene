#include "result_panel.hpp"
#include "../../../Calculations/calculate_diagram.hpp"

result_panel::result_panel(const std::vector<std::vector<calculation_result>> & c_results,
std::vector<whole_gamete> & gamete_1_set, std::vector<whole_gamete> & gamete_2_set,
const std::string & title){
    

    Gtk::Widget * all_objs[] = {&main_vbox, &main_grid, &main_frame, &main_scroll};
    main_vbox = Gtk::Box(Gtk::Orientation::ORIENTATION_VERTICAL);
    this->pack_start(main_scroll);
    main_scroll.add(main_vbox);
    main_vbox.pack_start(main_frame);
    main_frame.add(main_grid);
    main_frame.set_border_width(5);

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
            grid_frames.back().add(grid_labels.back());
            main_grid.attach(grid_frames.back(), row+1, col+1);
        }
    }


}