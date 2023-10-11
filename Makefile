TARGET_EXEC := bin
BUILD_DIR := ./build
SRC_DIR := ./src
INC_DIR := ./inc

CXX := g++
CXXFLAGS := -O0 -g -Werror -Wall -Wextra -std=c++17
LDFLAGS := -lgtest -lgtest_main -lpcre2-8
CPPFLAGS := -I$(SRC_DIR)/$(INC_DIR) -MMD -MP

SRCS := $(wildcard $(SRC_DIR)/*.cc)
OBJS := $(SRCS:$(SRC_DIR)/%.cc=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

# Valgrind
VALGRIND_FLAGS := --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose

.PHONY: all clean run valgrind

all: $(BUILD_DIR)/$(TARGET_EXEC)

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cc
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	rm -r $(BUILD_DIR)

run:
	@$(BUILD_DIR)/$(TARGET_EXEC)

valgrind:
	valgrind $(VALGRIND_FLAGS) $(BUILD_DIR)/$(TARGET_EXEC)

-include $(DEPS)
