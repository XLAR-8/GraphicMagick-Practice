RM		= rm
CC      = gcc
CFLAGS  = $(shell GraphicsMagick-config --cppflags --cflags)
LDFLAGS = $(shell GraphicsMagick-config --ldflags) -lGraphicsMagickWand $(shell GraphicsMagick-config --libs)
TARGET  = test_is_opaque_image

all: $(TARGET)

$(TARGET): test_is_opaque_image.c
	$(CC) -o $@ $< $(CFLAGS) $(LDFLAGS)

clean:
	$(RM) -f $(TARGET)
