CC = g++
CC_FLAGS = -Wall \
TARGET = axolote-engine
TARGET_DIR = lib
SRC = $(shell find ./src -name "*.cpp")
TEST = axolote-engine-test
TEST_SRC = test
TEST_TARGET_DIR = $(TEST_SRC)/bin

$(TARGET): dir
	$(CC) -o ./$(TARGET_DIR)/$(TARGET) $(SRC) $(CC_FLAGS)

debug: CC_FLAGS += -g3 -fsanitize=address,undefined
debug: $(TARGET)

.PHONY: dir
dir:
	if [ ! -d $(TARGET_DIR) ]; then mkdir $(TARGET_DIR); fi
	if [ ! -d $(TEST_SRC) ]; then mkdir $(TEST_SRC); fi

.PHONY: clean
clean: ./$(TARGET_DIR)/$(TARGET)
	rm ./$(TARGET_DIR)/*
