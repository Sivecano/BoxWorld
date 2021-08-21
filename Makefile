
comp = clang++

FLAGS = -O2
LIBS = -lSDL2_ttf -lSDL2_gfx -lSDL2

OBJECTS = main.o src/boxbase.o src/circlecollider.o src/events.o src/vector.o

build : $(OBJECTS) Makefile
	$(comp) -o build/boxworld $(OBJECTS) $(LIBS) $(FLAGS) -I src

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

%.o: %.cpp
	$(comp) -c $< -o $@ $(FLAGS) -I src

clean: 
	rm build/boxworld
	rm build/boxworld_debug
