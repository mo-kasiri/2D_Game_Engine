###########################################################
# Declare some Makefile variables
###########################################################

ifeq ($(OS), Windows NT)
	CC=msvc
else
	CC=g++
endif

LANG_STD = -std=c++17
COMPILER_FLAGS = -Wall -Wfatal-errors
INCLUDE_PATH = -I"./libs/"
SRC_FILES = ./src/*.cpp \
			./src/Game/*.cpp
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -llua5.3 -lm
OBJ_NAME = gameengine

###########################################################
# Declare some Makefile Rules
###########################################################

build:
	$(CC) $(COMPILER_FLAGS) $(LANG_STD) $(INCLUDE_PATH) $(SRC_FILES) $(LINKER_FLAGS) -o $(OBJ_NAME);
run:
	./$(OBJ_NAME)
clear:
	rm $(OBJ_NAME)