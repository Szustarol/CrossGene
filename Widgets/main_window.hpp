#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <gtkmm.h>
#include <array>
#include <utility>

class main_window : public Gtk::Window{
    Gtk::HeaderBar header_bar;

    Gtk::Notebook notebook;
    
    std::vector<std::shared_ptr<Gtk::Container>> panels;

    public:
    main_window();


};

#endif