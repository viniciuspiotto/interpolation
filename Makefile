CC = gcc
CFLAGS = -Wall -Wextra -pedantic -Iinclude
LDFLAGS = -lm
TARGET = interpolation
SRCDIR = src
OBJDIR = obj
BINDIR = bin
OUTPUT_FILE = output.txt
PLOTSDIR = plots

SRCS := $(wildcard $(SRCDIR)/*.c)
OBJS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

all: $(BINDIR)/$(TARGET)

$(BINDIR)/$(TARGET): $(OBJS)
	@mkdir -p $(BINDIR)
	@$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

run: all
	@./$(BINDIR)/$(TARGET)

clean:
	@rm -rf $(OBJDIR) $(BINDIR) $(OUTPUT_FILE) $(PLOTSDIR)

.PHONY: all run clean