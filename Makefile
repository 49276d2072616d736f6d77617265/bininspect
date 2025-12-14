CC ?= gcc
# CC ?=x86_64-w64-mingw32-g++
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -Iinclude -O2
LDLIBS ?= -lm

BIN := build/bininspect
OBJDIR := build/obj

SRCS := src/main.c \
	src/modules/file_io.c \
	src/modules/endian.c \
	src/modules/hash_sha256.c \
	src/modules/magic.c \
	src/modules/entropy.c \
	src/modules/inspect.c  \
	src/modules/json.c \
	src/modules/elf_parse.c \
	src/modules/pe_parse.c \
	src/modules/strings.c


OBJS := $(SRCS:%.c=$(OBJDIR)/%.o)

all: $(BIN)

$(BIN): $(OBJS)
	@mkdir -p build
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDLIBS)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf build

.PHONY: all clean
