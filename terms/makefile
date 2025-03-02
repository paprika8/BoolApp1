flags := -std=c++17 -fpermissive

.PHONY: all clear
all: terms\term.exe
	
terms\term.exe: terms\term.o terms\term.to
	gcc $(flags) terms\term.o terms\term.to -o terms\term.exe

terms\term.o: terms\term.cpp
	gcc $(flags) -c terms\term.cpp -o terms\term.o

terms\term.to: terms\term.test
	gcc $(flags) -xc++ -c terms\term.test -o terms\term.to

clear:
