#include <iostream>
#include "defines.hpp"
#include "Translations/strings.hpp"
#include "Widgets/main_window.hpp"
#include <gtkmm.h>

int main(int argc, char ** argv){
    if constexpr(DEBUG_MODE){
        std::cout << program_name << " is starting." << std::endl;
    }

    auto app = Gtk::Application::create(argc, argv, "gene.cross");

    main_window mw;

    return app->run(mw);

    return 0;
}