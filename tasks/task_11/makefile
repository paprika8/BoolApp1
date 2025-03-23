flags := -std=c++17 -fpermissive -g

.PHONY: all clear
all: tasks\task_11\task_11.exe
	
tasks\task_11\task_11.exe: terms\term.o tasks\task_11\term.to
	g++ $(flags) terms\term.o tasks\task_11\term.to -o tasks\task_11\task_11.exe

terms\term.o: terms\term.cpp
	g++ $(flags) -c terms\term.cpp -o terms\term.o

tasks\task_11\term.to: tasks\task_11\task_11.cpp
	g++ $(flags) -xc++ -c tasks\task_11\task_11.cpp -o tasks\task_11\term.to

clear:
