CCX=g++
CXXFLAGS=-std=c++17 -Wall -Wextra
LIBS=

crossgene.out: crossgene.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

clean:
	$(RM) crossgene.out
