# Define the compiler to use
CXX=g++

# Compiler flags
CXXFLAGS=-std=c++11 -Wall -Wextra -Iinclude
# Linker flags
LDFLAGS=-pthread

# Define project directories
SRC_DIR=src
BUILD_DIR=build

# Define project files
SRCS=$(SRC_DIR)/main.cpp
OBJS=$(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Name of the final executable to produce
EXECUTABLE=matrix_test

# Default target
all: $(BUILD_DIR) $(EXECUTABLE)

# Ensure the build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
# Rule to link the executable
$(EXECUTABLE): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)
# Rule to compile source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean project
clean:
	rm -rf $(BUILD_DIR) $(EXECUTABLE)
# Rebuild project
re: clean all

# Phony targets
.PHONY: all clean re