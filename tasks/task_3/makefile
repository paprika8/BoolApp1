flags := -std=c++17 -fpermissive -g

.PHONY: all clear
all: tasks\task_3\task_3.exe
	
tasks\task_3\task_3.exe: terms\term.o tasks\task_3\term.to
	g++ $(flags) terms\term.o tasks\task_3\term.to -o tasks\task_3\task_3.exe

terms\term.o: terms\term.cpp
	g++ $(flags) -c terms\term.cpp -o terms\term.o

tasks\task_3\term.to: tasks\task_3\task_3.cpp
	g++ $(flags) -xc++ -c tasks\task_3\task_3.cpp -o tasks\task_3\term.to

clear:
