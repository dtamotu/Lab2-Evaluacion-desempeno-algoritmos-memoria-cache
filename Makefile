CXX = g++
CXXFLAGS = -std=c++14 -O2 -g

all: bucles clasica bloques

bucles: bucles.cpp
	$(CXX) $(CXXFLAGS) bucles.cpp -o bucles

clasica: clasica.cpp
	$(CXX) $(CXXFLAGS) clasica.cpp -o clasica

bloques: bloques.cpp
	$(CXX) $(CXXFLAGS) bloques.cpp -o bloques

clean:
	rm -f bucles clasica bloques
