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

$(BD)/probpanel.o: Widgets/Panels/prob_panel.cpp $(BD)/strings.o $(BD)/recordmodel.o
	$(CXX) -c $(CXXFLAGS) -o $@ $< $(LIBS) $(PKG_CONFIG)

$(BD)/recordmodel.o: Widgets/Panels/record_model.cpp  Widgets/Panels/record_model.hpp
	$(CXX) -c $(CXXFLAGS) -o $@ $< $(LIBS) $(PKG_CONFIG)

$(BD)/strings.o: $(LANGUAGE_FILE)
	$(CXX) -c $(CXXFLAGS) -o $@ $< $(LIBS) $(PKG_CONFIG)

clean:
	$(RM) crossgene.out
	$(RM) $(BD)/*
