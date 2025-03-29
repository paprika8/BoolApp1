DIRS := button Edit component composite LinearContainer Text window design tasks/task_1 tasks/task_2 tasks/task_3 tasks/task_5 tasks/task_8 tasks/task_9 tasks/task_12 terms 

SRC  := $(addprefix /,$(wildcard *.cpp))  $(foreach dir,$(DIRS), $(addprefix /,$(wildcard $(dir)/*.cpp)))          #$(shell find . -name '*.cpp') #$(addprefix /,$(wildcard *.cpp))
HDR := $(wildcard *.h)  $(foreach dir,$(DIRS), $(wildcard $(dir)/*.h))                              #$(addprefix /,$(wildcard *.h)) #$(shell find . -name '*.h')
SRC_NAME := $(subst ./,/,$(SRC))
OBJS  := $(addprefix obj, $(SRC_NAME:.cpp=.o)) 
LIB := -lgdiplus -lgdi32
FLAGS := -g -fpermissive -w -D UNICODE -std=c++20 -Wl,--subsystem,windows  #-fcompare-debug-second
ARGS := $(FLAGS)
.PHONY: all clear clear_all

all: build/BoolApp.exe

rebuild: clear all

build/BoolApp.exe:  $(OBJS)
	g++ $(ARGS) $(OBJS) -o build/BoolApp.exe $(LIB)

obj/%.co: %.c $(HDR)
	gcc $(ARGS) $(INCLUDE) -c $< -o $@

obj/%.o:  %.cpp $(HDR)
	@mkdir -p $(dir $@)
	g++ $(ARGS) $(INCLUDE) -c $< -o $@

clear: 
	rm -f obj/*.o

clear_all: clear
	rm -f build/BoolApp.exe