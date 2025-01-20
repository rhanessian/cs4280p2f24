CC = gcc
CFLAGS = -g -Wall
OBJFILES = scanner.o main.o parser.o 
TARGET = parser

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CLFAGS) -o $(TARGET) $(OBJFILES) 
	
clean:
	$(RM) $(OBJFILES) $(TARGET) temptext.txt