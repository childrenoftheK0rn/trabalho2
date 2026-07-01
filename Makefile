CC     = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
SRCDIR = src
INCDIR = include
OBJDIR = obj
TARGET = sensor_system

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

all: $(OBJDIR) $(TARGET)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	@echo "Build concluido: ./$(TARGET)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(TARGET)

cleanall: clean
	rm -f sensores.bin setores.bin

run: all
	./$(TARGET)

.PHONY: all clean cleanall run