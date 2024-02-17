CC := gcc
CFLAGS := -Wall -Wextra -g
SRCDIR := src
PARSERDIR := src/core
BUILDDIR := build
SOURCES := $(wildcard $(SRCDIR)/*.c) $(wildcard $(PARSERDIR)/*.c)
OBJECTS := $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(filter $(SRCDIR)/%, $(SOURCES))) \
           $(patsubst $(PARSERDIR)/%.c, $(BUILDDIR)/core/%.o, $(filter $(PARSERDIR)/%, $(SOURCES)))
TARGET := example

.PHONY: build clean run

build: $(BUILDDIR)/$(TARGET)

$(BUILDDIR)/$(TARGET): $(OBJECTS) $(BUILDDIR)/$(TARGET).o
	$(CC) $(CFLAGS) $^ -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p "$(dir $@)"
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR)/parser/%.o: $(PARSERDIR)/%.c
	@mkdir -p "$(dir $@)"
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR)/$(TARGET).o: $(TARGET).c
	@mkdir -p "$(dir $@)"
	$(CC) $(CFLAGS) -c $< -o $@ 

run: $(BUILDDIR)/$(TARGET)
	@echo ""
	@echo "### Running program ###"
	@echo "-----------------------"
	@$(BUILDDIR)/$(TARGET)

clean:
	rm -rf "$(BUILDDIR)"

.PHONY: build clean run