flags := -std=c++17 -fpermissive -g

.PHONY: all clear
all: tasks\task_6\task_6.exe
	
tasks\task_6\task_6.exe: terms\term.o tasks\task_6\term.to
	g++ $(flags) terms\term.o tasks\task_6\term.to -o tasks\task_6\task_6.exe

terms\term.o: terms\term.cpp
	g++ $(flags) -c terms\term.cpp -o terms\term.o

tasks\task_6\term.to: tasks\task_6\task_6.cpp
	g++ $(flags) -xc++ -c tasks\task_6\task_6.cpp -o tasks\task_6\term.to

clear:
