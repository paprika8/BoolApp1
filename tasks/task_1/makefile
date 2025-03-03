flags := -std=c++17 -fpermissive -g

.PHONY: all clear
all: tasks\task_1\task_1.exe
	
tasks\task_1\task_1.exe: terms\term.o tasks\task_1\term.to
	g++ $(flags) terms\term.o tasks\task_1\term.to -o tasks\task_1\task_1.exe

terms\term.o: terms\term.cpp
	g++ $(flags) -c terms\term.cpp -o terms\term.o

tasks\task_1\term.to: tasks\task_1\task_1.cpp
	g++ $(flags) -xc++ -c tasks\task_1\task_1.cpp -o tasks\task_1\term.to

clear:
