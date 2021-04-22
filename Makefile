
comp = clang++

FLAGS = -O2
LIBS = -lSDL2_ttf -lSDL2_gfx -lSDL2

FILES = main.cpp src/*.cpp

build : $(FILES) Makefile
	$(comp) -o build/boxworld $(FILES) $(LIBS) $(FLAGS) -I src

dbuild : $(FILES) Makefile
	$(comp) -o build/boxworld_debug $(FILES) $(LIBS) $(FLAGS) -I src -Wall -g

run: build
	./build/boxworld

debug : dbuild
	./build/boxworld_debug

all: build dbuild
	echo "compiled all"
emscripten: $(FILES)
	source "/usr/lib/emsdk/emsdk_env.sh"  
	sudo em++ $(FILES) $(FLAGS) -s USE_SDL=2 -I src -I /usr/include

clean: 
	rm build/boxworld
	rm build/boxworld_debug
