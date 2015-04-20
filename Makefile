CC=gcc
CFLAGS=-g -Wall -Wextra -static
TARGET=a.out
SRCF=.
SRCS=main.c

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS =$(patsubst %.c, %.o, $(wildcard $(SRCF)/*.c))

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@ $(LDFLAGS)

clean:
	-rm -f $(SRCF)/*.o
	-rm -f $(TARGET)

