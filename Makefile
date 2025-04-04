# Variables
SRC_DIR = src
BUILD_DIR = build/debug
CC = g++
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_NAME = play

# Paths
INCLUDE_PATHS = -Iinclude -I/opt/homebrew/Cellar/sdl2/2.32.2/include -I/opt/homebrew/Cellar/sdl2/2.32.2/include/SDL2 -I/opt/homebrew/Cellar/sdl2_image/2.8.8/include -I/opt/homebrew/Cellar/sdl2_ttf/2.24.0/include
LIBRARY_PATHS = -L/opt/homebrew/Cellar/sdl2/2.32.2/lib -L/opt/homebrew/Cellar/sdl2_image/2.8.8/lib -L/opt/homebrew/Cellar/sdl2_ttf/2.24.0/lib

# Flags
COMPILER_FLAGS = -std=c++11 -Wall -O0 -g
LINKER_FLAGS = -lsdl2 -lsdl2_image -lsdl2_ttf

all: create_build_dir
	$(CC) $(COMPILER_FLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(SRC_FILES) $(LINKER_FLAGS) -o $(BUILD_DIR)/$(OBJ_NAME)

create_build_dir:
	mkdir -p $(BUILD_DIR)

# Cleaning rule
clean:
	rm -rf $(BUILD_DIR)/*