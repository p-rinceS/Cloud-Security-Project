
TARGET = vuln-app
CC = gcc
CFLAGS = -fno-stack-protector -z execstack -g -Wall
SRC = vuln-app.c
all: $(TARGET)
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Clean up 
clean:
	rm -f $(TARGET)


