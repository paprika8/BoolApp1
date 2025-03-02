flags := -std=c++17 -fpermissive -g

.PHONY: all clear
all: terms\term.exe
	
terms\term.exe: terms\term.o terms\term.to
	g++ $(flags) terms\term.o terms\term.to -o terms\term.exe

terms\term.o: terms\term.cpp
	g++ $(flags) -c terms\term.cpp -o terms\term.o

terms\term.to: terms\termtest.cpp
	g++ $(flags) -xc++ -c terms\termtest.cpp -o terms\term.to

clear:
