flags := -std=c++17 -fpermissive -g

.PHONY: all clear
all: tasks\task_2\task_2.exe
	
tasks\task_2\task_2.exe: terms\term.o tasks\task_2\term.to
	g++ $(flags) terms\term.o tasks\task_2\term.to -o tasks\task_2\task_2.exe

terms\term.o: terms\term.cpp
	g++ $(flags) -c terms\term.cpp -o terms\term.o

tasks\task_2\term.to: tasks\task_2\task_2.cpp
	g++ $(flags) -xc++ -c tasks\task_2\task_2.cpp -o tasks\task_2\term.to

clear:
