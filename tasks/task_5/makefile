flags := -std=c++17 -fpermissive -g

.PHONY: all clear
all: tasks\task_5\task_5.exe
	
tasks\task_5\task_5.exe: terms\term.o tasks\task_5\term.to
	g++ $(flags) terms\term.o tasks\task_5\term.to -o tasks\task_5\task_5.exe

terms\term.o: terms\term.cpp
	g++ $(flags) -c terms\term.cpp -o terms\term.o

tasks\task_5\term.to: tasks\task_5\task_5.cpp
	g++ $(flags) -xc++ -c tasks\task_5\task_5.cpp -o tasks\task_5\term.to

clear:
