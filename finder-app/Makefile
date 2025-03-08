CC = $(CROSS_COMPILE)gcc
CFLAGS = -g -Wall -Werror

objects = writer.o

%.o : %.c
	$(CC) -c $(CFLAGS) $^ -o $@

default: $(objects)
	$(CC) $^ -o writer

clean:
	echo "clean"
	rm -f *.o writer

