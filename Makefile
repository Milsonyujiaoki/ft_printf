# =========================================================
# Project
# =========================================================
NAME := libftprintf



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
BINS_DIR  = $(BUILD_DIR)/bins

LIBFT_DIR        = ./libft
LIBFT_STATIC     = $(LIBFT_DIR)/build/static/libft.a
LIBFT_SHARED_DIR = $(LIBFT_DIR)/build/shared
LIBFT_SHARED     = $(LIBFT_SHARED_DIR)/libft.so.$(SHARED_MAJOR)

# =========================================================
# Library output
# =========================================================

STATIC_LIB   = $(STATIC_DIR)/$(NAME).a
SHARED_MAJOR  = 1
SHARED_VERSION = $(SHARED_MAJOR).0.0
SHARED_SONAME = $(NAME).so.$(SHARED_MAJOR)
SHARED_LIB    = $(SHARED_DIR)/$(NAME).so.$(SHARED_VERSION)
SHARED_LIB_MAJOR = $(SHARED_DIR)/$(SHARED_SONAME)
SHARED_LINK   = $(SHARED_DIR)/$(NAME).so
SHARED_MAP    = make/libftprintf.map



# =========================================================
# Sources
# =========================================================

SRC          = $(wildcard $(SRC_DIR)/*/*.c)

OBJ_STATICS  = $(patsubst $(SRC_DIR)/%.c,$(OBJ_STATIC)/%.o,$(SRC))
OBJ_SHAREDS  = $(patsubst $(SRC_DIR)/%.c,$(OBJ_SHARED)/%.o,$(SRC))

DEP_STATICS  = $(OBJ_STATICS:.o=.d)
DEP_SHAREDS  = $(OBJ_SHAREDS:.o=.d)

# =========================================================
# Tests
# =========================================================

TESTS        = $(wildcard $(TEST_SRC_DIR)/*/*.c)

TEST_BINS    = $(patsubst $(TEST_SRC_DIR)/%.c,$(TEST_DIR)/%,$(TESTS))

# =========================================================
# Compiler / Archiver
# =========================================================
CC := cc
AR := ar
ARFLAGS  = rcs

CFLAGS := -Wall -Wextra -Werror 
CFLAGS      += -Wpedantic -std=c11 # Enforce C11 standard and pedantic warnings
CFLAGS      += -O2 # Optimize for speed (can be adjusted for debugging)
CFLAGS      += -I$(INC_DIR)
CFLAGS      += -MMD -MP # Dependency Generation

CFLAGS += -I$(LIBFT_DIR)/include # Include libft headers for tests

TEST_INC     = -I$(INC_DIR)/core

PIC_FLAGS    = -fPIC # Position Independent Code for shared library

LDFLAGS      = -L$(STATIC_DIR) -lftprintf # Link against static library for tests
SHARED_LDFLAGS = -shared -Wl,-soname,$(SHARED_SONAME) -Wl,--version-script=$(abspath $(SHARED_MAP))


# =========================================================
# Main targets
# =========================================================



all: static 

static: $(STATIC_LIB)

shared: $(SHARED_LIB)

tests: $(TEST_BINS)

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
# Auto-build libft
# =========================================================

$(LIBFT_STATIC):
	$(MAKE) -C $(LIBFT_DIR) static

$(LIBFT_SHARED):
	$(MAKE) -C $(LIBFT_DIR) shared

# =========================================================
# Static library
# =========================================================

$(STATIC_LIB): $(OBJ_STATICS) $(LIBFT_STATIC)
	@mkdir -p $(STATIC_DIR)
	cp $(LIBFT_STATIC) $@
	$(AR) $(ARFLAGS) $@ $(OBJ_STATICS)
	@echo "Built static library: $@"

# =========================================================
# Shared library
# =========================================================

$(SHARED_LIB): $(OBJ_SHAREDS) $(LIBFT_SHARED)
	@mkdir -p $(SHARED_DIR)
	$(CC) $(SHARED_LDFLAGS) -o $@ $(OBJ_SHAREDS) -L$(LIBFT_SHARED_DIR) -lft
	ln -sfn $(notdir $@) $(SHARED_LIB_MAJOR)
	ln -sfn $(notdir $(SHARED_LIB_MAJOR)) $(SHARED_LINK)
	@echo "Built shared library: $@"

# =========================================================
# Test binaries
# =========================================================

$(TEST_DIR)/%: $(TEST_SRC_DIR)/%.c $(STATIC_LIB)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(TEST_INC) \
		-include ft_printf.h \
		$< $(LDFLAGS) -o $@

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
# Install / Uninstall
# =========================================================

PREFIX ?= /usr/local

install: static shared
	@mkdir -p $(PREFIX)/include
	@mkdir -p $(PREFIX)/lib

	cp $(INC_DIR)/libftprintf.h $(PREFIX)/include/
	cp $(STATIC_LIB) $(PREFIX)/lib/
	cp -a $(SHARED_DIR)/$(NAME).so* $(PREFIX)/lib/

	@echo "Installed libftprintf to $(PREFIX)"

uninstall:
	rm -f $(PREFIX)/include/libftprintf.h
	rm -f $(PREFIX)/lib/libftprintf.a
	rm -f $(PREFIX)/lib/$(NAME).so
	rm -f $(PREFIX)/lib/$(NAME).so.$(SHARED_MAJOR)
	rm -f $(PREFIX)/lib/$(NAME).so.$(SHARED_VERSION)

	@echo "Removed libftprintf from $(PREFIX)"

# =========================================================
# Cleanup
# =========================================================

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean

libft_clean:
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

# =========================================================
# Dependency files
# =========================================================

-include $(DEP_STATICS)
-include $(DEP_SHAREDS)

.PHONY:\
	all \
	static \
	shared \
	tests \
	test \
	install \
	uninstall \
	clean \
	fclean \
	libft_clean \
	re