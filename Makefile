# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./src

# Directories
SRC_DIR = src
TEST_DIR = tests
BIN_DIR = bin

# Source files
SRC_FILES = $(SRC_DIR)/*.cpp
TEST_FILES = $(TEST_DIR)/*.cpp

# Additional sources for compiler and interpreter
COMPILER_SRC = $(SRC_DIR)/compiler.cpp
INTERPRETER_SRC = $(SRC_DIR)/interpreter.cpp

# Output files
TEST_TARGET = $(BIN_DIR)/test.exe
COMPILER_TARGET = $(BIN_DIR)/compiler.exe
INTERPRETER_TARGET = $(BIN_DIR)/interpreter.exe

# Detect operating system using OS variable
ifeq ($(OS), Windows_NT)
    MKDIR = mkdir
    RUN_CMD = $(TEST_TARGET)
else
    MKDIR = mkdir -p
    RUN_CMD = ./$(TEST_TARGET)
endif

# Make sure the bin directory exists
$(BIN_DIR):
	$(MKDIR) $(BIN_DIR)

# Rule to build the test executable
$(TEST_TARGET): $(SRC_FILES) $(TEST_FILES) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_FILES) $(TEST_FILES) -o $(TEST_TARGET)

# Rule to build the compiler executable
$(COMPILER_TARGET): $(SRC_FILES) $(COMPILER_SRC) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_FILES) $(COMPILER_SRC) -o $(COMPILER_TARGET)

# Rule to build the interpreter executable
$(INTERPRETER_TARGET): $(SRC_FILES) $(INTERPRETER_SRC) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_FILES) $(INTERPRETER_SRC) -o $(INTERPRETER_TARGET)

# Rule to run the tests
test: $(TEST_TARGET)
	$(RUN_CMD)

# Rule to run the compiler (adjust as needed)
run_compiler: $(COMPILER_TARGET)
ifeq ($(OS), Windows_NT)
	$(COMPILER_TARGET)
else
	./$(COMPILER_TARGET)
endif

# Rule to run the interpreter (adjust as needed)
run_interpreter: $(INTERPRETER_TARGET)
ifeq ($(OS), Windows_NT)
	$(INTERPRETER_TARGET)
else
	./$(INTERPRETER_TARGET)
endif

# Rule to clean up generated files
clean:
	rm -rf $(BIN_DIR)/*.exe

# Phony targets
.PHONY: clean test run_compiler run_interpreter
