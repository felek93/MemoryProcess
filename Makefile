CC = g++
CFLAGS = -Wall
LDFLAGS = 
OBJFILES = MemoryProcess.o example.o
TARGET = example.exe

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET)