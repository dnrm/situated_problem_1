# Makefile for situated_problem_1 project
# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -O2
INCLUDES = -I.
SRCDIR = src
OBJDIR = obj

# Source files
SRC_FILES = $(wildcard $(SRCDIR)/*.cpp)
SOURCES = main.cpp $(SRC_FILES)
OBJ_FILES = $(SRC_FILES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
OBJECTS = $(OBJDIR)/main.o $(OBJ_FILES)
EXECUTABLE = main

# Default target
all: $(EXECUTABLE)

# Create object directory if it doesn't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Build the executable by linking all object files together
$(EXECUTABLE): $(OBJECTS)
	@echo "Linking all object files into executable: $(EXECUTABLE)"
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXECUTABLE)
	@echo "Build complete!"

# Compile main.cpp
$(OBJDIR)/main.o: main.cpp | $(OBJDIR)
	@echo "Compiling main.cpp..."
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c main.cpp -o $(OBJDIR)/main.o

# Generic rule to compile all .cpp files in src directory
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Run the program
run: $(EXECUTABLE)
	./$(EXECUTABLE)

# Clean build artifacts
clean:
	rm -rf $(OBJDIR) $(EXECUTABLE)

# Clean and rebuild
rebuild: clean all

# Install dependencies (if needed)
install:
	@echo "No external dependencies required for this project"

# Debug build with additional flags
debug: CXXFLAGS += -DDEBUG -g3 -O0
debug: clean $(EXECUTABLE)

# Release build with optimizations
release: CXXFLAGS += -DNDEBUG -O3
release: clean $(EXECUTABLE)

# Check for memory leaks (requires valgrind)
memcheck: $(EXECUTABLE)
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXECUTABLE)

# Static analysis (requires cppcheck)
analyze:
	cppcheck --enable=all --std=c++17 --suppress=missingIncludeSystem main.cpp $(SRCDIR)/*.cpp

# Format code (requires clang-format)
format:
	clang-format -i -style=Google main.cpp $(SRCDIR)/*.cpp $(SRCDIR)/*.h

# Show help
help:
	@echo "Available targets:"
	@echo "  all       - Build the project (default)"
	@echo "  run       - Build and run the executable"
	@echo "  clean     - Remove build artifacts"
	@echo "  rebuild   - Clean and rebuild"
	@echo "  debug     - Build with debug flags"
	@echo "  release   - Build with release optimizations"
	@echo "  memcheck  - Run with valgrind memory checker"
	@echo "  analyze   - Run static analysis with cppcheck"
	@echo "  format    - Format code with clang-format"
	@echo "  help      - Show this help message"

# Declare phony targets
.PHONY: all run clean rebuild install debug release memcheck analyze format help
