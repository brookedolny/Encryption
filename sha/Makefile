SOURCE=main.c sha.c private/sha1.c private/sha256.c private/sha_tables.c
HEADER=sha.h private/sha1.h private/sha256.h private/sha_functions.h
TARGET=sha.out

all: $(TARGET)

clean:
	rm $(TARGET)

$(TARGET): $(SOURCE) $(HEADER)
	gcc $(SOURCE) -o $(TARGET)

.PHONY: all clean
