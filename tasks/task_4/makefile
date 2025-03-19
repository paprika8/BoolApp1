flags := -std=c++17 -fpermissive -g

.PHONY: all clear
all: tasks\task_4\task_4.exe
	
tasks\task_4\task_4.exe: terms\term.o tasks\task_4\term.to
	g++ $(flags) terms\term.o tasks\task_4\term.to -o tasks\task_4\task_4.exe

terms\term.o: terms\term.cpp
	g++ $(flags) -c terms\term.cpp -o terms\term.o

tasks\task_4\term.to: tasks\task_4\task_4.cpp
	g++ $(flags) -xc++ -c tasks\task_4\task_4.cpp -o tasks\task_4\term.to

clear:
