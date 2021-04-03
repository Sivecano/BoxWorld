build : main.cpp src/*.cpp Makefile
	g++ -o build/boxworld main.cpp src/*.cpp -lSDL2 -I src -lSDL2_ttf -O2

dbuild : main.cpp src/*.cpp Makefile
	g++ -o build/boxworld_debug main.cpp src/*.cpp -lSDL2 -I src -lSDL2_ttf -Wall -g -O2

run: build
	./build/boxworld

debug : dbuild
	./build/boxworld_debug

clean: 
	rm build/boxworld
	rm build/boxworld_debug