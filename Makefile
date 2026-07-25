# Makefile
# ‾‾‾‾‾‾‾‾

# clang										\
	-O0 -Wall -Wextra -Wpedantic			\
	-I"$( brew --prefix libmagic )/include"	\
	-L"$( brew --prefix libmagic )/lib"		\
	-lmagic									\
	-o ~cs/C/ls.c/out/lk					\
	~cs/C/ls.c/source/**/*.c				\
		&& lk --clear

# ——————————————————————————————————————————————————————————————————————————————————————————————————————————————————— #

CC		= clang
CFLAGS	= -O0 -Wall -Wextra -Wpedantic

# ——————————————————————————————————————————————————————————————————————————————————————————————————————————————————— #

TARGET = out/lk

# ———————————————————————————————————————————————————————— #

# recursively find all .c files in the source directory
SOURCES = $(shell find source -type f -name '*.c')

# convert list of source files into a list of object files (.c => .o)
OBJECTS = $(patsubst source/%.c, out/%.o, $(SOURCES))

# ———————————————————————————————————————————————————————— #

FRAMEWORKS	= -framework CoreFoundation

# find where the `libmagic` library is stored, and pass it to the linker
BREW_PREFIX	:= $(shell brew --prefix libmagic)
INCLUDES	= -I$(BREW_PREFIX)/include
LDFLAGS		= -L$(BREW_PREFIX)/lib
LDLIBS		= -lmagic

# ——————————————————————————————————————————————————————————————————————————————————————————————————————————————————— #

.PHONY: all run

all: $(TARGET)

# ———————————————————————————————————————————————————————— #

# link all object files into the final executable
$(TARGET): $(OBJECTS)
	@$(CC) $(LDFLAGS) $(LDLIBS) $(FRAMEWORKS) --output $@ $^

# compile all .c files into .o files
out/%.o: source/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< --output $@

run: $(TARGET)
	./$(TARGET) --clear
	@rm -f $(OBJECTS)

# ——————————————————————————————————————————————————————————————————————————————————————————————————————————————————— #

# spell:ignoreRegExp /(?<!-)-(?!framework)\w/g
