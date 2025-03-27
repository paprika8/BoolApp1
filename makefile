DIRS := button Edit component composite LinearContainer Text window design

SRC  := $(addprefix /,$(wildcard *.cpp))  $(foreach dir,$(DIRS), $(addprefix /,$(wildcard $(dir)/*.cpp)))          #$(shell find . -name '*.cpp') #$(addprefix /,$(wildcard *.cpp))
HDR := $(wildcard *.h)  $(foreach dir,$(DIRS), $(wildcard $(dir)/*.h))                              #$(addprefix /,$(wildcard *.h)) #$(shell find . -name '*.h')
SRC_NAME := $(subst ./,/,$(SRC))
OBJS  := $(addprefix obj, $(SRC_NAME:.cpp=.o)) 
LIB := -lgdiplus -lgdi32
FLAGS := -g -fpermissive -w -D UNICODE -std=c++20 -Wl,--subsystem,windows #-fcompare-debug-second
ARGS := $(FLAGS)
.PHONY: all clean cleanall

all: build/BoolApp.exe

rebuild: clean all

build/BoolApp.exe:  $(OBJS)
	g++ $(ARGS) $(OBJS) -o build/BoolApp.exe $(LIB)

obj/%.co: %.c $(HDR)
	gcc $(ARGS) $(INCLUDE) -c $< -o $@

obj/%.o:  %.cpp $(HDR)
	@mkdir -p $(dir $@)
	g++ $(ARGS) $(INCLUDE) -c $< -o $@

clean: 
	rm -f obj/*.o

cleanall: clean
	rm -f build/BoolApp.exe