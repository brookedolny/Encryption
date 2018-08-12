SOURCE=main.c sha.c sha1.c sha256.c sha_tables.c
HEADER=sha.h sha1.h sha256.h sha_functions.h
TARGET=sha.out

all: $(TARGET)

clean:
	rm $(TARGET)

$(TARGET): $(SOURCE) $(HEADER)
	gcc $(SOURCE) -o $(TARGET)

.PHONY: all clean
