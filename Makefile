# Compiler and flags
CXX = g++
CXXFLAGS = -Iinclude -std=c++11 `sdl2-config --cflags`

# Directories
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

# Target executable
TARGET = powerpoint

# SDL2 linking flags (add SDL_image or other SDL libraries if needed)
LDFLAGS = `sdl2-config --libs`

# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Compilation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)

.PHONY: all clean