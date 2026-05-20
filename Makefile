# =========================================================
# Project
# =========================================================

NAME := libftprintf.a
TEST := build/tests/test_ftprintf

# =========================================================
# Directories
# =========================================================

SRC_DIR := src
OBJ_DIR := build/obj
INC_DIR := include
LIBFT_DIR := lib

# =========================================================
# Compiler
# =========================================================

CC := cc
AR := ar rcs

# =========================================================
# Flags
# =========================================================

CFLAGS := -Wall -Wextra -Werror
CFLAGS += -Wpedantic -std=c11
CFLAGS += -O2
CFLAGS += -I$(INC_DIR)
CFLAGS += -I$(LIBFT_DIR)

ifdef DEBUG
CFLAGS += -g3
CFLAGS += -fsanitize=address,undefined
LDFLAGS += -fsanitize=address,undefined
endif

# =========================================================
# Sources
# =========================================================

SRC := \
	src/core/ft_printf.c \
	src/conversions/print_char.c \
	src/conversions/print_str.c \
	src/conversions/print_int.c \
	src/conversions/print_uint.c \
	src/conversions/print_hex.c \
	src/conversions/print_ptr.c \
	src/conversions/print_percent.c \
	src/utils/ft_print_utils.c

OBJ := $(SRC:src/%.c=$(OBJ_DIR)/%.o)
DEP := $(OBJ:.o=.d)

# =========================================================
# Libft
# =========================================================

LIBFT := $(LIBFT_DIR)/libft.a

# =========================================================
# Rules
# =========================================================

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	$(AR) $@ $^

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# =========================================================
# Test
# =========================================================

test: all
	@mkdir -p build/tests
	$(CC) $(CFLAGS) $(LDFLAGS) \
		tests/test_ftprintf.c \
		$(NAME) \
		$(LIBFT) \
		-o $(TEST)
	./$(TEST)

# =========================================================
# Clean
# =========================================================

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)
	rm -rf build/tests

re: fclean all

# =========================================================
# Includes
# =========================================================

-include $(DEP)

.PHONY: all clean fclean re test