SOURCE=aes.c aes_tables.c modes/cbc.c modes/ecb.c modes/padding.c main.c
HEADER=aes.h modes/cbc.h modes/ecb.h modes/padding.h
TARGET=aes.out

all: $(TARGET)

clean:
	rm $(TARGET)

$(TARGET): $(SOURCE) $(HEADER)
	gcc $(SOURCE) -o $(TARGET)

.PHONY: all clean
