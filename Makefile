# Compiler and Flags
CXX = g++
CXXFLAGS = -O2 -std=gnu++17 -Wall -Wextra -pedantic -flto=auto
LDFLAGS = -lraylib -flto=auto

# Directories
BIN = bin
OBJ = obj
SRC = src
INCLUDE = include

# Source and Object Files
SOURCES = $(wildcard $(SRC)/*.cpp)
OBJECTS = $(patsubst $(SRC)/%.cpp,$(OBJ)/%.o,$(SOURCES))

# Executable Name
EXECUTABLE = $(BIN)/blockbiter

# Target: All
all: $(EXECUTABLE)

# Create the Executable
$(EXECUTABLE): $(OBJECTS)
	mkdir -p $(BIN)
	$(CXX) $(OBJECTS) -o $(EXECUTABLE) $(LDFLAGS)

# Create Object Files
$(OBJ)/%.o: $(SRC)/%.cpp
	mkdir -p $(OBJ)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE) -c $< -o $@

# Clean Target
clean:
	rm -rf $(BIN) $(OBJ)
