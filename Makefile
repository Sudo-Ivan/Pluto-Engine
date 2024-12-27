CC = gcc
CFLAGS = -Wall -Wextra -O2
INCLUDES = -I/opt/homebrew/include -I./include -I./src
LDFLAGS = -L/opt/homebrew/lib
LIBS = -lraylib -lGL -lm -lpthread -ldl

SRC_DIR = src
EXAMPLES_DIR = examples
BUILD_DIR = build

# Add ECS source files
CORE_SRCS = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/ecs/*.c)
CORE_OBJS = $(CORE_SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

EXAMPLES = $(basename $(notdir $(wildcard $(EXAMPLES_DIR)/*.c)))
EXAMPLE_TARGETS = $(addprefix $(BUILD_DIR)/,$(EXAMPLES))

all: engine examples

engine: $(BUILD_DIR)/engine

$(BUILD_DIR)/engine: $(CORE_OBJS)
	$(CC) $(CORE_OBJS) -o $@ $(LDFLAGS) $(LIBS)

examples: $(EXAMPLE_TARGETS)

$(BUILD_DIR)/%: $(EXAMPLES_DIR)/%.c $(filter-out $(BUILD_DIR)/main.o,$(CORE_OBJS))
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ $(LDFLAGS) $(LIBS)

# Create subdirectories for object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)