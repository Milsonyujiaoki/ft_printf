# =========================================================
# Compiler / Archiver
# =========================================================

CC       = gcc
AR       = ar
ARFLAGS  = rcs

# =========================================================
# Project
# =========================================================

NAME     = libftprintf

# =========================================================
# Directories
# =========================================================

SRC_DIR      = src
TEST_SRC_DIR = tests
INC_DIR      = include

BUILD_DIR    = build

STATIC_DIR   = $(BUILD_DIR)/static
SHARED_DIR   = $(BUILD_DIR)/shared

OBJ_DIR      = $(BUILD_DIR)/obj
OBJ_STATIC   = $(OBJ_DIR)/static
OBJ_SHARED   = $(OBJ_DIR)/shared

TEST_DIR     = $(BUILD_DIR)/tests

# =========================================================
# Dependency: libft
# =========================================================

LIBFT_DIR  = libft
LIBFT      = $(LIBFT_DIR)/build/static/libft.a

# =========================================================
# Library output
# =========================================================

STATIC_LIB     = $(STATIC_DIR)/$(NAME).a

SHARED_MAJOR   = 1
SHARED_VERSION = $(SHARED_MAJOR).0.0
SHARED_SONAME  = $(NAME).so.$(SHARED_MAJOR)
SHARED_LIB     = $(SHARED_DIR)/$(NAME).so.$(SHARED_VERSION)
SHARED_LINK    = $(SHARED_DIR)/$(NAME).so

# =========================================================
# Compiler flags
# =========================================================

CFLAGS     = -Wall -Wextra -Werror
CFLAGS    += -Wpedantic -std=c11
CFLAGS    += -O2
CFLAGS    += -I$(INC_DIR) -I$(LIBFT_DIR)/include
CFLAGS    += -MMD -MP

PIC_FLAGS  = -fPIC

LDFLAGS    = -L$(STATIC_DIR) -lftprintf -L$(LIBFT_DIR)/build/static -lft

SHARED_LDFLAGS = -shared -Wl,-soname,$(SHARED_SONAME)

# =========================================================
# Debug
# =========================================================

DEBUG_FLAGS  = -g3
DEBUG_FLAGS += -fsanitize=address,undefined

debug: CFLAGS  += $(DEBUG_FLAGS)
debug: LDFLAGS += -fsanitize=address,undefined
debug: all

# =========================================================
# Sources
# =========================================================

SRC         = $(wildcard $(SRC_DIR)/*/*.c)

OBJ_STATICS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_STATIC)/%.o,$(SRC))
OBJ_SHAREDS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_SHARED)/%.o,$(SRC))

DEP_STATICS = $(OBJ_STATICS:.o=.d)
DEP_SHAREDS = $(OBJ_SHAREDS:.o=.d)

# =========================================================
# Tests
# =========================================================

TESTS     = $(wildcard $(TEST_SRC_DIR)/*.c)
TEST_BINS = $(patsubst $(TEST_SRC_DIR)/%.c,$(TEST_DIR)/%,$(TESTS))

# =========================================================
# Main targets
# =========================================================

all: $(LIBFT) static tests

static: $(STATIC_LIB)

shared: $(LIBFT) $(SHARED_LIB)

tests: $(TEST_BINS)

# =========================================================
# Build libft
# =========================================================

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) static

# =========================================================
# Static objects
# =========================================================

$(OBJ_STATIC)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# =========================================================
# Shared objects (PIC)
# =========================================================

$(OBJ_SHARED)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(PIC_FLAGS) -c $< -o $@

# =========================================================
# Static library
# =========================================================

$(STATIC_LIB): $(OBJ_STATICS)
	@mkdir -p $(STATIC_DIR)
	$(AR) $(ARFLAGS) $@ $^
	@echo "Built static library: $@"

# =========================================================
# Shared library
# =========================================================

$(SHARED_LIB): $(OBJ_SHAREDS)
	@mkdir -p $(SHARED_DIR)
	$(CC) $(SHARED_LDFLAGS) -o $@ $^
	ln -sfn $(notdir $@) $(SHARED_LINK)
	@echo "Built shared library: $@"

# =========================================================
# Test binaries
# =========================================================

$(TEST_DIR)/%: $(TEST_SRC_DIR)/%.c $(STATIC_LIB)
	@mkdir -p $(dir $@)
	$(CC) $(filter-out -Werror,$(CFLAGS)) $< $(LDFLAGS) -o $@

# =========================================================
# Run tests
# =========================================================

test: all
	@echo ""
	@echo "========================================"
	@echo " Running test suite"
	@echo "========================================"
	@PASS=0; FAIL=0; \
	for bin in $(TEST_BINS); do \
		if [ -f $$bin ]; then \
			echo ""; \
			echo "--- $$bin ---"; \
			$$bin; \
			if [ $$? -eq 0 ]; then \
				PASS=$$((PASS+1)); \
			else \
				FAIL=$$((FAIL+1)); \
			fi; \
		fi; \
	done; \
	echo ""; \
	echo "========================================"; \
	echo " Suites: $$PASS passed, $$FAIL failed"; \
	echo "========================================"; \
	[ $$FAIL -eq 0 ]

# =========================================================
# Cleanup
# =========================================================

clean:
	rm -rf $(BUILD_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean

re: fclean all

# =========================================================
# Dependency files
# =========================================================

-include $(DEP_STATICS)
-include $(DEP_SHAREDS)

# =========================================================
# Phony
# =========================================================

.PHONY: all static shared tests test debug clean fclean re
