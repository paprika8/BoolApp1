flags := -std=c++17 -fpermissive -g

.PHONY: all clear
all: tasks\task_10\task_10.exe
	
tasks\task_10\task_10.exe: terms\term.o tasks\task_10\term.to
	g++ $(flags) terms\term.o tasks\task_10\term.to -o tasks\task_10\task_10.exe

terms\term.o: terms\term.cpp
	g++ $(flags) -c terms\term.cpp -o terms\term.o

tasks\task_10\term.to: tasks\task_10\task_10.cpp
	g++ $(flags) -xc++ -c tasks\task_10\task_10.cpp -o tasks\task_10\term.to

clear:
