NAME := libftprintf.a

CC := cc
AR := ar rcs

CFLAGS := -Wall -Wextra -Werror 


BUILD_DIR = build
OBJ_DIR   = $(BUILD_DIR)/obj
TEST_DIR  = $(BUILD_DIR)/tests
BINS_DIR  = $(BUILD_DIR)/bins



LIB = $(BUILD_DIR)/$(NAME)

SRC := $(wildcard src/*.c)

OBJ := $(patsubst src/%.c,$(OBJ_DIR)/%.o,$(SRC))

 

all: $(LIB)


$(LIB): $(OBJ)
	@mkdir -p $(BUILD_DIR)
	$(AR) $@ $^
	@echo "Built: $@  ($(words $(OBJ)) objects)"

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB): $(OBJ)
	$(AR) $(LIB) $(OBJ)

run: 

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(LIB)

re: fclean all

.PHONY: all clean fclean re
