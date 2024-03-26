# Compiler
CC = g++

# Compiler flags
CFLAGS = -Wall -Wextra -Iinclude `sdl2-config --cflags`

# Libraries
LIBS = `sdl2-config --libs`

# Source directory
SRCDIR = src

# Object directory
OBJDIR = obj

# Target executable
TARGET = pacman

# Source files
SRCS = $(wildcard $(SRCDIR)/*.cpp)

# Object files
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

# Default rule
all: $(TARGET)

# Rule to compile object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to link the object files into the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) $^ -o $@

# Create obj directory if it doesn't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Clean rule
clean:
	rm $(TARGET)
	rm $(OBJS)
	rmdir $(OBJDIR)

# Phony targets
.PHONY: all clean
