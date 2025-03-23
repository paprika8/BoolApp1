flags := -std=c++17 -fpermissive -g

.PHONY: all clear
all: tasks\task_8\task_8.exe
	
tasks\task_8\task_8.exe: terms\term.o tasks\task_8\term.to
	g++ $(flags) terms\term.o tasks\task_8\term.to -o tasks\task_8\task_8.exe

terms\term.o: terms\term.cpp
	g++ $(flags) -c terms\term.cpp -o terms\term.o

tasks\task_8\term.to: tasks\task_8\task_8.cpp
	g++ $(flags) -xc++ -c tasks\task_8\task_8.cpp -o tasks\task_8\term.to

clear:
