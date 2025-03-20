SRC  := $(addprefix /,$(wildcard *.cpp)) #$(shell find . -name '*.cpp') #$(addprefix /,$(wildcard *.cpp))
HDR := $(wildcard *.h) #$(addprefix /,$(wildcard *.h)) #$(shell find . -name '*.h')
SRC_NAME := $(subst ./,/,$(SRC))
OBJS  := $(addprefix obj, $(SRC_NAME:.cpp=.o)) 
LIB := -lgdi32
FLAGS := -g -fpermissive -w -fcompare-debug-second -D UNICODE -std=c++20 -Wl,--subsystem,windows
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