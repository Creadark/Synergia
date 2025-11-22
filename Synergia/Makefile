CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic
TARGET = student_demo
SOURCES = main.c student.c
HEADERS = student.h

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: clean run
