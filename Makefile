build:
	g++ -Wall -std=c++17 -I"./libs/" ./src/*.cpp -lSDL2 -lSDL2_image -lSDL2_ttf -llua5.3 -lm -o gameengine;
run:
	./gameengine
clear:
	rm gameengine