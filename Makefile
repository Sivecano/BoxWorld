build : main.cpp src/*.cpp
	g++ -o build/boxworld main.cpp src/*.cpp -lSDL2 -I src

run: build
	./build/boxworld

clean: build
	rm build/boxworld