CC = g++
CC_FLAGS = -I./include/ -I./external/glad/include/ -lglfw -lGL -fPIC -Wall
CC_TEST_FLAGS = -I./include/ -L./lib -laxolote -Wall

TARGET = libaxolote.so
TARGET_DIR = lib
SRC = $(shell find ./src -name "*.cpp")
SRC += external/glad/src/glad.c
OBJ = $(patsubst ./src/%.cpp, ./obj/%.o, $(filter %.cpp, $(SRC)))
OBJ += obj/glad.o

TEST = axolote-engine-test
TEST_SRC = $(shell find ./tests -name "*.cpp")
TEST_OBJ = $(patsubst ./tests/%.cpp, ./obj/%.o, $(TEST_SRC))
TEST_TARGET_DIR = tests/bin

$(TARGET): dir
	$(CC) -c $(SRC) $(CC_FLAGS)
	mv *.o ./obj/
	$(CC) -shared -o ./$(TARGET_DIR)/$(TARGET) $(OBJ) $(CC_FLAGS)
	printf "\e[1;31m==== Finished compiling library ====\e[0m\n"

debug: CC_FLAGS += -g3 -fsanitize=address,undefined
debug: $(TARGET)

test: $(TARGET)
	$(CC) -c $(TEST_SRC) $(CC_TEST_FLAGS)
	mv *.o ./obj/
	$(CC) -o ./$(TEST_TARGET_DIR)/$(TEST) $(TEST_OBJ) $(CC_TEST_FLAGS)
	printf "\e[1;31m==== Finished compiling tests ====\e[0m\n\n"

	LD_LIBRARY_PATH="${LD_LIBRARY_PATH}:./lib" MESA_GL_VERSION_OVERRIDE=3.3 \
	./$(TEST_TARGET_DIR)/$(TEST)

.PHONY: dir
dir:
	if [ ! -d $(TARGET_DIR) ]; then mkdir $(TARGET_DIR); fi
	if [ ! -d $(TEST_TARGET_DIR) ]; then mkdir -p $(TEST_TARGET_DIR); fi
	if [ ! -d obj ]; then mkdir obj; fi

.PHONY: clean
clean: ./$(TARGET_DIR)/$(TARGET)
	rm ./$(TARGET_DIR)/*
