# Kompilator
CC = gcc

# Flagi kompilatora
CFLAGS = -Wall -Wextra -std=c11

# Nazwa programu
TARGET = program

# Pliki źródłowe
SRCS = main.c

# Pliki obiektowe
OBJS = $(SRCS:.c=.o)

# Reguła domyślna
all: $(TARGET)

# Reguła budowania programu
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Reguła budowania plików obiektowych
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Reguła czyszczenia
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean