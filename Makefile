CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0` -Iinclude -Wno-deprecated-declarations
LDFLAGS = `pkg-config --libs gtk+-3.0`
SRC = $(wildcard src/*.c)
Execution = myproject
TARGET = build/$(Execution)_app

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

run: $(TARGET)
	$(TARGET)

clean:
	rm -fr $(TARGET) src/*.o *.xls

.PHONY: all clean run
