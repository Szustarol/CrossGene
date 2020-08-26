CCX=g++
CXXFLAGS=-std=c++17 -Wall -Wextra 
LIBS=
LANGUAGE_FILE=Translations/strings_english.cpp
BD=build
PKG_CONFIG=$(shell pkg-config gtkmm-3.0 --cflags --libs)
.PHONY=clean run
_=$(shell if [ ! -d build ]; then mkdir build; fi;)

run: crossgene.out
	./crossgene.out

crossgene.out: crossgene.cpp $(BD)/mainwindow.o $(BD)/strings.o
	$(CXX) $(CXXFLAGS) -o $@ build/* $< $(LIBS) $(PKG_CONFIG)

$(BD)/mainwindow.o: Widgets/main_window.cpp $(BD)/probpanel.o $(BD)/strings.o
	$(CXX) -c $(CXXFLAGS) -o $@ $< $(LIBS) $(PKG_CONFIG)

#Probability panel

$(BD)/probpanel.o: Widgets/Panels/ProbPanel/prob_panel.cpp program_data.hpp $(BD)/probpanelgtksetup.o $(BD)/addgenedialog.o $(BD)/calculatediagram.o
	$(CXX) -c $(CXXFLAGS) -o $@ $< $(LIBS) $(PKG_CONFIG)

$(BD)/probpanelgtksetup.o: Widgets/Panels/ProbPanel/prob_panel_gtk_setup.cpp $(BD)/strings.o $(BD)/recordmodel.o
	$(CXX) -c $(CXXFLAGS) -o $@ $< $(LIBS) $(PKG_CONFIG)

$(BD)/recordmodel.o: Widgets/Panels/ProbPanel/record_model.cpp program_data.hpp $(BD)/strings.o Widgets/Panels/ProbPanel/record_model.hpp
	$(CXX) -c $(CXXFLAGS) -o $@ $< $(LIBS) $(PKG_CONFIG)

$(BD)/addgenedialog.o: Widgets/Panels/ProbPanel/Dialogs/add_gene_dialog.cpp $(BD)/strings.o
	$(CXX) -c $(CXXFLAGS) -o $@ $< $(LIBS) $(PKG_CONFIG)


#Calculations

$(BD)/calculatediagram.o: Calculations/calculate_diagram.cpp program_data.hpp Calculations/calculate_diagram.hpp
	$(CXX) -c $(CXXFLAGS) -o $@ $< $(LIBS) $(PKG_CONFIG)


#Strings and globals

$(BD)/strings.o: $(LANGUAGE_FILE)
	$(CXX) -c $(CXXFLAGS) -o $@ $< $(LIBS) $(PKG_CONFIG)

clean:
	$(RM) crossgene.out
	$(RM) $(BD)/*
