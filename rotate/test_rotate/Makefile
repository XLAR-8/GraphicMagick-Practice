RM		= rm
CC      = gcc
CFLAGS  = $(shell GraphicsMagick-config --cppflags --cflags)
LDFLAGS = $(shell GraphicsMagick-config --ldflags) $(shell GraphicsMagick-config --libs)
TARGET  = test_rotate

all: $(TARGET)

$(TARGET): test_rotate.c
	$(CC) -o $@ $< $(CFLAGS) $(LDFLAGS)

clean:
	$(RM) -f $(TARGET)
