NAME    := libftprintf.a

CC      := cc
AR      := ar
ARFLAGS := rcs

CFLAGS  := -Wall -Wextra -Werror
CFLAGS  += -Wpedantic -std=c11

SRC_DIR    := src
INC_DIR    := include
BUILD_DIR  := build
OBJ_DIR    := $(BUILD_DIR)/obj/static

LIBFT_DIR  := libft
LIBFT      := $(LIBFT_DIR)/build/static/libft.a

CPPFLAGS   := -I$(INC_DIR) -I$(LIBFT_DIR)/include

SRCS := $(wildcard $(SRC_DIR)/core/*.c) \
        $(wildcard $(SRC_DIR)/conversions/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

TEST_SRC := tests/test_ftprintf.c
TEST_BIN := $(BUILD_DIR)/test_ftprintf

# ---- Targets ----

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^
	@echo "Built: $@"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) static

# ---- Test ----

test: all $(TEST_BIN)
	@echo "--- Running tests ---"
	./$(TEST_BIN)

$(TEST_BIN): $(TEST_SRC) $(NAME) $(LIBFT)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(filter-out -Werror,$(CFLAGS)) $(CPPFLAGS) $(TEST_SRC) -o $@ \
		$(NAME) \
		-L$(LIBFT_DIR)/build/static -lft

# ---- Clean ----

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(TEST_BIN)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all test clean fclean re
