flags := -std=c++17 -fpermissive -g

.PHONY: all clear
all: tasks\task_12\task_12.exe
	
tasks\task_12\task_12.exe: terms\term.o tasks\task_12\term.to
	g++ $(flags) terms\term.o tasks\task_12\term.to -o tasks\task_12\task_12.exe

terms\term.o: terms\term.cpp
	g++ $(flags) -c terms\term.cpp -o terms\term.o

tasks\task_12\term.to: tasks\task_12\task_12.cpp
	g++ $(flags) -xc++ -c tasks\task_12\task_12.cpp -o tasks\task_12\term.to

clear:
