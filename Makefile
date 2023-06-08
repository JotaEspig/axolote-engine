CC = g++
CC_FLAGS = -I./include/ -lglut -lGLU -lGL -Wall
CC_TEST_FLAGS = -I./include/ -L./lib/ -laxolote -Wall

TARGET = libaxolote.so
TARGET_DIR = lib
SRC = $(shell find ./src -name "*.cpp")
OBJ = $(patsubst ./src/%.cpp, ./obj/%.o, $(SRC))

TEST = axolote-engine-test
TEST_SRC = $(shell find ./tests -name "*.cpp")
TEST_OBJ = $(patsubst ./tests/%.cpp, ./obj/%.o, $(TEST_SRC))
TEST_TARGET_DIR = tests/bin

$(TARGET): dir
	$(CC) -c $(SRC) $(CC_FLAGS)
	mv *.o ./obj/
	$(CC) -shared -o ./$(TARGET_DIR)/$(TARGET) $(OBJ)

debug: CC_FLAGS += -g3 -fsanitize=address,undefined
debug: $(TARGET)

test: $(TARGET)
	$(CC) -c $(TEST_SRC) $(CC_TEST_FLAGS)
	mv *.o ./obj/
	$(CC) -o ./$(TEST_TARGET_DIR)/$(TEST) $(TEST_OBJ) $(CC_TEST_FLAGS)
	LD_LIBRARY_PATH="${LD_LIBRARY_PATH}:./lib" ./$(TEST_TARGET_DIR)/$(TEST)

.PHONY: dir
dir:
	if [ ! -d $(TARGET_DIR) ]; then mkdir $(TARGET_DIR); fi
	if [ ! -d $(TEST_TARGET_DIR) ]; then mkdir -p $(TEST_TARGET_DIR); fi
	if [ ! -d obj ]; then mkdir obj; fi

.PHONY: clean
clean: ./$(TARGET_DIR)/$(TARGET)
	rm ./$(TARGET_DIR)/*
