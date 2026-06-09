CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude
TEST_CXXFLAGS = $(CXXFLAGS) -pthread
TEST_LDFLAGS = -lgtest -lgtest_main -pthread

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TEST_DIR = tests


SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

TEST_OBJECTS = $(filter-out $(OBJ_DIR)/main.o, $(OBJECTS))

TEST_SOURCES = $(wildcard $(TEST_DIR)/*.cpp)
TEST_BIN = $(BIN_DIR)/symulacja_test



TARGET = $(BIN_DIR)/symulacja

.PHONY: all clean run directories test dashboard

all: directories $(TARGET)

directories:
	@mkdir -p $(OBJ_DIR) $(BIN_DIR) config output

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | directories
	$(CXX) $(CXXFLAGS) -c -o $@ $<



test: directories $(TEST_OBJECTS) $(TEST_BIN)
	./$(TEST_BIN)

$(TEST_BIN): $(TEST_SOURCES) $(TEST_OBJECTS)
	$(CXX) $(TEST_CXXFLAGS) -o $@ $^ $(TEST_LDFLAGS)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) output/*.csv temp_test_config.ini

run: all
	./$(TARGET)

dashboard:
	streamlit run dashboard.py
