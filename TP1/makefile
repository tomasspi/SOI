# compilador
CC = gcc

# flags para el compilador
CFLAGS  = -Wall -pedantic

# Output
TARGET = rdproc

all: $(TARGET)
 $(TARGET): $(TARGET).c
	 $(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
	$(RM) $(TARGET)
