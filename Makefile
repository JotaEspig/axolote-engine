CC = g++
CC_FLAGS = -I./include/ -I./external/include/ -lglfw -lGL -fPIC -Wall
CC_TEST_FLAGS = -I./include/ -I./external/include/ -L./lib -laxolote -Wall

TARGET = libaxolote.so
TARGET_DIR = lib

SRC_DIR = src
SRC = $(shell find ./$(SRC_DIR) -name "*.cpp")
OBJ_DIR = obj
OBJ = $(patsubst ./$(SRC_DIR)/%.cpp, ./$(OBJ_DIR)/%.o, $(filter %.cpp, $(SRC)))

SRC_EXTERNAL = external/glad/src/glad.c
OBJ_EXTERNAL = $(OBJ_DIR)/glad.o

TEST_TARGET = axolote-engine-test
TEST_DIR = tests
TEST_SRC = $(shell find ./$(TEST_DIR) -name "*.cpp")
TEST_OBJ = $(patsubst ./$(TEST_DIR)/%.cpp, ./$(OBJ_DIR)/%.o, $(TEST_SRC))
TEST_TARGET_DIR = $(TEST_DIR)/bin

$(TARGET): dir $(OBJ) $(OBJ_EXTERNAL)
	@printf "\e[1;33m==== Compiling library ====\e[0m\n"
	$(CC) -shared -o ./$(TARGET_DIR)/$(TARGET) $(OBJ) $(OBJ_EXTERNAL) $(CC_FLAGS)
	@printf "\e[1;31m==== Finished compiling library ====\e[0m\n\n"

debug: CC_FLAGS += -g3 -fsanitize=address,undefined
debug: CC_TEST_FLAGS += -g3 -fsanitize=address,undefined
debug: test

$(OBJ): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CC) $(CC_FLAGS) -c -o $@ $<

$(OBJ_EXTERNAL): $(OBJ_DIR)/%.o : external/glad/src/%.c
	$(CC) $(CC_FLAGS) -c -o $@ $<

test: $(TARGET)
	@printf "\e[1;33m==== Compiling tests ====\e[0m\n"
	$(CC) -c $(TEST_SRC) $(CC_TEST_FLAGS)
	@mv *.o ./obj/
	$(CC) -o ./$(TEST_TARGET_DIR)/$(TEST_TARGET) $(TEST_OBJ) $(CC_TEST_FLAGS)
	@printf "\e[1;31m==== Finished compiling tests ====\e[0m\n\n"
	@printf "\e[1;33mRunning...\e[0m\n\n"

	@LD_LIBRARY_PATH="${LD_LIBRARY_PATH}:./lib" MESA_GL_VERSION_OVERRIDE=3.3 \
	./$(TEST_TARGET_DIR)/$(TEST_TARGET)

install:
	// TODO

.PHONY: dir
dir:
	@if [ ! -d $(TARGET_DIR) ]; then mkdir $(TARGET_DIR); fi
	@if [ ! -d $(TEST_TARGET_DIR) ]; then mkdir -p $(TEST_TARGET_DIR); fi
	@if [ ! -d $(OBJ_DIR) ]; then mkdir $(OBJ_DIR); fi

.PHONY: clean
clean: dir
	-rm ./$(TARGET_DIR)/* 2> /dev/null
	-rm ./$(TEST_TARGET_DIR)/* 2> /dev/null
	-rm ./$(OBJ_DIR)/* 2> /dev/null
