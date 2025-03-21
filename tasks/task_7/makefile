flags := -std=c++17 -fpermissive -g

.PHONY: all clear
all: tasks\task_7\task_7.exe
	
tasks\task_7\task_7.exe: terms\term.o tasks\task_7\term.to
	g++ $(flags) terms\term.o tasks\task_7\term.to -o tasks\task_7\task_7.exe

terms\term.o: terms\term.cpp
	g++ $(flags) -c terms\term.cpp -o terms\term.o

tasks\task_7\term.to: tasks\task_7\task_7.cpp
	g++ $(flags) -xc++ -c tasks\task_7\task_7.cpp -o tasks\task_7\term.to

clear:
