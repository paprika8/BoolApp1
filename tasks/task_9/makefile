flags := -std=c++17 -fpermissive -g

.PHONY: all clear
all: tasks\task_9\task_9.exe
	
tasks\task_9\task_9.exe: terms\term.o tasks\task_9\term.to
	g++ $(flags) terms\term.o tasks\task_9\term.to -o tasks\task_9\task_9.exe

terms\term.o: terms\term.cpp
	g++ $(flags) -c terms\term.cpp -o terms\term.o

tasks\task_9\term.to: tasks\task_9\task_9.cpp
	g++ $(flags) -xc++ -c tasks\task_9\task_9.cpp -o tasks\task_9\term.to

clear:
